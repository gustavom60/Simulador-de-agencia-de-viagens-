#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "extras.h"
#include "busca.h"
#include "entidades.h"
#include "salvar_entidades.h"

// Funcao que limpa o buffer de entrada
void LimpaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Verifica se o turista tem interesse em pelo menos um dos países do roteiro
bool TuristaTemInteresse(Turista t, FILE *destinos, Roteiro r) {
    Destino d;
    for (int i = 0; i < r.qtdDestinos; i++) {
        fseek(destinos, 0, SEEK_SET);
        while (fread(&d, sizeof(Destino), 1, destinos)) {
            if (d.id == r.destinos[i]) {
                for (int j = 0; j < MAX_PAISES_INTERESSE; j++) {
                    if (strcmp(t.paisesInteresse[j], d.nomePais) == 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void AssociarTuristaARoteiro(FILE *roteiros, FILE *turistas, FILE *destinos) {
    int idTurista, idRoteiro;
    int execucoes;
    double tempo;

    // Exibe os turistas disponíveis
    printf("\n--- Lista de turistas disponiveis ---\n");
    Turista tempTurista;
    fseek(turistas, 0, SEEK_SET);
    while (fread(&tempTurista, sizeof(Turista), 1, turistas)) {
        printf("ID: %d - Nome: %s - Orcamento: %.2f\n", tempTurista.id, tempTurista.nome, tempTurista.orcamento);
    }

    printf("Digite o ID do turista que deseja associar: ");
    scanf("%d", &idTurista);
    LimpaBuffer();

    // Exibe os roteiros disponíveis
    printf("\n--- Lista de roteiros disponiveis ---\n");
    Roteiro tempRoteiro;
    fseek(roteiros, 0, SEEK_SET);
    while (fread(&tempRoteiro, sizeof(Roteiro), 1, roteiros)) {
        // Aqui você pode utilizar sua função de impressão ou exibir informações básicas
        printf("Roteiro ID: %d, Custo Total: %.2f, Vagas Disponiveis: %d\n",
               tempRoteiro.id, tempRoteiro.custoTotal, tempRoteiro.vagasDisponiveis);
    }

    printf("Digite o ID do roteiro para associar ao turista: ");
    scanf("%d", &idRoteiro);
    LimpaBuffer();

    // Busca o turista e o roteiro via busca binária
    Turista *turista = BuscaBinariaTurista("turistas.dat", idTurista, &execucoes, &tempo);
    if (turista == NULL) {
        printf("Turista nao encontrado!\n");
        return;
    }

    Roteiro *roteiro = BuscaBinariaRoteiro("roteiros.dat", idRoteiro, &execucoes, &tempo);
    if (roteiro == NULL) {
        printf("Roteiro nao encontrado!\n");
        free(turista);
        return;
    }

    // Verifica se o turista tem interesse em pelo menos um dos países do roteiro
    if (!TuristaTemInteresse(*turista, destinos, *roteiro)) {
        printf("O turista nao tem interesse em nenhum dos paises deste roteiro!\n");
        free(turista);
        free(roteiro);
        return;
    }

    // Verifica se o orçamento do turista é suficiente
    if (turista->orcamento < roteiro->custoTotal) {
        printf("Orcamento insuficiente para este roteiro!\n");
        free(turista);
        free(roteiro);
        return;
    }

    // Verifica se há vagas disponíveis
    if (roteiro->vagasDisponiveis <= 0) {
        printf("Nao ha vagas disponiveis neste roteiro!\n");
        free(turista);
        free(roteiro);
        return;
    }

    // Atualiza o roteiro para associar o turista
    roteiro->turistasAssociados[roteiro->qtdTuristasAssociados] = turista->id;
    roteiro->qtdTuristasAssociados++;
    roteiro->vagasDisponiveis--;

    // Salva o roteiro atualizado utilizando a função SalvarRoteiro
    SalvarRoteiro(roteiro, idRoteiro);

    printf("Turista %s associado ao roteiro %d com sucesso!\n", turista->nome, roteiro->id);

    free(turista);
    free(roteiro);
}

int arquivoExiste(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}