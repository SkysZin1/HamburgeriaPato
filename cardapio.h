#ifndef CARDAPIO_H
#define CARDAPIO_H
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "pilha.h"
#define valorBase 1.5
#define tamanho 10

typedef struct {  // Criação da struct tp_hamburger
    char nome[20];
    int id;
    float valor;
    tp_pilha ingrediente;
}tp_hamburger;

void pedidos(tp_hamburger *cardapio, int dia){  // Gera pedidos de forma aleatoria com base no dia(fase) do jogo
    for(int i=0; i<dia; i++){
        int valor = (rand() % 10);
        printf("%s\n", cardapio[valor].nome);
    }
}

void imprimecardapio(tp_hamburger *p){  // Imprime o nome, preço e a pilha de ingredientes de cada hamburger
    for(int i=0; i<tamanho; i++){
        printf("\n%s R$%.2f\n", p[i].nome, p[i].valor);
        imprimepilha(p[i].ingrediente);
    }
}

void inicializacardapio(tp_hamburger *cardapio){  // Set de todos os dados de todos os hamburgeres
    
    strcpy(cardapio[0].nome, "Bit and Bacon");
    cardapio[0].id = 150;
    cardapio[0].valor = valorBase*35;
    inicializapilha(&cardapio[0].ingrediente);
    push(&cardapio[0].ingrediente, "Pao");
    push(&cardapio[0].ingrediente, "Queijo");
    push(&cardapio[0].ingrediente, "Carne");
    push(&cardapio[0].ingrediente, "Bacon");
    push(&cardapio[0].ingrediente, "Pao");

    strcpy(cardapio[1].nome, "Duck Cheese");
    cardapio[1].id = 155;
    cardapio[1].valor = valorBase*25;
    inicializapilha(&cardapio[1].ingrediente);
    push(&cardapio[1].ingrediente, "Pao");
    push(&cardapio[1].ingrediente, "Queijo");
    push(&cardapio[1].ingrediente, "Tomate");
    push(&cardapio[1].ingrediente, "Alface");
    push(&cardapio[1].ingrediente, "Pao");
 
    strcpy(cardapio[2].nome, "Quackteirao");
    cardapio[2].id = 160;
    cardapio[2].valor = valorBase*40;
    inicializapilha(&cardapio[2].ingrediente);
    push(&cardapio[2].ingrediente, "Pao");
    push(&cardapio[2].ingrediente, "Queijo");
    push(&cardapio[2].ingrediente, "Carne");
    push(&cardapio[2].ingrediente, "Queijo");
    push(&cardapio[2].ingrediente, "Alface");
    push(&cardapio[2].ingrediente, "Pao");

    strcpy(cardapio[3].nome, "Big Pato");
    cardapio[3].id = 170;
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
    cardapio[4].id = 165;
    cardapio[4].valor = valorBase*30;
    inicializapilha(&cardapio[4].ingrediente);
    push(&cardapio[4].ingrediente, "Pao");
    push(&cardapio[4].ingrediente, "Tomate");
    push(&cardapio[4].ingrediente, "Alface");
    push(&cardapio[4].ingrediente, "Carne de Falafel");
    push(&cardapio[4].ingrediente, "Pao");

    strcpy(cardapio[5].nome, "Chicken Burguer");
    cardapio[5].id = 175;
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
    cardapio[6].id = 180;
    cardapio[6].valor = valorBase*45;
    inicializapilha(&cardapio[6].ingrediente);
    push(&cardapio[6].ingrediente, "Pao");
    push(&cardapio[6].ingrediente, "Carne");
    push(&cardapio[6].ingrediente, "Cheddar");
    push(&cardapio[6].ingrediente, "Carne");
    push(&cardapio[6].ingrediente, "Cheddar");
    push(&cardapio[6].ingrediente, "Cebola crispy");
    push(&cardapio[6].ingrediente, "Pao");

    strcpy(cardapio[7].nome, "Bacon 2.0");
    cardapio[7].id = 190;
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
    cardapio[8].id = 185;
    cardapio[8].valor = valorBase*35;
    inicializapilha(&cardapio[8].ingrediente);
    push(&cardapio[8].ingrediente, "Pao");
    push(&cardapio[8].ingrediente, "Maionese Temperada");
    push(&cardapio[8].ingrediente, "Carne");
    push(&cardapio[8].ingrediente, "Ovo");
    push(&cardapio[8].ingrediente, "Pao");

    strcpy(cardapio[9].nome, "Pa-Tudo");
    cardapio[9].id = 195;
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