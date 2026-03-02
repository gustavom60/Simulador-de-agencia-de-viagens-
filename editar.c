#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editar.h"
#include "busca.h"
#include "extras.h"
#include "entidades.h"
#include "salvar_entidades.h"

void EditarTurista(const char *filename, FILE *destinos) {
    int id, execucoes;
    double tempo;
    printf("Digite o ID do turista a editar: ");
    scanf("%d", &id);
    LimpaBuffer();

    Turista *turista = BuscaBinariaTurista(filename, id, &execucoes, &tempo);
    if (!turista) {
        printf("Turista nao encontrado!\n");
        return;
    }

    // Exibe os dados atuais do turista
    printf("\nDados atuais do turista:\n");
    printf("1. Nome: %s\n", turista->nome);
    printf("2. CPF: %s\n", turista->cpf);
    printf("3. Orcamento: %.2f\n", turista->orcamento);
    printf("4. Paises de interesse:\n");
    for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
        printf("   %d. %s\n", i + 1, turista->paisesInteresse[i]);
    }

    // Submenu para escolher qual campo editar
    int op;
    printf("\nDigite o numero da opcao que deseja editar (0 para cancelar): ");
    scanf("%d", &op);
    LimpaBuffer();

    switch (op) {
        case 0:
            printf("Edicao cancelada.\n");
            break;
        case 1:
            printf("Digite o novo nome: ");
            fgets(turista->nome, MAX_NOME, stdin);
            turista->nome[strcspn(turista->nome, "\n")] = '\0';
            break;
        case 2:
            printf("Digite o novo CPF (formato 000.000.000-00): ");
            fgets(turista->cpf, 15, stdin);
            turista->cpf[strcspn(turista->cpf, "\n")] = '\0';
            break;
        case 3:
            printf("Digite o novo orcamento: ");
            scanf("%f", &turista->orcamento);
            LimpaBuffer();
            break;
        case 4: {
            Destino d;
            int numDestinos = 0;
            printf("\n--- Lista de destinos disponiveis ---\n");
            fseek(destinos, 0, SEEK_SET);
            while (fread(&d, sizeof(Destino), 1, destinos)) {
                printf("ID: %d - Pais: %s\n", d.id, d.nomePais);
                numDestinos++;
            }
            if (numDestinos == 0) {
                printf("Nenhum destino cadastrado.\n");
                break;
            }
            for (int i = 0; i < MAX_PAISES_INTERESSE; i++) {
                int idEscolhido;
                printf("Digite o ID do pais de interesse %d: ", i + 1);
                scanf("%d", &idEscolhido);
                LimpaBuffer();
                fseek(destinos, 0, SEEK_SET);
                while (fread(&d, sizeof(Destino), 1, destinos)) {
                    if (d.id == idEscolhido) {
                        strncpy(turista->paisesInteresse[i], d.nomePais, MAX_NOME);
                        break;
                    }
                }
            }
            break;
        }
        default:
            printf("Opcao invalida. Nenhuma edicao realizada.\n");
            break;
    }

    SalvarTurista(turista, id);
    free(turista);
    printf("Turista atualizado com sucesso!\n");
}

void EditarDestino(const char *filename) {
    int id, execucoes;
    double tempo;
    printf("Digite o ID do destino a editar: ");
    scanf("%d", &id);
    LimpaBuffer();

    Destino *d = BuscaBinariaDestino(filename, id, &execucoes, &tempo);
    if (!d) {
        printf("Destino com ID %d nao encontrado.\n", id);
        return;
    }

    printf("\nDados atuais do destino:\n");
    printf("1. Pais: %s\n", d->nomePais);
    printf("2. Atracao: %s\n", d->principalAtracao);
    printf("3. Clima: %s\n", d->clima);
    printf("4. Custo medio: %.2f\n", d->custoMedioEstadia);

    int op;
    printf("\nDigite o numero da opcao que deseja editar (0 para cancelar): ");
    scanf("%d", &op);
    LimpaBuffer();

    switch(op) {
        case 0:
            printf("Edicao cancelada.\n");
            free(d);
            return;
        case 1:
            printf("Digite o novo nome do pais: ");
            fgets(d->nomePais, MAX_NOME, stdin);
            d->nomePais[strcspn(d->nomePais, "\n")] = '\0';
            break;
        case 2:
            printf("Digite a nova atracao: ");
            fgets(d->principalAtracao, MAX_NOME, stdin);
            d->principalAtracao[strcspn(d->principalAtracao, "\n")] = '\0';
            break;
        case 3:
            printf("Digite o novo clima: ");
            fgets(d->clima, MAX_NOME, stdin);
            d->clima[strcspn(d->clima, "\n")] = '\0';
            break;
        case 4:
            printf("Digite o novo custo medio: ");
            scanf("%f", &d->custoMedioEstadia);
            LimpaBuffer();
            break;
        default:
            printf("Opcao invalida. Nenhuma edicao realizada.\n");
            free(d);
            return;
    }

    SalvarDestino(d, id);
    free(d);
    printf("Destino atualizado com sucesso!\n");
}

