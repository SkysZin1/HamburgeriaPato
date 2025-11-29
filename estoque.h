#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "cardapio.h"
#include "arvoreavl.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo do estoque (árvore + array de dados)
typedef struct {
    ArvAVL* arvore; // árvore que contém os IDs dos ingredientes
    tp_ingrediente itens[13]; // dados dos ingredientes (nome, valor, quantidade)
} tp_estoque_arvore;

static const char* nomes_ingredientes[13] = {
    "Pao","Queijo","Alface","Tomate","Carne","Bacon",
    "Carne de Falafel","Frango Empanado","Maionese Temperada","BBQ",
    "Cebola Crispy","Ovo","Cheddar"
};

// Inicializa o estoque em árvore AVL com valores padrão
void inicializa_estoque_arvore(tp_estoque_arvore* estoque) {
    estoque->arvore = criarAVL();
    if (estoque->arvore == NULL) {
        printf("Erro ao criar árvore AVL!\n");
        exit(1);
    }

    // Set de todos os ingredientes com seus valores e quantidades iniciais
    for (int i = 0; i < 13; ++i) {
        strncpy(estoque->itens[i].nome, nomes_ingredientes[i], sizeof(estoque->itens[i].nome)-1);
        estoque->itens[i].nome[sizeof(estoque->itens[i].nome)-1] = '\0';
        switch(i){
            case 0: estoque->itens[i].valor = valorBase*3; break;
            case 1: estoque->itens[i].valor = valorBase*5; break;
            case 2: estoque->itens[i].valor = valorBase*3; break;
            case 3: estoque->itens[i].valor = valorBase*3; break;
            case 4: estoque->itens[i].valor = valorBase*8; break;
            case 5: estoque->itens[i].valor = valorBase*6; break;
            case 6: estoque->itens[i].valor = valorBase*10; break;
            case 7: estoque->itens[i].valor = valorBase*7; break;
            case 8: estoque->itens[i].valor = valorBase*3; break;
            case 9: estoque->itens[i].valor = valorBase*4; break;
            case 10: estoque->itens[i].valor = valorBase*5; break;
            case 11: estoque->itens[i].valor = valorBase*5; break;
            case 12: estoque->itens[i].valor = valorBase*4; break;
            default: estoque->itens[i].valor = valorBase*1.0; break;
        }
        estoque->itens[i].quantidade = 5; // quantidade inicial

        // Insere o ID na árvore (usaremos o ID como chave)
        inserir(estoque->arvore, i);
    }
}

// Busca o ID do ingrediente pelo nome (retorna -1 se não encontrado)
int encontra_id_por_nome(tp_estoque_arvore* estoque, const char* nome) {
    for (int i = 0; i < 13; ++i) {
        if (strcmp(estoque->itens[i].nome, nome) == 0) return i;
    }
    return -1;
}

// Função auxiliar: imprime os itens seguindo a ordem da árvore (in-order)
void imprime_estoque_ordem(struct NO* no, tp_estoque_arvore* estoque) {
    if (no == NULL) return;
    imprime_estoque_ordem(no->esq, estoque);
    int id = no->info;
    printf("| %-30s | %8d |\n", estoque->itens[id].nome, estoque->itens[id].quantidade);
    imprime_estoque_ordem(no->dir, estoque);
}

// Imprime estoque
void imprime_estoque_arvore(tp_estoque_arvore* estoque) {
    int opcao = 1;
    while (opcao != 0) {
        system("cls");
        printf("\n+-------------------- Estoque de Ingredientes --------------------+\n");
        printf("| %-30s | %8s |\n", "INGREDIENTE", "QUANT.");
        printf("---------------------------------------------------------------\n");

        if (estoque->arvore != NULL && *estoque->arvore != NULL) {
            imprime_estoque_ordem(*estoque->arvore, estoque);
        }

        printf("---------------------------------------------------------------\n");
        printf("Digite 0 para sair\n");
        scanf("%d", &opcao);
    }
    system("cls");
}

// Libera memória do estoque
void libera_estoque_arvore(tp_estoque_arvore* estoque) {
    if (estoque->arvore != NULL) {
        liberaABB(estoque->arvore);
        estoque->arvore = NULL;
    }
}

// Adiciona ingrediente ao pedido
int adicionarIngrediente_arvore(int opcao, tp_pilha *montado, tp_estoque_arvore *estoque) {
    if (opcao >= 0 && opcao <= 12) {
        int id = opcao;
        if (estoque->itens[id].quantidade <= 0) {
            printf("Sem estoque de %s!\n", estoque->itens[id].nome);
            return 0;
        }
        push(montado, estoque->itens[id].nome);
        estoque->itens[id].quantidade--;
        system("cls");
        printf("\nIngrediente %s adicionado ao pedido!\n", estoque->itens[id].nome);
        return 1;
    }
    return 0;
}

#endif
