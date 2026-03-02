#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "entidades.h"
#include "busca.h"

//
// Funções de busca sequencial
//

Turista *BuscaSequencialTurista(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Turista);
    rewind(arq);

    clock_t start = clock();
    Turista t;
    *execucoes = 0;
    Turista *found = NULL;
    while(fread(&t, sizeof(Turista), 1, arq)) {
        (*execucoes)++;
        if(t.id == id) {
            found = malloc(sizeof(Turista));
            if(found != NULL)
                *found = t;
            break;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if(logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Sequencial\nEntidade: Turista\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

Destino *BuscaSequencialDestino(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Destino);
    rewind(arq);

    clock_t start = clock();
    Destino d;
    *execucoes = 0;
    Destino *found = NULL;
    while(fread(&d, sizeof(Destino), 1, arq)) {
        (*execucoes)++;
        if(d.id == id) {
            found = malloc(sizeof(Destino));
            if(found != NULL)
                *found = d;
            break;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if(logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Sequencial\nEntidade: Destino\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

Roteiro *BuscaSequencialRoteiro(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Roteiro);
    rewind(arq);

    clock_t start = clock();
    Roteiro r;
    *execucoes = 0;
    Roteiro *found = NULL;
    while(fread(&r, sizeof(Roteiro), 1, arq)) {
        (*execucoes)++;
        if(r.id == id) {
            found = malloc(sizeof(Roteiro));
            if(found != NULL)
                *found = r;
            break;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if(logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Sequencial\nEntidade: Roteiro\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

//
// Funções de busca binária
//

Turista *BuscaBinariaTurista(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Turista);
    rewind(arq);

    int left = 0, right = total - 1, mid;
    Turista t;
    *execucoes = 0;
    Turista *found = NULL;

    clock_t start = clock();
    while (left <= right) {
        mid = (left + right) / 2;
        fseek(arq, mid * sizeof(Turista), SEEK_SET);
        if (fread(&t, sizeof(Turista), 1, arq) != 1)
            break;
        (*execucoes)++;
        if (t.id == id) {
            found = malloc(sizeof(Turista));
            if (found != NULL)
                *found = t;
            break;
        } else if (t.id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Binaria\nEntidade: Turista\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

Destino *BuscaBinariaDestino(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Destino);
    rewind(arq);

    int left = 0, right = total - 1, mid;
    Destino d;
    *execucoes = 0;
    Destino *found = NULL;

    clock_t start = clock();
    while (left <= right) {
        mid = (left + right) / 2;
        fseek(arq, mid * sizeof(Destino), SEEK_SET);
        if (fread(&d, sizeof(Destino), 1, arq) != 1)
            break;
        (*execucoes)++;
        if (d.id == id) {
            found = malloc(sizeof(Destino));
            if (found != NULL)
                *found = d;
            break;
        } else if (d.id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Binaria\nEntidade: Destino\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

Roteiro *BuscaBinariaRoteiro(const char* filename, int id, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Roteiro);
    rewind(arq);

    int left = 0, right = total - 1, mid;
    Roteiro r;
    *execucoes = 0;
    Roteiro *found = NULL;

    clock_t start = clock();
    while (left <= right) {
        mid = (left + right) / 2;
        fseek(arq, mid * sizeof(Roteiro), SEEK_SET);
        if (fread(&r, sizeof(Roteiro), 1, arq) != 1)
            break;
        (*execucoes)++;
        if (r.id == id) {
            found = malloc(sizeof(Roteiro));
            if (found != NULL)
                *found = r;
            break;
        } else if (r.id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Binaria\nEntidade: Roteiro\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nID: %d\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, id, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

//
// Buscas Sequenciais pelo nome da entidade
//

Turista *BuscaSequencialTuristaPorNome(const char* filename, const char* nomeBusca, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Turista);
    rewind(arq);

    clock_t start = clock();
    Turista t;
    *execucoes = 0;
    Turista *found = NULL;
    while (fread(&t, sizeof(Turista), 1, arq)) {
        (*execucoes)++;
        if (strcmp(t.nome, nomeBusca) == 0) {
            found = malloc(sizeof(Turista));
            if (found != NULL)
                *found = t;
            break;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Sequencial\nEntidade: Turista\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nNome: %s\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, nomeBusca, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

Destino *BuscaSequencialDestinoPorNome(const char* filename, const char* nomeBusca, int* execucoes, double* tempo) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return NULL;
    }
    // Determina o total de registros e o tamanho total em bytes
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    int total = fileSize / sizeof(Destino);
    rewind(arq);

    clock_t start = clock();
    Destino d;
    *execucoes = 0;
    Destino *found = NULL;
    while (fread(&d, sizeof(Destino), 1, arq)) {
        (*execucoes)++;
        if (strcmp(d.nomePais, nomeBusca) == 0) {
            found = malloc(sizeof(Destino));
            if (found != NULL)
                *found = d;
            break;
        }
    }
    clock_t end = clock();
    *tempo = (double)(end - start) / CLOCKS_PER_SEC;
    fclose(arq);

    // Salva os dados da busca no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Busca: Sequencial\nEntidade: Destino\nQuantidade: %d entidades armazenadas\nTamanho total do arquivo: %ld bytes\nNome: %s\nQuantidade de execucoes: %d vezes\nTempo: %.6f seconds\n\n",
                total, fileSize, nomeBusca, *execucoes, *tempo);
        fclose(logFile);
    }
    return found;
}

