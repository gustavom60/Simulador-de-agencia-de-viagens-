#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>

#define MAX_NOME 100
#define MAX_ATRACOES 100
#define MAX_DESTINOS 10
#define MAX_PAISES_INTERESSE 5
#define MAX_TURISTAS_ROTEIRO 10

typedef struct {
    int id;
    char nome[MAX_NOME];
    char cpf[15];
    char paisesInteresse[MAX_PAISES_INTERESSE][MAX_NOME];
    float orcamento;
} Turista;

typedef struct {
    int id;
    char nomePais[MAX_NOME];
    char principalAtracao[MAX_NOME];
    char clima[MAX_NOME];
    float custoMedioEstadia; // custo medio de estadia
} Destino;

typedef struct {
    int id;
    int destinos[MAX_DESTINOS];  // IDs dos destinos do roteiro
    int qtdDestinos;
    float custoTotal;
    int duracaoTotal;          // soma dos dias em cada destino
    int vagasDisponiveis;      // vagas disponíveis no roteiro
    int turistasAssociados[MAX_TURISTAS_ROTEIRO]; // IDs dos turistas associados
    int qtdTuristasAssociados;
} Roteiro;

Turista criarTurista(int id, char nome[], char cpf[], char paisesInteresse[][MAX_NOME], float orcamento);
Destino criarDestino(int id, char nomePais[], char principalAtracao[], char clima[], float custoMedioEstadia);
void CriarRoteiro(FILE *roteiros, FILE *destinos);

#endif
