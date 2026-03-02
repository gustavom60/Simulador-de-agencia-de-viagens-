#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entidades.h"
#include "salvar_entidades.h"

void CriarBaseTuristas(FILE *out, int tam) {
    Turista *t;
    char genericPaises[][MAX_NOME] = {"Pais1", "Pais2", "Pais3", "Pais4", "Pais5"};

    fseek(out, 0, SEEK_END);
    long fileSize = ftell(out);
    int registroExistente = fileSize / sizeof(Turista);
    int startId = registroExistente + 1;

    printf("Gerando a base de turistas (novos registros a partir do id %d)...\n", startId);

    for (int i = 0; i < tam; i++) {
        char nome[MAX_NOME];
        int novoId = startId + i;
        snprintf(nome, MAX_NOME, "Turista %d", novoId);

        char cpf[15];
        snprintf(cpf, 15, "000.000.000-%02d", novoId);

        char paisesInteresse[MAX_PAISES_INTERESSE][MAX_NOME];
        for (int j = 0; j < MAX_PAISES_INTERESSE; j++) {
            strncpy(paisesInteresse[j], genericPaises[j % 5], MAX_NOME);
        }

        t = malloc(sizeof(Turista));
        if (!t) {
            printf("Erro ao alocar memoria para Turista.\n");
            exit(1);
        }
        *t = criarTurista(novoId, nome, cpf, paisesInteresse, novoId * 1000.0);
        SalvarTurista(t, novoId);
        free(t);
    }
}

void CriarBaseDestinos(FILE *out, int tam) {
    Destino *d;
    char genericPaises[][MAX_NOME] = {"Pais1", "Pais2", "Pais3", "Pais4", "Pais5"};
    char genericAtracoes[][MAX_ATRACOES] = {"Atracao1", "Atracao2", "Atracao3", "Atracao4", "Atracao5"};

    fseek(out, 0, SEEK_END);
    long fileSize = ftell(out);
    int registroExistente = fileSize / sizeof(Destino);
    int startId = registroExistente + 1;

    printf("Gerando a base de destinos (novos registros a partir do id %d)...\n", startId);

    for (int i = 0; i < tam; i++) {
        int novoId = startId + i;
        d = malloc(sizeof(Destino));
        if (!d) {
            printf("Erro ao alocar memoria para Destino.\n");
            exit(1);
        }
        *d = criarDestino(novoId, genericPaises[novoId % 5], genericAtracoes[novoId % 5], "Generic", novoId * 500.0);
        SalvarDestino(d, novoId);
        free(d);
    }
}

void CriarBaseRoteiros(FILE *out, int tam) {
    Roteiro *r;
    Destino destinos[MAX_DESTINOS];
    int i, j;

    printf("Gerando a base de roteiros genéricos...\n");

    for (j = 0; j < MAX_DESTINOS; j++) {
        destinos[j] = criarDestino(j + 1, "Destino Generico", "Atracao Principal", "Tropical", (j + 1) * 200.0);
    }

    for (i = 0; i < tam; i++) {
        r = malloc(sizeof(Roteiro));
        if (!r) {
            printf("Erro ao alocar memoria para Roteiro.\n");
            exit(1);
        }

        fseek(out, 0, SEEK_END);
        long fileSize = ftell(out);
        int registroExistente = fileSize / sizeof(Roteiro);
        int novoId = registroExistente + 1;
        r->id = novoId;

        r->qtdDestinos = MAX_DESTINOS;
        for (j = 0; j < MAX_DESTINOS; j++) {
            r->destinos[j] = destinos[j].id;
        }

        int totalDias = 0;
        float totalCusto = 0;
        for (j = 0; j < MAX_DESTINOS; j++) {
            int dias = (i % 5) + 1;
            totalDias += dias;
            totalCusto += destinos[j].custoMedioEstadia * dias;
        }
        r->duracaoTotal = totalDias;
        r->custoTotal = totalCusto;

        r->vagasDisponiveis = 10;
        r->qtdTuristasAssociados = 0;

        SalvarRoteiro(r, novoId);
        free(r);
    }
}

