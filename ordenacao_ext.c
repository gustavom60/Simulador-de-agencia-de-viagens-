#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "ordenacao_ext.h"
#include "entidades.h"

#define TAM_MEMORIA_DEFAULT 100

typedef struct { //adiciona uma flag "congelado" ao tipo Turista
    Turista reg;
    int congelado;
} HeapItem;

void trocar(HeapItem *a, HeapItem *b) { //troca dois elementos de posição
    HeapItem temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapItem heap[], int n, int i) { //vetor de elementos HeapItem, qnt de elementos no vetor e o nó atual
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita  = 2 * i + 2;

    if (esquerda < n && heap[esquerda].reg.id < heap[menor].reg.id)
        menor = esquerda;
    if (direita < n && heap[direita].reg.id < heap[menor].reg.id)
        menor = direita;
    if (menor != i) {
        trocar(&heap[i], &heap[menor]);
        heapify(heap, n, menor);
    }
}

void construirHeap(HeapItem heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

int SelecionarPorSubstituicao(const char *nomeArquivoEntrada, const char *prefixoParticao) {

    //abre o arquivo
    FILE *entrada = fopen(nomeArquivoEntrada, "rb");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivoEntrada);
        return 0;
    }

    //aloca espaço necessário para armazenar os registros na heap
    int tamanhoMemoria = TAM_MEMORIA_DEFAULT;
    HeapItem *heap = malloc(tamanhoMemoria * sizeof(HeapItem));
    if (!heap) {
        printf("Erro ao alocar memória para a heap.\n");
        fclose(entrada);
        return 0;
    }

    //lê os registros até preencher a memória disponível
    int heapTamanho = 0;
    for (int i = 0; i < tamanhoMemoria; i++) {
        Turista t;
        if (fread(&t, sizeof(Turista), 1, entrada) == 1) {
            heap[i].reg = t;
            heap[i].congelado = 0;
            heapTamanho++;
        } else {
            break;
        }
    }

    construirHeap(heap, heapTamanho);

    //cria e abre o arquivo da primeira partição
    int numParticao = 1;
    char nomeParticao[100];
    sprintf(nomeParticao, "%s%d.dat", prefixoParticao, numParticao);
    FILE *saida = fopen(nomeParticao, "wb");
    if (!saida) {
        printf("Erro ao criar o arquivo de partição: %s\n", nomeParticao);
        free(heap);
        fclose(entrada);
        return 0;
    }

    //variável para armazenar o último id da partição, garantindo a ordem
    int ultimoValor = -1;

    while (heapTamanho > 0) { //executa enquanto houverem elementos na heap
        if (heap[0].congelado) { //cria uma nova partição se o menor elemento estiver congelado
            fclose(saida);
            numParticao++;
            sprintf(nomeParticao, "%s%d.dat", prefixoParticao, numParticao);
            saida = fopen(nomeParticao, "wb");
            if (!saida) {
                printf("Erro ao criar o arquivo de partição: %s\n", nomeParticao);
                break;
            }
            for (int i = 0; i < heapTamanho; i++) { //descongela os elementos para poder utilizá-los na nova partição
                heap[i].congelado = 0;
            }
            ultimoValor = -1;
        }

        Turista menorReg = heap[0].reg; //pega o menor registro
        fwrite(&menorReg, sizeof(Turista), 1, saida); //escreve o menor registro
        ultimoValor = menorReg.id; //atualiza o último valor utilizado

        Turista novo;
        if (fread(&novo, sizeof(Turista), 1, entrada) == 1) {
            if (novo.id >= ultimoValor) {
                heap[0].reg = novo;
                heap[0].congelado = 0;
            } else { //se a entidade que estiver sendo analisada for menor que o último escrita, congela
                heap[0].reg = novo;
                heap[0].congelado = 1;
            }
        } else { //remove o elemento se não houver mais registros
            heap[0] = heap[heapTamanho - 1];
            heapTamanho--;
        }

        heapify(heap, heapTamanho, 0); //refaz a heap após a substituição da raiz
    }

    fclose(saida);
    fclose(entrada);
    free(heap);

    printf("Selecao por Substituicao para Turistas concluida. %d particoes foram geradas.\n", numParticao);
    return numParticao;
}

