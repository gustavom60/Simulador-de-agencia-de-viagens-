#ifndef IMPRIMIR_H
#define IMPRIMIR_H

#include "entidades.h"

void ImprimirBaseTuristas(const char *filename);
void ImprimirBaseDestinos(const char *filename);
void ImprimirBaseRoteiros(const char *filename, FILE *turistas);
void ImprimirTurista(const char *filename, Turista *t);
void ImprimirDestino(const char *filename, Destino *d);
void ImprimirRoteiro(const char *filename, int idRoteiro);

#endif //IMPRIMIR_H
