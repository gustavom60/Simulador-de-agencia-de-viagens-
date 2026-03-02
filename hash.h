#ifndef HASH_H
#define HASH_H

#include "entidades.h"

#define TABLE_SIZE 101  // Tamanho da tabela (preferencialmente um número primo)

typedef struct {
    int status; // 0: vazio, 1: ocupado, 2: deletado
    Turista data;
} HashSlot;

// Protótipos das funções da Tabela Hash
void criarTabelaHash(const char *filename);
int hashInserirTurista(const char *filename, Turista t);
Turista *hashBuscarTurista(const char *filename, int id);
int hashRemoverTurista(const char *filename, int id);
void hashVisualizar(const char *filename);
void hashPreencherGenericos(const char *filename);

#endif
