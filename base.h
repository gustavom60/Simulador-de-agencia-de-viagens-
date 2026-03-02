#ifndef BASE_H
#define BASE_H

#include <stdio.h>

void CriarBaseTuristas(FILE *out, int tam);
void CriarBaseDestinos(FILE *out, int tam);
void CriarBaseRoteiros(FILE *out, int tam);
void GerarBaseDesordenadaTuristas(const char *filename, int quantidade);
void GerarBaseDesordenadaDestinos(const char *filename, int quantidade);

#endif