void IntercalarArvoreVencedores(const char *prefixoParticao, int numParticoes, const char *nomeArquivoSaida) {

    //aloca a memória necessária
    FILE **particoes = malloc(numParticoes * sizeof(FILE*));
    Turista *v = malloc(numParticoes * sizeof(Turista));
    int *arvore = malloc(2 * numParticoes * sizeof(int));
    if (!particoes || !v || !arvore) {
        printf("Erro ao alocar memoria para intercalacao.\n");
        free(particoes); free(v); free(arvore);
        return;
    }

    char nomeParticao[100];

    //le o primeiro elemento de cada partição
    for (int i = 0; i < numParticoes; i++) {
        sprintf(nomeParticao, "%s%d.dat", prefixoParticao, i+1);
        particoes[i] = fopen(nomeParticao, "rb");
        if (!particoes[i]) {
            v[i].id = INT_MAX; //ignora a partição caso não consiga ser lida
        } else {
            if (fread(&v[i], sizeof(Turista), 1, particoes[i]) != 1) {
                v[i].id = INT_MAX;
            }
        }
    }

    int k = numParticoes;

    //preenche as folhas com os índices das partições
    for (int i = 0; i < k; i++) {
        arvore[i + k] = i;
    }

    //propaga o vencedor, comparando os menores registros dentre as partições, para a raiz
    for (int i = k - 1; i > 0; i--) {
        int idxEsq = arvore[2*i];
        int idxDir = arvore[2*i + 1];
        if (v[idxEsq].id <= v[idxDir].id)
            arvore[i] = idxEsq;
        else
            arvore[i] = idxDir;
    }

    //abre o arquivo onde será gravada a sequência ordenada
    FILE *saida = fopen(nomeArquivoSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saida: %s\n", nomeArquivoSaida);
        for (int i = 0; i < numParticoes; i++) {
            if (particoes[i])
                fclose(particoes[i]);
        }
        free(particoes); free(v); free(arvore);
        return;
    }

    while (v[arvore[1]].id != INT_MAX) { //executa enquanto o menor registro não for INT_MAX que sinaliza o fim dos dados
        int vencedor = arvore[1];
        fwrite(&v[vencedor], sizeof(Turista), 1, saida); //escreve o registro vencedor no arquivo de saída

        if (particoes[vencedor] && fread(&v[vencedor], sizeof(Turista), 1, particoes[vencedor]) != 1) {
            v[vencedor].id = INT_MAX; //tenta ler o próximo menor registro, se não conseguir define com INT_MAX
        }

        //atualiza a árvore para o novo conjunto de registros
        int pos = (vencedor + k) / 2;
        while (pos >= 1) {
            int idxEsq = arvore[2*pos];
            int idxDir = arvore[2*pos + 1];
            if (v[idxEsq].id <= v[idxDir].id)
                arvore[pos] = idxEsq;
            else
                arvore[pos] = idxDir;
            pos /= 2;
        }
    }

    fclose(saida);
    for (int i = 0; i < numParticoes; i++) {
        if (particoes[i])
            fclose(particoes[i]);
    }
    free(particoes);
    free(v);
    free(arvore);

    printf("Intercalacao por Arvore Binaria de Vencedores para Turistas concluida. Arquivo ordenado: %s\n", nomeArquivoSaida);
}

// ===========

typedef struct {
    Destino reg;   // Registro do destino
    int congelado; // 0 = não congelado, 1 = congelado
} HeapItemDestino;

void trocarDestino(HeapItemDestino *a, HeapItemDestino *b) {
    HeapItemDestino temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDestino(HeapItemDestino heap[], int n, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita  = 2 * i + 2;

    if (esquerda < n && heap[esquerda].reg.id < heap[menor].reg.id)
        menor = esquerda;
    if (direita < n && heap[direita].reg.id < heap[menor].reg.id)
        menor = direita;
    if (menor != i) {
        trocarDestino(&heap[i], &heap[menor]);
        heapifyDestino(heap, n, menor);
    }
}

void construirHeapDestino(HeapItemDestino heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDestino(heap, n, i);
    }
}

