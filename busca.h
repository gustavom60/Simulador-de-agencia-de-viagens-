#ifndef BUSCA_H
#define BUSCA_H

#include "entidades.h"

Turista *BuscaSequencialTurista(const char* filename, int id, int* execucoes, double* tempo);
Destino *BuscaSequencialDestino(const char* filename, int id, int* execucoes, double* tempo);
Roteiro *BuscaSequencialRoteiro(const char* filename, int id, int* execucoes, double* tempo);
Turista *BuscaBinariaTurista(const char* filename, int id, int* execucoes, double* tempo);
Destino *BuscaBinariaDestino(const char* filename, int id, int* execucoes, double* tempo);
Roteiro *BuscaBinariaRoteiro(const char* filename, int id, int* execucoes, double* tempo);
Turista *BuscaSequencialTuristaPorNome(const char* filename, const char* nomeBusca, int* execucoes, double* tempo);
Destino *BuscaSequencialDestinoPorNome(const char* filename, const char* nomeBusca, int* execucoes, double* tempo);

#endif
