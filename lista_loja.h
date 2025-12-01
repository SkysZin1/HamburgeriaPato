#ifndef LISTA_LOJA_H
#define LISTA_LOJA_H

#include "estoque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó da lista encadeada da loja (apenas referencia o nome do ingrediente)
typedef struct no_loja {
    char nome[25];
    struct no_loja* proximo;
} tp_no_loja;

// Tipo da lista encadeada da loja (apenas interface, sem duplicação de dados)
typedef struct {
    tp_no_loja* inicio;
    int qtd_ingredientes;
} tp_lista_loja;

// Inicializa a lista da loja com os 13 ingredientes fixos
void inicializa_lista_loja(tp_lista_loja* loja, tp_estoque_arvore* estoque) {
    loja->inicio = NULL;
    loja->qtd_ingredientes = 0;

    if (estoque->arvore == NULL || *estoque->arvore == NULL) {
        printf("Erro: Estoque vazio!\n");
        return;
    }

    // Obtém ingredientes ordenados da árvore
    tp_ingrediente ingredientes[13];
    int qtd_ingredientes = 0;
    obtem_ingredientes_ordenados(estoque, ingredientes, &qtd_ingredientes);

    // Insere cada ingrediente (apenas nome) na lista encadeada
    for (int i = 0; i < qtd_ingredientes; i++) {
        tp_no_loja* novo_no = (tp_no_loja*) malloc(sizeof(tp_no_loja));
        if (novo_no == NULL) {
            printf("Erro ao alocar memória para nó da loja!\n");
            return;
        }

        strncpy(novo_no->nome, ingredientes[i].nome, sizeof(novo_no->nome) - 1);
        novo_no->nome[sizeof(novo_no->nome) - 1] = '\0';
        novo_no->proximo = NULL;

        // Insere no final da lista
        if (loja->inicio == NULL) {
            loja->inicio = novo_no;
        } else {
            tp_no_loja* atual = loja->inicio;
            while (atual->proximo != NULL) {
                atual = atual->proximo;
            }
            atual->proximo = novo_no;
        }
        loja->qtd_ingredientes++;
    }
}

// Obtém o nome de um ingrediente da lista pelo índice
const char* obtem_nome_ingrediente_loja(tp_lista_loja* loja, int indice) {
    if (indice < 0 || indice >= loja->qtd_ingredientes) {
        return NULL;
    }

    tp_no_loja* atual = loja->inicio;
    for (int i = 0; i < indice; i++) {
        atual = atual->proximo;
    }
    return atual->nome;
}

// Encontra o nome de um ingrediente na lista
const char* encontra_nome_ingrediente_loja(tp_lista_loja* loja, int indice) {
    if (indice < 0 || indice >= loja->qtd_ingredientes) {
        return NULL;
    }

    tp_no_loja* atual = loja->inicio;
    for (int i = 0; i < indice; i++) {
        atual = atual->proximo;
    }
    return atual->nome;
}

// Imprime a lista da loja (busca valores na árvore)
void imprime_lista_loja(tp_lista_loja* loja, tp_estoque_arvore* estoque) {
    printf("ID  INGREDIENTE\t\tPREÇO\t\tESTOQUE\n");
    printf("----------------------------------------------------------\n");

    tp_no_loja* atual = loja->inicio;
    int i = 0;
    while (atual != NULL) {
        struct NO* ing = encontra_ingrediente_na_arvore(estoque->arvore, atual->nome);
        if (ing != NULL) {
            printf("%-3d %-20s", i, atual->nome);
            printf("R$%-10.2f", ing->info.valor);
            printf("%-3d\n", ing->info.quantidade);
        }
        atual = atual->proximo;
        i++;
    }
}

// Imprime a lista da loja em modo de venda (70% do valor)
void imprime_lista_loja_venda(tp_lista_loja* loja, tp_estoque_arvore* estoque) {
    printf("ID  INGREDIENTE\t\tPREÇO (70%%)\tESTOQUE\n");
    printf("----------------------------------------------------------\n");

    tp_no_loja* atual = loja->inicio;
    int i = 0;
    while (atual != NULL) {
        struct NO* ing = encontra_ingrediente_na_arvore(estoque->arvore, atual->nome);
        if (ing != NULL) {
            printf("%-3d %-20s", i, atual->nome);
            printf("R$%-10.2f", ing->info.valor * 0.7);
            printf("%-3d\n", ing->info.quantidade);
        }
        atual = atual->proximo;
        i++;
    }
}

// Libera a memória da lista
void libera_lista_loja(tp_lista_loja* loja) {
    tp_no_loja* atual = loja->inicio;
    while (atual != NULL) {
        tp_no_loja* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    loja->inicio = NULL;
    loja->qtd_ingredientes = 0;
}

#endif