int SelecionarPorSubstituicaoDestino(const char *nomeArquivoEntrada, const char *prefixoParticao) {
    FILE *entrada = fopen(nomeArquivoEntrada, "rb");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivoEntrada);
        return 0;
    }

    int tamanhoMemoria = TAM_MEMORIA_DEFAULT;
    HeapItemDestino *heap = malloc(tamanhoMemoria * sizeof(HeapItemDestino));
    if (!heap) {
        printf("Erro ao alocar memoria para a heap de destinos.\n");
        fclose(entrada);
        return 0;
    }

    int heapTamanho = 0;
    for (int i = 0; i < tamanhoMemoria; i++) {
        Destino d;
        if (fread(&d, sizeof(Destino), 1, entrada) == 1) {
            heap[i].reg = d;
            heap[i].congelado = 0;
            heapTamanho++;
        } else {
            break;
        }
    }

    construirHeapDestino(heap, heapTamanho);

    int numParticao = 1;
    char nomeParticao[100];
    sprintf(nomeParticao, "%s%d.dat", prefixoParticao, numParticao);
    FILE *saida = fopen(nomeParticao, "wb");
    if (!saida) {
        printf("Erro ao criar o arquivo de particao: %s\n", nomeParticao);
        free(heap);
        fclose(entrada);
        return 0;
    }

    int ultimoValor = -1;

    while (heapTamanho > 0) {
        if (heap[0].congelado) {
            fclose(saida);
            numParticao++;
            sprintf(nomeParticao, "%s%d.dat", prefixoParticao, numParticao);
            saida = fopen(nomeParticao, "wb");
            if (!saida) {
                printf("Erro ao criar o arquivo de particao: %s\n", nomeParticao);
                break;
            }
            for (int i = 0; i < heapTamanho; i++) {
                heap[i].congelado = 0;
            }
            ultimoValor = -1;
        }

        Destino menorReg = heap[0].reg;
        fwrite(&menorReg, sizeof(Destino), 1, saida);
        ultimoValor = menorReg.id;

        Destino novo;
        if (fread(&novo, sizeof(Destino), 1, entrada) == 1) {
            if (novo.id >= ultimoValor) {
                heap[0].reg = novo;
                heap[0].congelado = 0;
            } else {
                heap[0].reg = novo;
                heap[0].congelado = 1;
            }
        } else {
            heap[0] = heap[heapTamanho - 1];
            heapTamanho--;
        }

        heapifyDestino(heap, heapTamanho, 0);
    }

    fclose(saida);
    fclose(entrada);
    free(heap);

    printf("Selecao por Substituicao para Destinos concluida. %d particoes foram geradas.\n", numParticao);
    return numParticao;
}

void IntercalarArvoreVencedoresDestino(const char *prefixoParticao, int numParticoes, const char *nomeArquivoSaida) {
    FILE **particoes = (FILE**) malloc(numParticoes * sizeof(FILE*));
    Destino *v = (Destino*) malloc(numParticoes * sizeof(Destino));
    int *arvore = (int*) malloc(2 * numParticoes * sizeof(int));
    if (!particoes || !v || !arvore) {
        printf("Erro ao alocar memoria para intercalacao de destinos.\n");
        free(particoes); free(v); free(arvore);
        return;
    }

    char nomeParticao[100];
    for (int i = 0; i < numParticoes; i++) {
        sprintf(nomeParticao, "%s%d.dat", prefixoParticao, i+1);
        particoes[i] = fopen(nomeParticao, "rb");
        if (!particoes[i]) {
            v[i].id = INT_MAX;
        } else {
            if (fread(&v[i], sizeof(Destino), 1, particoes[i]) != 1) {
                v[i].id = INT_MAX;
            }
        }
    }

    int k = numParticoes;
    for (int i = 0; i < k; i++) {
        arvore[i + k] = i;
    }
    for (int i = k - 1; i > 0; i--) {
        int idxEsq = arvore[2*i];
        int idxDir = arvore[2*i + 1];
        if (v[idxEsq].id <= v[idxDir].id)
            arvore[i] = idxEsq;
        else
            arvore[i] = idxDir;
    }

    FILE *saida = fopen(nomeArquivoSaida, "wb");
    if (!saida) {
        printf("Erro ao criar arquivo de saida: %s\n", nomeArquivoSaida);
        for (int i = 0; i < numParticoes; i++) {
            if (particoes[i])
                fclose(particoes[i]);
        }
        free(particoes); free(v); free(arvore);
        return;
    }

    while (v[arvore[1]].id != INT_MAX) {
        int vencedor = arvore[1];
        fwrite(&v[vencedor], sizeof(Destino), 1, saida);

        if (particoes[vencedor] && fread(&v[vencedor], sizeof(Destino), 1, particoes[vencedor]) != 1) {
            v[vencedor].id = INT_MAX;
        }

        int pos = (vencedor + k) / 2;
        while (pos >= 1) {
            int idxEsq = arvore[2*pos];
            int idxDir = arvore[2*pos + 1];
            if (v[idxEsq].id <= v[idxDir].id)
                arvore[pos] = idxEsq;
            else
                arvore[pos] = idxDir;
            pos /= 2;
        }
    }

    fclose(saida);
    for (int i = 0; i < numParticoes; i++) {
        if (particoes[i])
            fclose(particoes[i]);
    }
    free(particoes);
    free(v);
    free(arvore);

    printf("Intercalacao por Arvore Binaria de Vencedores para Destinos concluida. Arquivo ordenado: %s\n", nomeArquivoSaida);
}

