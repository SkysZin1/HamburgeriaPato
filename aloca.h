#ifndef ALOCA_H
#define ALOCA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "cardapio.h"

int apagaRelatorio() {
    FILE *arq = fopen("../alocacao.txt", "w");

    if (arq == NULL) {
        perror("Erro ao abrir alocacao.txt (apagar relatorio)");
        return 0;
    }
    fclose(arq);
    return 1;    
}

int gravaRelatorioDia(int dia, int totalHamburgueres, float totalMoedas) {
    FILE *arq = fopen("../alocacao.txt", "a");

    if (arq == NULL) {
        perror("Erro ao abrir alocacao.txt (relatorio dia)");
        return 0;
    }

    else {
        fprintf(arq, "\n======= RELATÓRIO DO DIA %d =======\n", dia);
        fprintf(arq, "Total de hambúrgueres vendidos: %d\n", totalHamburgueres);
        fprintf(arq, "Total de moedas obtidas: R$ %.2f\n", totalMoedas);
        fprintf(arq, "=====================================\n\n");

        fflush(arq);
        fclose(arq);
        return 1;
    }
}

#endif