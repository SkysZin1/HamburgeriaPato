#include "pilha.h" 
#include "cardapio.h"
#include "montagem.h"
#include <stdio.h>

int main(void) {
    system("chcp 65001");
    system("cls");
    tp_pilha pilha;
    tp_ingrediente ing;
    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    inicializapilha(&pilha);   // ou o nome da função que inicia a pilha

    // Empilha alguns ingredientes (exemplo)
    strcpy(ing.nome, "Pao");
    push(&pilha, ing.nome);

    strcpy(ing.nome, "Carne");
    push(&pilha, ing.nome);

    strcpy(ing.nome, "Queijo");
    push(&pilha, ing.nome);
    
    strcpy(ing.nome, "Bacon");
    push(&pilha, ing.nome);

    strcpy(ing.nome, "Pao");
    push(&pilha, ing.nome);

    /* Agora chama a função que imprime
    print_montagem(&pilha);
    */
    float valor_recebido = compara_hamburger(&pilha, cardapio, 0);
    printf("%.2f", valor_recebido);

    return 0;
}