void OrdenarTuristasExterna(const char *arquivo) {
    clock_t inicio = clock();
    int numParticoes = SelecionarPorSubstituicao(arquivo, "particao_turista");
    IntercalarArvoreVencedores("particao_turista", numParticoes, arquivo);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Obtem informações do arquivo ordenado
    FILE *fp = fopen(arquivo, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        int quantidade = fileSize / sizeof(Turista);
        fclose(fp);

        FILE *logFile = fopen("log.txt", "a");
        if (logFile != NULL) {
            fprintf(logFile, "Tipo de Ordenacao: Particoes e Intercalacoes\nEntidade: Turista\nQuantidade: %d entidades ordenadas\nTamanho total do arquivo: %ld bytes\nQuantidade de particoes: %d\nTempo: %.6f seconds\n\n", quantidade, fileSize, numParticoes, tempo);
            fclose(logFile);
        }
    }

    // Remover arquivos de particao utilizados
    for (int i = 1; i <= numParticoes; i++) {
        char nomeParticao[100];
        sprintf(nomeParticao, "particao_turista%d.dat", i);
        if (remove(nomeParticao) == 0) {
            // Arquivo removido com sucesso (pode imprimir mensagem de debug, se desejado)
        } else {
            printf("Aviso: nao foi possivel remover o arquivo %s\n", nomeParticao);
        }
    }

    printf("Ordenacao externa para Turistas concluida.\n");
}

void OrdenarDestinosExterna(const char *arquivo) {
    clock_t inicio = clock();
    int numParticoes = SelecionarPorSubstituicaoDestino(arquivo, "particao_destino");
    IntercalarArvoreVencedoresDestino("particao_destino", numParticoes, arquivo);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE *fp = fopen(arquivo, "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        int quantidade = fileSize / sizeof(Destino);
        fclose(fp);

        FILE *logFile = fopen("log.txt", "a");
        if (logFile != NULL) {
            fprintf(logFile, "Tipo de Ordenacao: Particoes e Intercalacoes\nEntidade: Destino\nQuantidade: %d entidades ordenadas\nTamanho total do arquivo: %ld bytes\nQuantidade de particoes: %d\nTempo: %.6f seconds\n\n", quantidade, fileSize, numParticoes, tempo);
            fclose(logFile);
        }
    }

    // Remover arquivos de particao utilizados
    for (int i = 1; i <= numParticoes; i++) {
        char nomeParticao[100];
        sprintf(nomeParticao, "particao_destino%d.dat", i);
        if (remove(nomeParticao) == 0) {
            // Arquivo removido com sucesso
        } else {
            printf("Aviso: nao foi possivel remover o arquivo %s\n", nomeParticao);
        }
    }

    printf("Ordenacao externa para Destinos concluida.\n");
}