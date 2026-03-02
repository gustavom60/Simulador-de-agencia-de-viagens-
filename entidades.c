#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "entidades.h"
#include "busca.h"
#include "extras.h"
#include "salvar_entidades.h"

Turista criarTurista(int id, char nome[], char cpf[], char paisesInteresse[][MAX_NOME], float orcamento) {
    Turista t;
    t.id = id;                                  // Define o ID do turista
    strncpy(t.nome, nome, MAX_NOME);      // Copia o nome para a estrutura
    strncpy(t.cpf, cpf, 15);              // Copia o CPF para a estrutura
    t.orcamento = orcamento;                    // Define o orçamento do turista

    // Copia a lista de países de interesse
    for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
        strncpy(t.paisesInteresse[i], paisesInteresse[i], MAX_NOME);
    }

    return t;
}

Destino criarDestino(int id, char nomePais[], char principalAtracao[], char clima[], float custoMedioEstadia) {
    Destino d;
    d.id = id;                                                          // Define o ID do destino
    strncpy(d.nomePais, nomePais, MAX_NOME);                      // Copia o nome do país para a estrutura
    strncpy(d.principalAtracao, principalAtracao, MAX_ATRACOES);  // Copia a principal atração
    strncpy(d.clima, clima, 20);                                  // Copia o clima do destino
    d.custoMedioEstadia = custoMedioEstadia;                            // Define o custo médio da estadia

    return d;
}

void CriarRoteiro(FILE *roteiros, FILE *destinos) {
    Roteiro r;
    Destino d;
    float custoTotal = 0;
    int duracaoTotal = 0;

    // Define o id do roteiro com base no total já existente
    fseek(roteiros, 0, SEEK_END);
    long fileSize = ftell(roteiros);
    int total = fileSize / sizeof(Roteiro);
    r.id = total + 1;
    r.qtdDestinos = 0;
    r.qtdTuristasAssociados = 0;
    r.vagasDisponiveis = MAX_TURISTAS_ROTEIRO; // Definindo 10 vagas iniciais

    // Exibe a lista de destinos disponíveis
    printf("\n--- Lista de destinos disponiveis ---\n");
    fseek(destinos, 0, SEEK_SET);
    while (fread(&d, sizeof(Destino), 1, destinos)) {
        printf("ID: %d - Pais: %s - Custo medio: %.2f\n", d.id, d.nomePais, d.custoMedioEstadia);
    }

    printf("Quantos destinos deseja adicionar ao roteiro? (Max: %d): ", MAX_DESTINOS);
    scanf("%d", &r.qtdDestinos);
    LimpaBuffer();

    for (int i = 0; i < r.qtdDestinos; i++) {
        int id;
        int execucoes;
        double tempo;
        printf("Digite o ID do destino: ");
        scanf("%d", &id);
        LimpaBuffer();
        Destino *destino = BuscaBinariaDestino("destinos.dat", id, &execucoes, &tempo);
        if (destino != NULL) {
            r.destinos[i] = destino->id;
            int dias;
            printf("Quantos dias deseja passar em %s? ", destino->nomePais);
            scanf("%d", &dias);
            LimpaBuffer();
            duracaoTotal += dias;
            custoTotal += destino->custoMedioEstadia * dias;

            free(destino);
        } else {
            printf("Destino com ID %d nao encontrado. Tente novamente.\n", id);
            i--; // repete a iteração para este destino
        }
    }

    r.custoTotal = custoTotal;
    r.duracaoTotal = duracaoTotal;

    SalvarRoteiro(&r, r.id);
    printf("Roteiro criado com sucesso!\n");
}