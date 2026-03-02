#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#include <time.h>

//retorna o índice baseado no ID
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void criarTabelaHash(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Erro ao criar tabela hash em %s\n", filename);
        return;
    }
    HashSlot slot;
    slot.status = 0; // vazio
    for (int i = 0; i < TABLE_SIZE; i++) {
        fwrite(&slot, sizeof(HashSlot), 1, fp);
    }
    fclose(fp);
    printf("Tabela hash criada com sucesso.\n");
}

// Insere um Turista na tabela hash usando sondagem linear
// Retorna a posição inserida ou -1 em caso de falha
int hashInserirTurista(const char *filename, Turista t) {
    FILE *fp = fopen(filename, "rb+");
    if (!fp) {
        printf("Erro ao abrir tabela hash em %s\n", filename);
        return -1;
    }
    int index = hashFunction(t.id);
    HashSlot slot;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (index + i) % TABLE_SIZE;
        fseek(fp, pos * sizeof(HashSlot), SEEK_SET);
        fread(&slot, sizeof(HashSlot), 1, fp);
        // Se o slot estiver ocupado, verifica se o ID já existe
        if (slot.status == 1 && slot.data.id == t.id) {
            printf("Erro: ID %d ja existe na tabela hash.\n", t.id);
            fclose(fp);
            return -1;
        }
        // Se o slot estiver vazio ou deletado, insere
        if (slot.status != 1) {
            slot.status = 1;
            slot.data = t;
            fseek(fp, pos * sizeof(HashSlot), SEEK_SET);
            fwrite(&slot, sizeof(HashSlot), 1, fp);
            fclose(fp);
            return pos;
        }
    }
    fclose(fp);
    printf("Tabela hash cheia. Insercao falhou.\n");
    return -1;
}

// Busca um Turista na tabela hash usando sondagem linear
Turista *hashBuscarTurista(const char *filename, int id) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Erro ao abrir tabela hash em %s\n", filename);
        return NULL;
    }
    int index = hashFunction(id);
    HashSlot slot;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (index + i) % TABLE_SIZE;
        fseek(fp, pos * sizeof(HashSlot), SEEK_SET);
        fread(&slot, sizeof(HashSlot), 1, fp);
        if (slot.status == 0) { // posição vazia: encerra busca
            fclose(fp);
            return NULL;
        }
        if (slot.status == 1 && slot.data.id == id) {
            Turista *result = malloc(sizeof(Turista));
            if (result)
                *result = slot.data;
            fclose(fp);
            return result;
        }
    }
    fclose(fp);
    return NULL;
}

// Remove um Turista da tabela hash (marca a posição como deletada)
int hashRemoverTurista(const char *filename, int id) {
    FILE *fp = fopen(filename, "rb+");
    if (!fp) {
        printf("Erro ao abrir tabela hash em %s\n", filename);
        return -1;
    }
    int index = hashFunction(id);
    HashSlot slot;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (index + i) % TABLE_SIZE;
        fseek(fp, pos * sizeof(HashSlot), SEEK_SET);
        fread(&slot, sizeof(HashSlot), 1, fp);
        if (slot.status == 0) { // não encontrado
            fclose(fp);
            return -1;
        }
        if (slot.status == 1 && slot.data.id == id) {
            slot.status = 2; // marca como deletado
            fseek(fp, pos * sizeof(HashSlot), SEEK_SET);
            fwrite(&slot, sizeof(HashSlot), 1, fp);
            fclose(fp);
            return pos;
        }
    }
    fclose(fp);
    return -1;
}

// Visualiza a tabela hash: imprime o índice, status e, se ocupado, o ID do turista
void hashVisualizar(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Erro ao abrir tabela hash para visualizacao.\n");
        return;
    }
    HashSlot slot;
    printf("\n--- Visualizacao da Tabela Hash ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        fseek(fp, i * sizeof(HashSlot), SEEK_SET);
        fread(&slot, sizeof(HashSlot), 1, fp);
        printf("Posicao %3d: ", i);
        if (slot.status == 0)
            printf("Vazio\n");
        else if (slot.status == 1)
            printf("Ocupado - ID: %d, Nome: %s\n", slot.data.id, slot.data.nome);
        else if (slot.status == 2)
            printf("Deletado\n");
    }
    fclose(fp);
}

// Preenche alguns slots com dados genéricos para demonstração
void hashPreencherGenericos(const char *filename) {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    Turista genericos[60];

    for (int i = 0; i < 60; i++) {
        genericos[i].id = rand() % 9999 + 1; // ID aleatório entre 1 e 9999
        snprintf(genericos[i].nome, MAX_NOME, "GenTurista%d", i + 1);
        snprintf(genericos[i].cpf, 15, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
        genericos[i].orcamento = (rand() % 29501) + 500.0; // Entre 500 e 30000

        for (int j = 0; j < MAX_PAISES_INTERESSE; j++) {
            snprintf(genericos[i].paisesInteresse[j], MAX_NOME, "Pais%d", rand() % 50 + 1);
        }

        hashInserirTurista(filename, genericos[i]);
    }
    printf("Tabela hash pre-preenchida com dados gerados aleatoriamente.\n");
}

