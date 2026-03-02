#include <stdio.h>
#include <stdbool.h>
#include "imprimir.h"
#include "entidades.h"

void ImprimirBaseTuristas(const char *filename) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de turistas para leitura.\n");
        return;
    }
    Turista t;
    printf("\n--- Turistas cadastrados: ---\n");
    while(fread(&t, sizeof(Turista), 1, arq)) {
        printf("\nID: %d\n Nome: %s\n CPF: %s\n Orcamento: %.2f\n", t.id, t.nome, t.cpf, t.orcamento);
        printf(" Paises de interesse:\n");
        for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
            printf("  %d: %s\n", i + 1, t.paisesInteresse[i]);
        }
    }
    fclose(arq);
}


// Funcao para listar os Destinos
void ImprimirBaseDestinos(const char *filename) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de destinos para leitura.\n");
        return;
    }
    Destino d;
    printf("\n--- Destinos cadastrados: ---\n");
    while(fread(&d, sizeof(Destino), 1, arq)) {
        printf("\nID: %d\n Pais: %s\n Atracao: %s\n Clima: %s\n Custo medio: %.2f\n", d.id, d.nomePais, d.principalAtracao, d.clima, d.custoMedioEstadia);
    }
    fclose(arq);
}

void ImprimirBaseRoteiros(const char *filename, FILE *turistas) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de roteiros para leitura.\n");
        return;
    }
    Roteiro r;
    Turista t;
    printf("\n--- Roteiros cadastrados: ---\n");
    while (fread(&r, sizeof(Roteiro), 1, arq)) {
        printf("\nID: %d\n", r.id);
        printf("Custo Total: %.2f\n", r.custoTotal);
        printf("Duracao Total: %d dias\n", r.duracaoTotal);
        printf("Vagas Disponiveis: %d\n", r.vagasDisponiveis);
        printf("Destinos: ");
        // Para cada destino, abrimos o arquivo de destinos e buscamos o nome do país
        for (int i = 0; i < r.qtdDestinos; i++) {
            int idDestino = r.destinos[i];
            FILE *arqDestinos = fopen("destinos.dat", "rb");
            if (arqDestinos != NULL) {
                Destino d;
                bool encontrado = false;
                while (fread(&d, sizeof(Destino), 1, arqDestinos)) {
                    if (d.id == idDestino) {
                        printf("\n - %s", d.nomePais);
                        encontrado = true;
                        break;
                    }
                }
                fclose(arqDestinos);
                if (!encontrado) {
                    printf("Desconhecido ");
                }
            } else {
                printf("Erro ao abrir destinos.dat ");
            }
        }
        printf("\n");
        printf("Turistas Associados:\n");
        if (r.qtdTuristasAssociados == 0) {
            printf("  Nenhum turista associado.\n");
        } else {
            FILE *arqTuristas = fopen("turistas.dat", "rb");
            if (arqTuristas != NULL) {
                for (int i = 0; i < r.qtdTuristasAssociados; i++) {
                    Turista t;
                    bool turistaEncontrado = false;
                    rewind(arqTuristas);
                    while (fread(&t, sizeof(Turista), 1, arqTuristas)) {
                        if (t.id == r.turistasAssociados[i]) {
                            printf("  - %s (ID: %d)\n", t.nome, t.id);
                            turistaEncontrado = true;
                            break;
                        }
                    }
                    if (!turistaEncontrado) {
                        printf("  - [Turista Desconhecido]\n");
                    }
                }
                fclose(arqTuristas);
            } else {
                printf("Erro ao abrir turistas.dat\n");
            }
        }
        printf("\n");
    }
    fclose(arq);
}

void ImprimirTurista(const char *filename, Turista *t) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de turistas para leitura.\n");
        return;
    }
    printf("\nID: %d\n Nome: %s\n CPF: %s\n Orcamento: %.2f\n", t->id, t->nome, t->cpf, t->orcamento);
    printf(" Paises de interesse:\n");
    for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
        printf("  %d: %s\n", i + 1, t->paisesInteresse[i]);
    }
}

void ImprimirDestino(const char *filename, Destino *d) {
    FILE *arq = fopen(filename, "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de destinos para leitura.\n");
        return;
    }
    printf("\nID: %d\n Pais: %s\n Atracao: %s\n Clima: %s\n Custo medio: %.2f\n", d->id, d->nomePais, d->principalAtracao, d->clima, d->custoMedioEstadia);
}

void ImprimirRoteiro(const char *filename, int idRoteiro) {
    FILE *arq = fopen(filename, "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de roteiros para leitura.\n");
        return;
    }

    Roteiro r;
    bool encontrado = false;

    // Busca o roteiro pelo ID
    while (fread(&r, sizeof(Roteiro), 1, arq)) {
        if (r.id == idRoteiro) {
            encontrado = true;
            break;
        }
    }
    fclose(arq);

    if (!encontrado) {
        printf("Roteiro com ID %d nao encontrado.\n", idRoteiro);
        return;
    }

    // Exibe informações do roteiro encontrado
    printf("\n--- Roteiro %d ---\n", r.id);
    printf("Custo Total: %.2f\n", r.custoTotal);
    printf("Duracao Total: %d dias\n", r.duracaoTotal);
    printf("Vagas Disponiveis: %d\n", r.vagasDisponiveis);

    // Exibir destinos
    printf("Destinos:\n");
    FILE *arqDestinos = fopen("destinos.dat", "rb");
    if (arqDestinos != NULL) {
        for (int i = 0; i < r.qtdDestinos; i++) {
            Destino d;
            bool destinoEncontrado = false;
            rewind(arqDestinos);  // Volta ao início do arquivo para buscar o destino correto
            while (fread(&d, sizeof(Destino), 1, arqDestinos)) {
                if (d.id == r.destinos[i]) {
                    printf("  - %s\n", d.nomePais);
                    destinoEncontrado = true;
                    break;
                }
            }
            if (!destinoEncontrado) {
                printf("  - [Destino Desconhecido]\n");
            }
        }
        fclose(arqDestinos);
    } else {
        printf("Erro ao abrir destinos.dat\n");
    }

    // Exibir turistas associados
    printf("Turistas Associados:\n");
    if (r.qtdTuristasAssociados == 0) {
        printf("  Nenhum turista associado.\n");
    } else {
        FILE *arqTuristas = fopen("turistas.dat", "rb");
        if (arqTuristas != NULL) {
            for (int i = 0; i < r.qtdTuristasAssociados; i++) {
                Turista t;
                bool turistaEncontrado = false;
                rewind(arqTuristas);
                while (fread(&t, sizeof(Turista), 1, arqTuristas)) {
                    if (t.id == r.turistasAssociados[i]) {
                        printf("  - %s (ID: %d)\n", t.nome, t.id);
                        turistaEncontrado = true;
                        break;
                    }
                }
                if (!turistaEncontrado) {
                    printf("  - [Turista Desconhecido]\n");
                }
            }
            fclose(arqTuristas);
        } else {
            printf("Erro ao abrir turistas.dat\n");
        }
    }
}