void EditarRoteiro(const char *filename) {
    int id, execucoes;
    double tempo;
    printf("Digite o ID do roteiro a editar: ");
    scanf("%d", &id);
    LimpaBuffer();

    Roteiro *r = BuscaBinariaRoteiro(filename, id, &execucoes, &tempo);
    if (!r) {
        printf("Roteiro com ID %d nao encontrado.\n", id);
        return;
    }

    // Exibe os dados atuais do roteiro
    printf("\nDados atuais do roteiro:\n");
    printf("1. Destinos (IDs): ");
    for (int i = 0; i < r->qtdDestinos; i++) {
        printf("%d ", r->destinos[i]);
    }
    printf("\n2. Custo Total: %.2f\n", r->custoTotal);
    printf("3. Duracao Total: %d dias\n", r->duracaoTotal);
    printf("4. Vagas Disponiveis: %d\n", r->vagasDisponiveis);
    printf("5. Turistas Associados (IDs): ");
    for (int i = 0; i < r->qtdTuristasAssociados; i++) {
        printf("%d ", r->turistasAssociados[i]);
    }
    printf("\n");

    int op;
    printf("\nDigite o numero da opcao que deseja editar (0 para cancelar): ");
    scanf("%d", &op);
    LimpaBuffer();

    switch(op) {
        case 0:
            printf("Edicao cancelada.\n");
            free(r);
            return;
        case 1:
            {
                // Editar destinos: atualizar lista de destinos e recalcular custo e duracao
                printf("Digite a nova quantidade de destinos (max %d): ", MAX_DESTINOS);
                scanf("%d", &r->qtdDestinos);
                LimpaBuffer();

                int novosDestinos[MAX_DESTINOS];
                int novosDias[MAX_DESTINOS];
                float novoCustoTotal = 0;
                int novaDuracaoTotal = 0;
                Destino d;

                for (int i = 0; i < r->qtdDestinos; i++) {
                    printf("Digite o novo ID do destino %d: ", i + 1);
                    scanf("%d", &novosDestinos[i]);
                    LimpaBuffer();

                    printf("Digite a quantidade de dias para o destino %d: ", i + 1);
                    scanf("%d", &novosDias[i]);
                    LimpaBuffer();

                    // Busca o destino pelo ID no arquivo "destinos.dat"
                    FILE *fpDestinos = fopen("destinos.dat", "rb");
                    if (fpDestinos != NULL) {
                        bool destinoEncontrado = false;
                        while (fread(&d, sizeof(Destino), 1, fpDestinos)) {
                            if (d.id == novosDestinos[i]) {
                                novoCustoTotal += d.custoMedioEstadia * novosDias[i];
                                destinoEncontrado = true;
                                break;
                            }
                        }
                        fclose(fpDestinos);
                        if (!destinoEncontrado) {
                            printf("Destino com ID %d nao encontrado. Considerando custo 0 para este destino.\n", novosDestinos[i]);
                        }
                    } else {
                        printf("Erro ao abrir o arquivo de destinos.\n");
                    }
                    novaDuracaoTotal += novosDias[i];
                }
                // Atualiza os destinos do roteiro
                for (int i = 0; i < r->qtdDestinos; i++) {
                    r->destinos[i] = novosDestinos[i];
                }
                r->custoTotal = novoCustoTotal;
                r->duracaoTotal = novaDuracaoTotal;
            }
            break;
        case 2:
            // Não permite edição direta do custo total, pois ele é calculado.
            printf("O custo total e calculado automaticamente a partir dos destinos e dias. Edite os destinos para alterar o custo.\n");
            break;
        case 3:
            // Não permite edição direta da duração total, pois ela é calculada.
            printf("A duracao total e calculada automaticamente a partir dos destinos e dias. Edite os destinos para alterar a duracao.\n");
            break;
        case 4:
            printf("Digite o novo numero de vagas disponiveis: ");
            scanf("%d", &r->vagasDisponiveis);
            LimpaBuffer();
            break;
        default:
            printf("Opcao invalida. Nenhuma edicao realizada.\n");
            free(r);
            return;
    }

    SalvarRoteiro(r, id);
    free(r);
    printf("Roteiro atualizado com sucesso!\n");
}
