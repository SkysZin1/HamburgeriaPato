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
    printf("Bem vindo a hamburgueria Pato Burger, hoje voce sera um de nossos montadores\n");
    printf("Voce tem um estoque limitado de ingredientes e a cada entrega ganha moedas para comprar mais\n");
    printf("Se seus ingredientes acabarem voce perde\n");
    printf("\nO que voce deseja fazer?\n1- Carregar um jogo salvo\n2- Iniciar um novo jogo\n");
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
        printf("%s\n", cardapio[valor].nome);
        insereFila(pedidos, cardapio[valor].id);
    }
}

int interface(tp_pilha montado){
    int opcao = 30;
    printf("\n\n------------------------------ escolha uma opcao ------------------------------ \n\n");
    printf("0 - Pao\t\t 1 - Queijo\t 2 - Alface\t 3 - Tomate\t 4 - Carne\n5 - Bacon\t 6 - Carne de Falafel\t 7 - Frango Empanado\t 8 - Maionese Temperada\n9 - BBQ\t\t 10 - Cebola Crispy\t 11 - Ovo\t\t 12 - Cheddar\n\n13 - Abrir cardapio\t 14 - Abrir estoque\t  15 - Finalizar pedido\n");
    printf("\n------------------------------ Seu pedido atual ------------------------------\n");
    print_montagem(montado);
    while(opcao < 0 || opcao > 15){ 
        scanf("%d", &opcao);
    }    
    return opcao;
}

void abrirCardapio(tp_hamburger *cardapio){  // Imprime o cardapio padrao
    int opcao = 1;
    while(opcao != 0){
        for(int i=0; i<tamanho; i++){
        printf("\n%s R$%.2f\n", cardapio[i].nome, cardapio[i].valor);
        imprimepilha(cardapio[i].ingrediente);
        }
        printf("\nDigite 0 para sair do cardapio\n");
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