#include <stdio.h>
#include "entidades.h"

// Salva um Turista inteiro (substituindo o existente, se necessário)
void SalvarTurista(Turista* turista, int id) {
    FILE *arqTurista = fopen("turistas.dat", "rb+");
    if (turista == NULL) {
        printf("Erro: Ponteiro nulo passado para SalvarTurista\n");
        return;
    }
    if (arqTurista == NULL) {
        arqTurista = fopen("turistas.dat", "wb+"); // Cria o arquivo se não existir
        if (arqTurista == NULL) {
            printf("Erro ao abrir o arquivo turistas.dat\n");
            return;
        }
    }

    // Posiciona o ponteiro no local correto (cada Turista tem um ID sequencial)
    fseek(arqTurista, (id - 1) * sizeof(Turista), SEEK_SET);
    fwrite(turista, sizeof(Turista), 1, arqTurista);
    fclose(arqTurista);
}

// Salva um Destino inteiro (substituindo o existente, se necessário)
void SalvarDestino(Destino* destino, int id) {
    FILE *arqDestino = fopen("destinos.dat", "rb+");
    if (destino == NULL) {
        printf("Erro: Ponteiro nulo passado para SalvarDestino\n");
        return;
    }
    if (arqDestino == NULL) {
        arqDestino = fopen("destinos.dat", "wb+"); // Cria o arquivo se não existir
        if (arqDestino == NULL) {
            printf("Erro ao abrir o arquivo destinos.dat\n");
            return;
        }
    }

    fseek(arqDestino, (id - 1) * sizeof(Destino), SEEK_SET);
    fwrite(destino, sizeof(Destino), 1, arqDestino);
    fclose(arqDestino);
}

// Salva um Roteiro inteiro (substituindo o existente, se necessário)
void SalvarRoteiro(Roteiro* roteiro, int id) {
    FILE *arqRoteiro = fopen("roteiros.dat", "rb+");
    if (roteiro == NULL) {
        printf("Erro: Ponteiro nulo passado para SalvarRoteiro\n");
        return;
    }
    if (arqRoteiro == NULL) {
        arqRoteiro = fopen("roteiros.dat", "wb+"); // Cria o arquivo se não existir
        if (arqRoteiro == NULL) {
            printf("Erro ao abrir o arquivo roteiros.dat\n");
            return;
        }
    }

    fseek(arqRoteiro, (id - 1) * sizeof(Roteiro), SEEK_SET);
    fwrite(roteiro, sizeof(Roteiro), 1, arqRoteiro);
    fclose(arqRoteiro);
}
