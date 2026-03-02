#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editar.h"
#include "inserir.h"
#include "imprimir.h"
#include "extras.h"
#include "busca.h"
#include "base.h"
#include "bubble.h"
#include "hash.h"
#include "ordenacao_ext.h"

int main() {

    FILE *arqTuristas, *arqDestinos, *arqRoteiros;
    int op, opSub;
    char filenameTuristas[] = "turistas.dat";
    char filenameDestinos[] = "destinos.dat";
    char filenameRoteiros[] = "roteiros.dat";
    char filenameHash[] = "hashTuristas.dat";

    // Abre ou cria o arquivo de turistas em modo de leitura e atualização binária
    arqTuristas = fopen(filenameTuristas, "rb+");
    if (arqTuristas == NULL) {
        arqTuristas = fopen(filenameTuristas, "wb+");
        if (arqTuristas == NULL) {
            printf("Erro ao criar o arquivo de turistas.\n");
            exit(1);
        }
    }

    // Abre ou cria o arquivo de destinos
    arqDestinos = fopen(filenameDestinos, "rb+");
    if (arqDestinos == NULL) {
        arqDestinos = fopen(filenameDestinos, "wb+");
        if (arqDestinos == NULL) {
            printf("Erro ao criar o arquivo de destinos.\n");
            exit(1);
        }
    }

    // Abre ou cria o arquivo de roteiros
    arqRoteiros = fopen(filenameRoteiros, "rb+");
    if (arqRoteiros == NULL) {
        arqRoteiros = fopen(filenameRoteiros, "wb+");
        if (arqRoteiros == NULL) {
            printf("Erro ao criar o arquivo de roteiros.\n");
            exit(1);
        }
    }

    // Se os arquivos estiverem vazios, insere os dados de exemplo com 50 registros reais.
    fseek(arqTuristas, 0, SEEK_END);
    if (ftell(arqTuristas) == 0) {
        InserirDadosExemploTuristas(arqTuristas);
    }
    fseek(arqDestinos, 0, SEEK_END);
    if (ftell(arqDestinos) == 0) {
        InserirDadosExemploDestinos(arqDestinos);
    }

    // Inicialização da tabela hash:
    if (!arquivoExiste(filenameHash)) {
        criarTabelaHash(filenameHash);
        hashPreencherGenericos(filenameHash);
    }

    // Menu interativo principal
    do {
        printf("\n===== Menu Principal: =====\n");
        printf("1. Inserir\n");
        printf("2. Listar\n");
        printf("3. Roteiros\n");
        printf("4. Editar\n");
        printf("5. Buscar\n");
        printf("6. Base Aleatoria\n");
        printf("7. Tabela Hash\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);
        LimpaBuffer();  // Limpa o buffer de entrada

        switch(op) {
            case 1:  // Inserir submenu
                do {
                    printf("\n--- Menu Inserir ---\n");
                    printf("1. Inserir novo Turista\n");
                    printf("2. Inserir novo Destino\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opSub);
                    LimpaBuffer();
                    switch(opSub) {
                        case 1:
                            InserirTuristaInterativo(arqTuristas, arqDestinos);
                            break;
                        case 2:
                            InserirDestinoInterativo(arqDestinos);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opSub != 0);
                break;
            case 2:  // Listar submenu
                do {
                    printf("\n--- Menu Listar ---\n");
                    printf("1. Listar Turistas\n");
                    printf("2. Listar Destinos\n");
                    printf("3. Listar Roteiros\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opSub);
                    LimpaBuffer();
                    switch(opSub) {
                        case 1:
                            ImprimirBaseTuristas(filenameTuristas);
                            break;
                        case 2:
                            ImprimirBaseDestinos(filenameDestinos);
                            break;
                        case 3:
                            ImprimirBaseRoteiros(filenameRoteiros, arqTuristas);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opSub != 0);
                break;
            case 3:  // Roteiros submenu
                do {
                    printf("\n--- Menu Roteiros ---\n");
                    printf("1. Criar novo Roteiro\n");
                    printf("2. Associar Turista a um Roteiro\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opSub);
                    LimpaBuffer();
                    switch(opSub) {
                        case 1:
                            CriarRoteiro(arqRoteiros, arqDestinos);
                            break;
                        case 2:
                            AssociarTuristaARoteiro(arqRoteiros, arqTuristas, arqDestinos);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opSub != 0);
                break;
            case 4:  // Editar submenu
                do {
                    printf("\n--- Menu Editar ---\n");
                    printf("1. Editar Turista\n");
                    printf("2. Editar Destino\n");
                    printf("3. Editar Roteiro\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opSub);
                    LimpaBuffer();
                    switch(opSub) {
                        case 1:
                            EditarTurista(filenameTuristas, arqDestinos);
                            break;
                        case 2:
                            EditarDestino(filenameDestinos);
                            break;
                        case 3:
                            EditarRoteiro(filenameRoteiros);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opSub != 0);
                break;
            case 5:   // Buscar submenu
                do {
                    printf("\n--- Menu Buscar ---\n");
                    printf("1. Buscar Turista\n");
                    printf("2. Buscar Destino\n");
                    printf("3. Buscar Roteiro\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opSub);
                    LimpaBuffer();
                    switch(opSub) {
                        case 1: {
                            int opBuscaTurista;
                            printf("\nBuscar Turista:\n");
                            printf("1. Por ID\n");
                            printf("2. Por Nome\n");
                            printf("Escolha uma opcao: ");
                            scanf("%d", &opBuscaTurista);
                            LimpaBuffer();
                            if (opBuscaTurista == 1) {
                                int id;
                                int execucoes;
                                double tempo;
                                printf("Digite o ID do turista: ");
                                scanf("%d", &id);
                                LimpaBuffer();
                                Turista *turista = BuscaBinariaTurista(filenameTuristas, id, &execucoes, &tempo);
                                if (turista != NULL) {
                                    printf("Turista encontrado:\n");
                                    ImprimirTurista(filenameTuristas, turista);
                                    printf("Busca realizada em %.6f seconds, com %d execucoes.\n", tempo, execucoes);
                                    free(turista);
                                } else {
                                    printf("Turista com ID %d nao encontrado.\n", id);
                                }
                            } else if (opBuscaTurista == 2) {
                                char nomeBusca[MAX_NOME];
                                int execucoes;
                                double tempo;
                                printf("Digite o nome do turista a buscar: ");
                                fgets(nomeBusca, MAX_NOME, stdin);
                                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                                Turista *turista = BuscaSequencialTuristaPorNome(filenameTuristas, nomeBusca, &execucoes, &tempo);
                                if (turista != NULL) {
                                    printf("Turista encontrado:\n");
                                    ImprimirTurista(filenameTuristas, turista);
                                    printf("Busca realizada em %.6f seconds, com %d execucoes.\n", tempo, execucoes);
                                    free(turista);
                                } else {
                                    printf("Nenhum turista encontrado com o nome '%s'.\n", nomeBusca);
                                }
                            } else {
                                printf("Opcao invalida.\n");
                            }
                        } break;
                        case 2: {
                            int opBuscaDestino;
                            printf("\nBuscar Destino:\n");
                            printf("1. Por ID\n");
                            printf("2. Por Nome\n");
                            printf("Escolha uma opcao: ");
                            scanf("%d", &opBuscaDestino);
                            LimpaBuffer();
                            if (opBuscaDestino == 1) {
                                int id;
                                int execucoes;
                                double tempo;
                                printf("Digite o ID do destino: ");
                                scanf("%d", &id);
                                LimpaBuffer();
                                Destino *destino = BuscaBinariaDestino(filenameDestinos, id, &execucoes, &tempo);
                                if (destino != NULL) {
                                    printf("Destino encontrado:\n");
                                    ImprimirDestino(filenameDestinos, destino);
                                    printf("Busca realizada em %.6f seconds, com %d execucoes.\n", tempo, execucoes);
                                    free(destino);
                                } else {
                                    printf("Destino com ID %d nao encontrado.\n", id);
                                }
                            } else if (opBuscaDestino == 2) {
                                char nomeBusca[MAX_NOME];
                                int execucoes;
                                double tempo;
                                printf("Digite o nome do pais a buscar: ");
                                fgets(nomeBusca, MAX_NOME, stdin);
                                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                                Destino *destino = BuscaSequencialDestinoPorNome(filenameDestinos, nomeBusca, &execucoes, &tempo);
                                if (destino != NULL) {
                                    printf("Destino encontrado:\n");
                                    ImprimirDestino(filenameDestinos, destino);
                                    printf("Busca realizada em %.6f seconds, com %d execucoes.\n", tempo, execucoes);
                                    free(destino);
                                } else {
                                    printf("Nenhum destino encontrado com o nome '%s'.\n", nomeBusca);
                                }
                            } else {
                                printf("Opcao invalida.\n");
                            }
                        } break;
                        case 3: {
                            int id;
                            int execucoes;
                            double tempo;
                            printf("Digite o ID do roteiro: ");
                            scanf("%d", &id);
                            LimpaBuffer();
                            Roteiro *roteiro = BuscaBinariaRoteiro(filenameRoteiros, id, &execucoes, &tempo);
                            if (roteiro != NULL) {
                                printf("Roteiro encontrado:\n");
                                ImprimirRoteiro(filenameRoteiros, id);
                                printf("Quantidade de execucoes: %d vezes, Tempo: %.6f seconds\n", execucoes, tempo);
                                free(roteiro);
                            } else {
                                printf("Roteiro com ID %d nao encontrado.\n", id);
                            }
                        } break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opSub != 0);
                break;
            case 6: {
                int n, opBase;
                printf("\n--- Menu Base Aleatoria ---\n");
                printf("1. Criar bases de dados aleatorios\n");
                printf("2. Ordenar base\n");
                printf("0. Voltar\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opBase);
                LimpaBuffer();

                switch (opBase) {
                    case 1:
                        printf("Digite a quantidade de entidades a serem criadas: ");
                        scanf("%d", &n);
                        LimpaBuffer();
                        GerarBaseDesordenadaTuristas("turistas.dat", n);
                        GerarBaseDesordenadaDestinos("destinos.dat", n);
                        break;
                    case 2: {
                        int opOrdenacao;
                        printf("\n- Submenu Ordenar -\n");
                        printf("1. Turistas Bubble Sort\n");
                        printf("2. Turistas Particoes e Intercalacao\n");
                        printf("3. Destinos Bubble Sort\n");
                        printf("4. Destinos Particoes e Intercalacao\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opOrdenacao);
                        LimpaBuffer();

                        switch (opOrdenacao) {
                            case 1:
                                BubbleSortTuristas("turistas.dat");
                                break;
                            case 2:
                                OrdenarTuristasExterna("turistas.dat");
                                break;
                            case 3:
                                BubbleSortDestinos("destinos.dat");
                                break;
                            case 4:
                                OrdenarDestinosExterna("destinos.dat");
                                break;
                            case 0:
                                break;
                            default:
                                printf("Opcao invalida. Tente novamente.\n");
                        }
                    }
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opcao invalida. Tente novamente.\n");
                }
            }
                break;
            case 7: {
                int opHash;
                do {
                    printf("\n--- Menu Tabela Hash ---\n");
                    printf("1. Visualizar Tabela Hash\n");
                    printf("2. Inserir Turista na Tabela Hash\n");
                    printf("3. Buscar Turista na Tabela Hash\n");
                    printf("4. Remover Turista da Tabela Hash\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opHash);
                    LimpaBuffer();
                    switch(opHash) {
                        case 1:
                            hashVisualizar(filenameHash);
                            break;
                        case 2: {
                            Turista t;
                            printf("Digite o ID do turista: ");
                            scanf("%d", &t.id);
                            LimpaBuffer();
                            printf("Digite o nome do turista: ");
                            fgets(t.nome, MAX_NOME, stdin);
                            t.nome[strcspn(t.nome, "\n")] = '\0';
                            printf("Digite o CPF do turista: ");
                            fgets(t.cpf, 15, stdin);
                            t.cpf[strcspn(t.cpf, "\n")] = '\0';
                            printf("Digite o orcamento do turista: ");
                            scanf("%f", &t.orcamento);
                            LimpaBuffer();
                            // Para simplificar, definimos os países de interesse com valor padrão
                            for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
                                strcpy(t.paisesInteresse[i], "N/A");
                            }
                            int pos = hashInserirTurista(filenameHash, t);
                            if (pos != -1)
                                printf("Turista inserido na posicao %d na tabela hash.\n", pos);
                        }
                            break;
                        case 3: {
                            int id;
                            printf("Digite o ID do turista para buscar: ");
                            scanf("%d", &id);
                            LimpaBuffer();
                            Turista *found = hashBuscarTurista(filenameHash, id);
                            if (found) {
                                printf("Turista encontrado:\n");
                                printf("ID: %d\nNome: %s\nCPF: %s\nOrcamento: %.2f\n", found->id, found->nome, found->cpf, found->orcamento);
                                free(found);
                            } else {
                                printf("Turista nao encontrado na tabela hash.\n");
                            }
                        }
                            break;
                        case 4: {
                            int id;
                            printf("Digite o ID do turista para remover: ");
                            scanf("%d", &id);
                            LimpaBuffer();
                            int pos = hashRemoverTurista(filenameHash, id);
                            if (pos != -1)
                                printf("Turista removido da posicao %d na tabela hash.\n", pos);
                            else
                                printf("Turista nao encontrado.\n");
                        }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while(opHash != 0);
                break;
            }
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(op != 0);

    fclose(arqTuristas);
    fclose(arqDestinos);
    fclose(arqRoteiros);
    return 0;
}