// Função para gerar uma base de dados desordenada de Turistas
void GerarBaseDesordenadaTuristas(const char *filename, int quantidade) {
    FILE *fp = fopen(filename, "wb");  // Abre em modo de escrita, sobrescrevendo o arquivo existente
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    Turista *vetor = malloc(quantidade * sizeof(Turista));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para a base de turistas.\n");
        fclose(fp);
        return;
    }

    // Lista fixa de países para os países de interesse
    const char *paises[] = {"Pais1", "Pais2", "Pais3", "Pais4", "Pais5"};

    // Cria registros ordenados
    for (int i = 0; i < quantidade; i++) {
        vetor[i].id = i + 1;
        snprintf(vetor[i].nome, MAX_NOME, "Turista %d", i + 1);
        snprintf(vetor[i].cpf, 15, "000.000.000-%02d", i + 1);

        for (int j = 0; j < MAX_PAISES_INTERESSE; j++) {
            strncpy(vetor[i].paisesInteresse[j], paises[j % 5], MAX_NOME);
        }
        // Define um orçamento aleatório entre 1000 e 5000
        vetor[i].orcamento = 1000 + rand() % 4001;
    }

    // Realiza o shuffle no vetor (Fisher–Yates)
    for (int i = quantidade - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Turista temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }

    // Escreve o vetor desordenado no arquivo
    fwrite(vetor, sizeof(Turista), quantidade, fp);
    fclose(fp);
    free(vetor);
    printf("Base desordenada de Turistas gerada com sucesso (%d registros).\n", quantidade);
}

// Função para gerar uma base de dados desordenada de Destinos
void GerarBaseDesordenadaDestinos(const char *filename, int quantidade) {
    FILE *fp = fopen(filename, "wb");  // Abre em modo de escrita, sobrescrevendo o arquivo existente
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    Destino *vetor = malloc(quantidade * sizeof(Destino));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para a base de destinos.\n");
        fclose(fp);
        return;
    }

    // Arrays de dados de exemplo
    const char *paises[] = {"Brasil", "Estados Unidos", "Franca", "Japao", "Italia",
                              "Alemanha", "Australia", "Canada", "Espanha", "Portugal"};
    const char *atracoes[] = {"Atracao1", "Atracao2", "Atracao3", "Atracao4", "Atracao5",
                              "Atracao6", "Atracao7", "Atracao8", "Atracao9", "Atracao10"};
    const char *climas[] = {"Tropical", "Temperado", "Frio", "Mediterraneo", "Subtropical"};
    int numPaises = sizeof(paises) / sizeof(paises[0]);
    int numAtracoes = sizeof(atracoes) / sizeof(atracoes[0]);
    int numClimas = sizeof(climas) / sizeof(climas[0]);

    // Cria registros ordenados
    for (int i = 0; i < quantidade; i++) {
        vetor[i].id = i + 1;
        // Escolhe um país aleatório dentre os disponíveis
        int idxPais = rand() % numPaises;
        strncpy(vetor[i].nomePais, paises[idxPais], MAX_NOME);
        // Escolhe uma atração aleatória
        int idxAtracao = rand() % numAtracoes;
        strncpy(vetor[i].principalAtracao, atracoes[idxAtracao], MAX_ATRACOES);
        // Escolhe um clima aleatório
        int idxClima = rand() % numClimas;
        strncpy(vetor[i].clima, climas[idxClima], 20);
        // Define um custo médio aleatório entre 500 e 3000
        vetor[i].custoMedioEstadia = 500 + rand() % 2501;
    }

    // Shuffle no vetor
    for (int i = quantidade - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Destino temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }

    fwrite(vetor, sizeof(Destino), quantidade, fp);
    fclose(fp);
    free(vetor);
    printf("Base desordenada de Destinos gerada com sucesso (%d registros).\n", quantidade);
}
