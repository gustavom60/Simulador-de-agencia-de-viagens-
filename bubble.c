#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "entidades.h"
#include "bubble.h"

void BubbleSortTuristas(const char *filename) {

    //abre o arquivo para leitura e escrita
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura/escrita.\n", filename);
        return;
    }

    //define a quantidade de registros
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    int tam = fileSize / sizeof(Turista);
    rewind(fp);


    clock_t inicio = clock();

    bool trocou;

    //implementação do bubble sort
    do { //executa enquanto houverem trocas
        trocou = false;
        for (int i = 0; i < tam - 1; i++) { //executa para todas as entidades (caso necessário)
            fseek(fp, i * sizeof(Turista), SEEK_SET);
            Turista ti;
            if (fread(&ti, sizeof(Turista), 1, fp) != 1) continue; //tenta ler a entidade, se não pula o restante do código
            fseek(fp, (i + 1) * sizeof(Turista), SEEK_SET);
            Turista tj;
            if (fread(&tj, sizeof(Turista), 1, fp) != 1) continue;
            if (ti.id > tj.id) { //faz a troca de posição dos dois arquivos
                fseek(fp, i * sizeof(Turista), SEEK_SET);
                fwrite(&tj, sizeof(Turista), 1, fp);
                fseek(fp, (i + 1) * sizeof(Turista), SEEK_SET);
                fwrite(&ti, sizeof(Turista), 1, fp);
                trocou = true;
            }
        }
    } while (trocou);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; //calcula o tempo total de execução

    fflush(fp);
    fclose(fp);

    //gravação no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Ordenacao: Bubble Sort\nEntidade: Turista\nQuantidade: %d entidades ordenadas\nTamanho total do arquivo: %ld bytes\nQuantidade de particoes: N/A\nTempo: %.6f seconds\n\n", tam, fileSize, tempo);
        fclose(logFile);
    }

    printf("Ordenacao por Bubble Sort (Turistas) concluida.\n");
}

void BubbleSortDestinos(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura/escrita.\n", filename);
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    int tam = fileSize / sizeof(Destino);
    rewind(fp);

    clock_t inicio = clock();
    bool trocou;
    do {
        trocou = false;
        for (int i = 0; i < tam - 1; i++) {
            fseek(fp, i * sizeof(Destino), SEEK_SET);
            Destino di;
            if (fread(&di, sizeof(Destino), 1, fp) != 1) continue;
            fseek(fp, (i + 1) * sizeof(Destino), SEEK_SET);
            Destino dj;
            if (fread(&dj, sizeof(Destino), 1, fp) != 1) continue;
            if (di.id > dj.id) {
                fseek(fp, i * sizeof(Destino), SEEK_SET);
                fwrite(&dj, sizeof(Destino), 1, fp);
                fseek(fp, (i + 1) * sizeof(Destino), SEEK_SET);
                fwrite(&di, sizeof(Destino), 1, fp);
                trocou = true;
            }
        }
    } while (trocou);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    fflush(fp);
    fclose(fp);

    //Gravação no log
    FILE *logFile = fopen("log.txt", "a");
    if (logFile != NULL) {
        fprintf(logFile, "Tipo de Ordenacao: Bubble Sort\nEntidade: Destino\nQuantidade: %d entidades ordenadas\nTamanho total do arquivo: %ld bytes\nQuantidade de particoes: N/A\nTempo: %.6f seconds\n\n", tam, fileSize, tempo);
        fclose(logFile);
    }

    printf("Ordenacao por Bubble Sort (Destinos) concluida.\n");
}
