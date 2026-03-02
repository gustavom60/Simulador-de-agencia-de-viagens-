#ifndef EXTRAS_H
#define EXTRAS_H

#define MAX_TURISTAS_EXEMPLO 50
#define MAX_DESTINOS_EXEMPLO 50

#include "entidades.h"
#include <stdbool.h>

void LimpaBuffer(void);
bool TuristaTemInteresse(Turista t, FILE *destinos, Roteiro r);
void AssociarTuristaARoteiro(FILE *roteiros, FILE *turistas, FILE *destinos);
int arquivoExiste(const char *filename);

#endif //EXTRAS_H
