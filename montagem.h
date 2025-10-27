#ifndef MONTAGEM_H
#define MONTAGEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "cardapio.h"

// Cores para o terminal
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define MAGENTA "\x1b[35m"
#define WHITE   "\x1b[37m"
#define BRIGHT_WHITE "\x1b[97m"

int print_montagem(tp_pilha pilha) {
    const char* reset = "\x1b[0m";
    
    tp_item e[30];

    while (!pilhavazia(&pilha)) {
        pop(&pilha, e);

        /* PÃO */
        if (strcmp(e, "Pao") == 0) {
            printf("\x1b[33m"); /* amarelo */
            printf("  _________  \n");
            printf(" (___PÃO___)  \n");
            printf("%s", reset);
        }

        /* QUEIJO */
        else if (strcmp(e, "Queijo") == 0) {
            printf("\x1b[33m"); /* amarelo */
            printf("  //////////  \n");
            printf("    QUEIJO     \n");
            printf("  //////////  \n");
            printf("%s", reset);
        }

        /* ALFACE */
        else if (strcmp(e, "Alface") == 0) {
            printf("\x1b[32m"); /* verde */
            printf("  ~~~~~~~~~  \n");
            printf("   ALFACE    \n");
            printf("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* TOMATE */
        else if (strcmp(e, "Tomate") == 0) {
            printf("\x1b[31m"); /* vermelho */
            printf("  ---------  \n");
            printf("   TOMATE    \n");
            printf("  ---------  \n");
            printf("%s", reset);
        }

        /* CARNE */
        else if (strcmp(e, "Carne") == 0) {
            printf("\x1b[31m"); /* vermelho */
            printf("  #########  \n");
            printf("    CARNE    \n");
            printf("  #########  \n");
            printf("%s", reset);
        }

        /* BACON */
        else if (strcmp(e, "Bacon") == 0) {
            printf("\x1b[35m"); /* magenta */
            printf("  ~~~~~~~~~  \n");
            printf("    BACON    \n");
            printf("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* CARNE DE FALAFEL */
        else if (strcmp(e, "Carne de Falafel") == 0) {
            printf("\x1b[33m");
            printf("  #########  \n");
            printf("CARNE FALAFEL\n");
            printf("  #########  \n");
            printf("%s", reset);
        }

        /* FRANGO EMPANADO */
        else if (strcmp(e, "Frango Empanado") == 0) {
            printf("\x1b[33m");
            printf("  *********  \n");
            printf(" FRANGO EMP  \n");
            printf("  *********  \n");
            printf("%s", reset);
        }

        /* MAIONESE TEMPERADA */
        else if (strcmp(e, "Maionese Temperada") == 0) {
            printf("\x1b[37m"); /* branco */
            printf("   :::::::   \n");
            printf(" MAIONESE T. \n");
            printf("   :::::::   \n");
            printf("%s", reset);
        }

        /* BBQ */
        else if (strcmp(e, "BBQ") == 0) {
            printf("\x1b[31m");
            printf("   ======    \n");
            printf("    BBQ      \n");
            printf("   ======    \n");
            printf("%s", reset);
        }

        /* CEBOLA CRISPY */
        else if (strcmp(e, "Cebola Crispy") == 0) {
            printf("\x1b[33m");
            printf("  ~~~~~~~~~  \n");
            printf("  CEBOLA CR. \n");
            printf("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* OVO */
        else if (strcmp(e, "Ovo") == 0) {
            printf("\x1b[37m");
            printf("   ( O )     \n");
            printf("    OVO      \n");
            printf("   ( O )     \n");
            printf("%s", reset);
        }

        /* CHEDDAR */
        else if (strcmp(e, "Cheddar") == 0) {
            printf("\x1b[33m");
            printf("  /////////  \n");
            printf("  CHEDDAR    \n");
            printf("  /////////  \n");
            printf("%s", reset);
        }


    }

    return 1;
}

#endif