#ifndef CARDAPIO_H
#define CARDAPIO_H
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "pilha.h"
#include "fila.h"
#include "montagem.h"
#define valorBase 1.5
#define tamanho 10
#define DISTANCIA_INTERFACE 4

typedef struct{ // Criação da struct tp_ingrediente
    char nome[25]; 
    float valor;
    int quantidade;
}tp_ingrediente;

typedef struct {  // Criação da struct tp_hamburger
    char nome[20];
    int id;
    float valor;
    tp_pilha ingrediente;
}tp_hamburger;

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

float compara_hamburger(tp_pilha *montado, tp_hamburger *cardapio, int id){
    tp_pilha esperado = cardapio[id].ingrediente;
    float contador = 0;
    int divisor;
    divisor = alturaPilha(&esperado);
    tp_item a[30], b[30];
    for(int i=0; i<divisor; i++){
        pop(&esperado, a);
        pop(montado, b);
        if(strcmp(a, b)==0) contador++;
    }
    return contador/divisor;
}

void gerar_pedidos(tp_hamburger *cardapio, int dia, tp_fila *pedidos){  // Gera pedidos de forma aleatoria com base no dia(fase) do jogo
    for(int i=0; i<dia; i++){
        int valor = (rand() % 10);
        printf("%d - %s\n", i + 1, cardapio[valor].nome);
        insereFila(pedidos, cardapio[valor].id);
    }
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

void inicializacardapio(tp_hamburger *cardapio){  // Set de todos os dados de todos os hamburgeres
    strcpy(cardapio[0].nome, "Bit and Bacon");  
    cardapio[0].id = 0;
    cardapio[0].valor = valorBase*35;
    inicializapilha(&cardapio[0].ingrediente);
    push(&cardapio[0].ingrediente, "Pao");
    push(&cardapio[0].ingrediente, "Queijo");
    push(&cardapio[0].ingrediente, "Carne");
    push(&cardapio[0].ingrediente, "Bacon");
    push(&cardapio[0].ingrediente, "Pao");

    strcpy(cardapio[1].nome, "Duck Cheese");
    cardapio[1].id = 1;
    cardapio[1].valor = valorBase*25;
    inicializapilha(&cardapio[1].ingrediente);
    push(&cardapio[1].ingrediente, "Pao");
    push(&cardapio[1].ingrediente, "Queijo");
    push(&cardapio[1].ingrediente, "Tomate");
    push(&cardapio[1].ingrediente, "Alface");
    push(&cardapio[1].ingrediente, "Pao");
 
    strcpy(cardapio[2].nome, "Quackteirao");
    cardapio[2].id = 2;
    cardapio[2].valor = valorBase*40;
    inicializapilha(&cardapio[2].ingrediente);
    push(&cardapio[2].ingrediente, "Pao");
    push(&cardapio[2].ingrediente, "Queijo");
    push(&cardapio[2].ingrediente, "Carne");
    push(&cardapio[2].ingrediente, "Queijo");
    push(&cardapio[2].ingrediente, "Alface");
    push(&cardapio[2].ingrediente, "Pao");

    strcpy(cardapio[3].nome, "Big Pato");
    cardapio[3].id = 3;
    cardapio[3].valor = valorBase*60;
    inicializapilha(&cardapio[3].ingrediente);
    push(&cardapio[3].ingrediente, "Pao");
    push(&cardapio[3].ingrediente, "Alface");
    push(&cardapio[3].ingrediente, "Queijo");
    push(&cardapio[3].ingrediente, "Carne");
    push(&cardapio[3].ingrediente, "Pao");
    push(&cardapio[3].ingrediente, "Alface");
    push(&cardapio[3].ingrediente, "Carne");
    push(&cardapio[3].ingrediente, "Pao");

    strcpy(cardapio[4].nome, "Vegan Pato");
    cardapio[4].id = 4;
    cardapio[4].valor = valorBase*30;
    inicializapilha(&cardapio[4].ingrediente);
    push(&cardapio[4].ingrediente, "Pao");
    push(&cardapio[4].ingrediente, "Tomate");
    push(&cardapio[4].ingrediente, "Alface");
    push(&cardapio[4].ingrediente, "Carne de Falafel");
    push(&cardapio[4].ingrediente, "Pao");

    strcpy(cardapio[5].nome, "Chicken Burguer");
    cardapio[5].id = 5;
    cardapio[5].valor = valorBase*40;
    inicializapilha(&cardapio[5].ingrediente);
    push(&cardapio[5].ingrediente, "Pao");
    push(&cardapio[5].ingrediente, "Frango Empanado");
    push(&cardapio[5].ingrediente, "Queijo");
    push(&cardapio[5].ingrediente, "Tomate");
    push(&cardapio[5].ingrediente, "Alface");
    push(&cardapio[5].ingrediente, "Maionese Temperada");
    push(&cardapio[5].ingrediente, "Pao");

    strcpy(cardapio[6].nome, "Chedao");
    cardapio[6].id = 6;
    cardapio[6].valor = valorBase*45;
    inicializapilha(&cardapio[6].ingrediente);
    push(&cardapio[6].ingrediente, "Pao");
    push(&cardapio[6].ingrediente, "Carne");
    push(&cardapio[6].ingrediente, "Cheddar");
    push(&cardapio[6].ingrediente, "Cebola Crispy");
    push(&cardapio[6].ingrediente, "Carne");
    push(&cardapio[6].ingrediente, "Cheddar");
    push(&cardapio[6].ingrediente, "Cebola Crispy");
    push(&cardapio[6].ingrediente, "Pao");

    strcpy(cardapio[7].nome, "Bacon 2.0");
    cardapio[7].id = 7;
    cardapio[7].valor = valorBase*50;
    inicializapilha(&cardapio[7].ingrediente);
    push(&cardapio[7].ingrediente, "Pao");
    push(&cardapio[7].ingrediente, "Carne");
    push(&cardapio[7].ingrediente, "Bacon");
    push(&cardapio[7].ingrediente, "BBQ");
    push(&cardapio[7].ingrediente, "Carne");
    push(&cardapio[7].ingrediente, "Bacon");
    push(&cardapio[7].ingrediente, "Pao");

    strcpy(cardapio[8].nome, "Pato Egg");
    cardapio[8].id = 8;
    cardapio[8].valor = valorBase*35;
    inicializapilha(&cardapio[8].ingrediente);
    push(&cardapio[8].ingrediente, "Pao");
    push(&cardapio[8].ingrediente, "Maionese Temperada");
    push(&cardapio[8].ingrediente, "Carne");
    push(&cardapio[8].ingrediente, "Ovo");
    push(&cardapio[8].ingrediente, "Pao");

    strcpy(cardapio[9].nome, "Pa-Tudo");
    cardapio[9].id = 9;
    cardapio[9].valor = valorBase*80;
    inicializapilha(&cardapio[9].ingrediente);
    push(&cardapio[9].ingrediente, "Pao");
    push(&cardapio[9].ingrediente, "Carne");
    push(&cardapio[9].ingrediente, "BBQ");
    push(&cardapio[9].ingrediente, "Cheddar");
    push(&cardapio[9].ingrediente, "Frango Empanado");
    push(&cardapio[9].ingrediente, "Maionese Temperada");
    push(&cardapio[9].ingrediente, "Carne");
    push(&cardapio[9].ingrediente, "Bacon");
    push(&cardapio[9].ingrediente, "Pao");
}

#endif