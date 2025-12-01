#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "cardapio.h"
#include "arvoreavl.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo do estoque (apenas árvore AVL)
typedef struct {
    ArvAVL* arvore; // árvore que contém os ingredientes
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
        tp_ingrediente novo_ingrediente;
        strncpy(novo_ingrediente.nome, nomes_ingredientes[i], sizeof(novo_ingrediente.nome)-1);
        novo_ingrediente.nome[sizeof(novo_ingrediente.nome)-1] = '\0';
        switch(i){
            case 0: novo_ingrediente.valor = valorBase*3; break;
            case 1: novo_ingrediente.valor = valorBase*5; break;
            case 2: novo_ingrediente.valor = valorBase*3; break;
            case 3: novo_ingrediente.valor = valorBase*3; break;
            case 4: novo_ingrediente.valor = valorBase*8; break;
            case 5: novo_ingrediente.valor = valorBase*6; break;
            case 6: novo_ingrediente.valor = valorBase*10; break;
            case 7: novo_ingrediente.valor = valorBase*7; break;
            case 8: novo_ingrediente.valor = valorBase*3; break;
            case 9: novo_ingrediente.valor = valorBase*4; break;
            case 10: novo_ingrediente.valor = valorBase*5; break;
            case 11: novo_ingrediente.valor = valorBase*5; break;
            case 12: novo_ingrediente.valor = valorBase*4; break;
            default: novo_ingrediente.valor = valorBase*1.0; break;
        }
        novo_ingrediente.quantidade = 5; // quantidade inicial

        // Insere o ingrediente na árvore
        inserir(estoque->arvore, novo_ingrediente);
    }
}

// imprime:  os itens seguindo a ordem da árvore
void imprime_estoque_ordem(struct NO* no, tp_estoque_arvore* estoque) {
    if (no == NULL) return;
    imprime_estoque_ordem(no->esq, estoque);
    printf("| %-30s | %8d |\n", no->info.nome, no->info.quantidade);
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

// Função auxiliar para coletar ingredientes em ordem em um array
void coleta_ingredientes_inorder(struct NO* no, tp_ingrediente* array, int* indice) {
    if (no == NULL) return;
    coleta_ingredientes_inorder(no->esq, array, indice);
    array[*indice] = no->info;
    (*indice)++;
    coleta_ingredientes_inorder(no->dir, array, indice);
}

// Obtém todos os ingredientes ordenados em um array
void obtem_ingredientes_ordenados(tp_estoque_arvore* estoque, tp_ingrediente* array, int* qtd) {
    if (estoque->arvore == NULL || *estoque->arvore == NULL) {
        *qtd = 0;
        return;
    }
    int indice = 0;
    coleta_ingredientes_inorder(*estoque->arvore, array, &indice);
    *qtd = indice;
}

// Busca e modifica um ingrediente na árvore pelo nome
struct NO* encontra_ingrediente_na_arvore(ArvAVL* arvore, const char* nome) {
    if (arvore == NULL || *arvore == NULL) return NULL;
    
    struct NO* atual = *arvore;
    while (atual != NULL) {
        int cmp = strcmp(nome, atual->info.nome);
        if (cmp == 0) {
            return atual;
        } else if (cmp < 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return NULL;
}

// Adiciona ingrediente ao pedido pelo índice (compatibilidade com interface)
int adicionarIngrediente_por_indice(int indice, tp_pilha *montado, tp_estoque_arvore *estoque) {
    tp_ingrediente ingredientes[13];
    int qtd_ingredientes = 0;
    obtem_ingredientes_ordenados(estoque, ingredientes, &qtd_ingredientes);
    
    if (indice < 0 || indice >= qtd_ingredientes) {
        return 0;
    }
    
    return adicionarIngrediente_arvore(ingredientes[indice].nome, montado, estoque);
}

// Adiciona ingrediente ao pedido
int adicionarIngrediente_arvore(const char* nome_ingrediente, tp_pilha *montado, tp_estoque_arvore *estoque) {
    if (estoque->arvore == NULL || *estoque->arvore == NULL) {
        printf("Estoque vazio!\n");
        return 0;
    }
    
    // Busca o ingrediente na árvore percorrendo em ordem
    struct NO* atual = *estoque->arvore;
    struct NO* encontrado = NULL;
    
    while (atual != NULL) {
        int cmp = strcmp(nome_ingrediente, atual->info.nome);
        if (cmp == 0) {
            encontrado = atual;
            break;
        } else if (cmp < 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    if (encontrado == NULL) {
        printf("Ingrediente %s não encontrado!\n", nome_ingrediente);
        return 0;
    }
    
    if (encontrado->info.quantidade <= 0) {
        printf("Sem estoque de %s!\n", encontrado->info.nome);
        return 0;
    }
    
    push(montado, encontrado->info.nome);
    encontrado->info.quantidade--;
    system("cls");
    printf("\nIngrediente %s adicionado ao pedido!\n", encontrado->info.nome);
    return 1;
}

#endif
