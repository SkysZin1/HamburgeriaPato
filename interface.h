#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "pilha.h"
#include "montagem.h"


int explicacao(){
    int r;
    system("cls");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| Bem vindo à hamburgueria Pato Burger!                                          |\n");
    printf("| Hoje você será um de nossos montadores.                                        |\n");
    printf("| Você tem um estoque limitado de ingredientes e a cada entrega ganha moedas.    |\n");
    printf("| O restaurante possui custos de operação a cada dia que passa.                  |\n");
    printf("| Se seus ingredientes ou moedas acabarem, você perde.                           |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| O que você deseja fazer?                                                       |\n");
    printf("| 1 - Carregar um jogo salvo                                                     |\n");
    printf("| 2 - Iniciar um novo jogo                                                       |\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("Escolha: ");
    scanf("%d", &r);
    return r;
}

int interface(tp_pilha montado){
    int opcao = 30;
    printf("\n+------------------------------ ESCOLHA UMA OPÇÃO ------------------------------+\n");
    printf("| %-2s | %-20s | %-2s | %-20s | %-2s | %-20s |\n", "ID", "INGREDIENTE", "ID", "INGREDIENTE", "ID", "INGREDIENTE");
    printf("-------------------------------------------------------------------------------\n");
    printf("| 0  | %-20s | 1  | %-20s | 2  | %-20s |\n", "Pao", "Queijo", "Alface");
    printf("| 3  | %-20s | 4  | %-20s | 5  | %-20s |\n", "Tomate", "Carne", "Bacon");
    printf("| 6  | %-20s | 7  | %-20s | 8  | %-20s |\n", "Carne de Falafel", "Frango Empanado", "Maionese Temperada");
    printf("| 9  | %-20s | 10 | %-20s | 11 | %-20s |\n", "BBQ", "Cebola Crispy", "Ovo");
    printf("| 12 | %-20s |\n", "Cheddar");
    printf("-------------------------------------------------------------------------------\n");
    printf("| 13 - Abrir cardápio | 14 - Abrir estoque | 15 - Finalizar pedido           |\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("\n+------------------------------ SEU PEDIDO ATUAL ------------------------------+\n");
    print_montagem(montado);
    while(opcao < 0 || opcao > 15){ 
        scanf("%d", &opcao);
    }    
    return opcao;
}

void abrirCardapio(tp_hamburger *cardapio){  // Imprime o cardapio padrao
    int opcao = 1;
    while(opcao != 0){
        printf("\n+------------------------------ CARDÁPIO ------------------------------+\n");
        printf("| %-20s | %-8s |\n", "HAMBÚRGUER", "PREÇO");
        printf("---------------------------------------------------------------\n");
        for(int i=0; i<tamanho; i++){
            printf("| %-20s | R$%6.2f |\n", cardapio[i].nome, cardapio[i].valor);
            imprimepilha(cardapio[i].ingrediente);
        }
        printf("---------------------------------------------------------------\n");
        printf("Digite 0 para sair do cardápio: ");
        scanf("%d", &opcao);
    }
    system("cls");
}



#endif