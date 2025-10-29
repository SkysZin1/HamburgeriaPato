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

#define MONTAGEM_OFFSET 33 // ajuste para centralizar prints no terminal

void print_centralizado(const char* texto) {
    for(int i=0; i<MONTAGEM_OFFSET; i++) printf(" ");
    printf("%s", texto);
}

int print_montagem(tp_pilha pilha) {
    const char* reset = "\x1b[0m";
    tp_item e[30];

    while (!pilhavazia(&pilha)) {
        pop(&pilha, e);

        /* PÃO */
        if (strcmp(e, "Pao") == 0) {
            printf("\x1b[33m"); /* amarelo */
            print_centralizado("  _________  \n");
            print_centralizado(" (___PÃO___)  \n");
            printf("%s", reset);
        }

        /* QUEIJO */
        else if (strcmp(e, "Queijo") == 0) {
            printf("\x1b[33m"); /* amarelo */
            print_centralizado("  //////////  \n");
            print_centralizado("    QUEIJO     \n");
            print_centralizado("  //////////  \n");
            printf("%s", reset);
        }

        /* ALFACE */
        else if (strcmp(e, "Alface") == 0) {
            printf("\x1b[32m"); /* verde */
            print_centralizado("  ~~~~~~~~~  \n");
            print_centralizado("   ALFACE    \n");
            print_centralizado("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* TOMATE */
        else if (strcmp(e, "Tomate") == 0) {
            printf("\x1b[31m"); /* vermelho */
            print_centralizado("  ---------  \n");
            print_centralizado("   TOMATE    \n");
            print_centralizado("  ---------  \n");
            printf("%s", reset);
        }

        /* CARNE */
        else if (strcmp(e, "Carne") == 0) {
            printf("\x1b[31m"); /* vermelho */
            print_centralizado("  #########  \n");
            print_centralizado("    CARNE    \n");
            print_centralizado("  #########  \n");
            printf("%s", reset);
        }

        /* BACON */
        else if (strcmp(e, "Bacon") == 0) {
            printf("\x1b[35m"); /* magenta */
            print_centralizado("  ~~~~~~~~~  \n");
            print_centralizado("    BACON    \n");
            print_centralizado("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* CARNE DE FALAFEL */
        else if (strcmp(e, "Carne de Falafel") == 0) {
            printf("\x1b[33m");
            print_centralizado("  #########  \n");
            print_centralizado("CARNE FALAFEL\n");
            print_centralizado("  #########  \n");
            printf("%s", reset);
        }

        /* FRANGO EMPANADO */
        else if (strcmp(e, "Frango Empanado") == 0) {
            printf("\x1b[33m");
            print_centralizado("  *********  \n");
            print_centralizado(" FRANGO EMP  \n");
            print_centralizado("  *********  \n");
            printf("%s", reset);
        }

        /* MAIONESE TEMPERADA */
        else if (strcmp(e, "Maionese Temperada") == 0) {
            printf("\x1b[37m"); /* branco */
            print_centralizado("   :::::::   \n");
            print_centralizado(" MAIONESE T. \n");
            print_centralizado("   :::::::   \n");
            printf("%s", reset);
        }

        /* BBQ */
        else if (strcmp(e, "BBQ") == 0) {
            printf("\x1b[31m");
            print_centralizado("   ======    \n");
            print_centralizado("    BBQ      \n");
            print_centralizado("   ======    \n");
            printf("%s", reset);
        }

        /* CEBOLA CRISPY */
        else if (strcmp(e, "Cebola Crispy") == 0) {
            printf("\x1b[33m");
            print_centralizado("  ~~~~~~~~~  \n");
            print_centralizado("  CEBOLA CR. \n");
            print_centralizado("  ~~~~~~~~~  \n");
            printf("%s", reset);
        }

        /* OVO */
        else if (strcmp(e, "Ovo") == 0) {
            printf("\x1b[37m");
            print_centralizado("   ( O )     \n");
            print_centralizado("    OVO      \n");
            print_centralizado("   ( O )     \n");
            printf("%s", reset);
        }

        /* CHEDDAR */
        else if (strcmp(e, "Cheddar") == 0) {
            printf("\x1b[33m");
            print_centralizado("  /////////  \n");
            print_centralizado("  CHEDDAR    \n");
            print_centralizado("  /////////  \n");
            printf("%s", reset);
        }


    }

    return 1;
}

#endif