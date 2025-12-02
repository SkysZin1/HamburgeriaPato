#ifndef LOJA_INGREDIENTES_H
#define LOJA_INGREDIENTES_H
#include "cardapio.h"
#include "arvoreavl.h"
#include "aloca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    ArvAVL* raiz;
} tp_estoque_arvore;

// Inicializa o estoque em árvore AVL com os 13 ingredientes padrão
void inicializa_estoque_lista(tp_estoque_arvore* estoque) {
    estoque->raiz = criarAVL();

    // Vetor com os 13 ingredientes padrão
    tp_ingrediente itens[13] = {
        {"Pao", valorBase*3, 5, 0},
        {"Queijo", valorBase*5, 5, 0},
        {"Alface", valorBase*3, 5, 0},
        {"Tomate", valorBase*3, 5, 0},
        {"Carne", valorBase*8, 5, 0},
        {"Bacon", valorBase*6, 5, 0},
        {"Carne de Falafel", valorBase*10, 5, 0},
        {"Frango Empanado", valorBase*7, 5, 0},
        {"Maionese Temperada", valorBase*3, 5, 0},
        {"BBQ", valorBase*4, 5, 0},
        {"Cebola Crispy", valorBase*5, 5, 0},
        {"Ovo", valorBase*5, 5, 0},
        {"Cheddar", valorBase*4, 5, 0}
    };

    // Insere todos os ingredientes na árvore
    for (int i = 0; i < 13; ++i) {
        inserir(estoque->raiz, itens[i]);
    }
}

// Função auxiliar: encontra nó do ingrediente por nome
struct NO* encontra_no_por_nome(tp_estoque_arvore* estoque, const char* nome) {
    return consultarValorAVL(estoque->raiz, nome);
}



// Imprime estoque (em ordem)
void imprime_estoque_em_ordem(struct NO* no) {
    if (no == NULL) return;
    imprime_estoque_em_ordem(no->esq);
    printf("| %-30s | %8d |\n", no->info.nome, no->info.quantidade);
    imprime_estoque_em_ordem(no->dir);
}

void imprime_estoque_lista(tp_estoque_arvore* estoque) {
    int opcao = 1;
    while (opcao != 0) {
        system("cls");
        printf("\n+-------------------- Estoque de Ingredientes --------------------+\n");
        printf("| %-30s | %8s |\n", "INGREDIENTE", "QUANT.");
        printf("---------------------------------------------------------------\n");

        imprime_estoque_em_ordem(*estoque->raiz);
        
        printf("---------------------------------------------------------------\n");
        printf("Digite 0 para sair\n");
        scanf("%d", &opcao);
    }
    system("cls");
}

// Interface da loja de ingredientes
void interface_loja(tp_estoque_arvore* estoque, float* moedas) {
    int opcao = -1;
    while (opcao != 0) {
        system("cls");
        printf("\n------------------------------ LOJA DE INGREDIENTES ------------------------------\n");
        printf("Suas moedas: %.2f\n\n", *moedas);
        printf("0 - Sair da loja\n");
        printf("1 - Comprar ingredientes\n");
        printf("2 - Vender ingredientes\n\n");
        while(opcao < 0 || opcao > 2) {
            scanf("%d", &opcao);
        }
        
        if (opcao == 1 || opcao == 2) {
            const char* nomes[13] = {
                "Pao","Queijo","Alface","Tomate","Carne","Bacon",
                "Carne de Falafel","Frango Empanado","Maionese Temperada","BBQ",
                "Cebola Crispy","Ovo","Cheddar"
            };
            int id_ingrediente = -1;
            while (id_ingrediente < 0 || id_ingrediente >= 13) {
                system("cls");
                printf("\n------------------------------ ESCOLHA O INGREDIENTE ------------------------------\n\n");
                if (opcao == 1) {
                    printf("MODO: COMPRA - Escolha o ingrediente para comprar\n");
                } else {
                    printf("MODO: VENDA - Escolha o ingrediente para vender (recebe 70%% do valor)\n");
                }
                printf("Suas moedas: %.2f\n\n", *moedas);
                
                // Primeira linha: cabeçalho
                printf("ID  INGREDIENTE\t\tPREÇO\t\tESTOQUE\n");
                printf("----------------------------------------------------------\n");
                
                // Lista de ingredientes
                for (int i = 0; i < 13; i++) {
                    struct NO* no_encontrado = encontra_no_por_nome(estoque, nomes[i]);
                    if (no_encontrado) {
                        printf("%-3d %-20s", i, nomes[i]);
                        if (opcao == 1) {
                            printf("R$%-10.2f", no_encontrado->info.valor);
                        } else {
                            printf("R$%-10.2f", no_encontrado->info.valor * 0.7);
                        }
                        printf("%-3d\n", no_encontrado->info.quantidade);
                    }
                }
                
                printf("\nDigite o número do ingrediente (0-12) ou 99 para voltar: ");
                scanf("%d", &id_ingrediente);
                
                if (id_ingrediente == 99) {
                    opcao = -1; // Força voltar ao menu principal
                    break;
                }
            }
            
            if (id_ingrediente >= 0 && id_ingrediente < 13) {
                int quantidade = 0;
                while (quantidade <= 0) {
                    printf("\nQuantidade desejada (ou 0 para cancelar): ");
                    scanf("%d", &quantidade);
                    if (quantidade == 0) {
                        opcao = -1; // Volta ao menu principal
                        break;
                    }
                }
            
            struct NO* no_encontrado = encontra_no_por_nome(estoque, nomes[id_ingrediente]);
            if (no_encontrado) {
                float valor_total = no_encontrado->info.valor * quantidade;
                
                if (opcao == 1) { // Compra
                    if (valor_total > *moedas) {
                        printf("\nMoedas insuficientes! Necessário: %.2f, Disponível: %.2f\n", 
                            valor_total, *moedas);
                        Sleep(2000);
                        continue;
                    }
                    no_encontrado->info.quantidade += quantidade;
                    *moedas -= valor_total;
                    printf("\nComprado %d unidades de %s por %.2f moedas\n", 
                        quantidade, nomes[id_ingrediente], valor_total);
                } else { // Venda
                    if (quantidade > no_encontrado->info.quantidade) {
                        printf("\nEstoque insuficiente! Disponível: %d\n", 
                            no_encontrado->info.quantidade);
                        Sleep(2000);
                        continue;
                    }
                    no_encontrado->info.quantidade -= quantidade;
                    *moedas += valor_total * 0.7; // Venda por 70% do valor
                    printf("\nVendido %d unidades de %s por %.2f moedas\n", 
                        quantidade, nomes[id_ingrediente], valor_total * 0.7);
                }
                Sleep(2000);
            }
        }
        }
    }
}

// Adiciona ingrediente ao pedido
int adicionarIngrediente_lista(int opcao, tp_pilha *montado, tp_estoque_arvore *estoque) {
    const char* nomes[13] = {
        "Pao","Queijo","Alface","Tomate","Carne","Bacon",
        "Carne de Falafel","Frango Empanado","Maionese Temperada","BBQ",
        "Cebola Crispy","Ovo","Cheddar"
    };
    if (opcao >= 0 && opcao <= 12) {
        const char* nome = nomes[opcao];
        struct NO* no_encontrado = encontra_no_por_nome(estoque, nome);
        if (no_encontrado->info.quantidade <= 0) {
            printf("Sem estoque de %s!\n", nome);
            return 0;
        }
        push(montado, no_encontrado->info.nome);
        no_encontrado->info.quantidade--;
        no_encontrado->info.usados++;
        system("cls");
        printf("\nIngrediente %s adicionado ao pedido!\n", no_encontrado->info.nome);
        return 1;
    }
    return 0;
}

void copiar_ingredientes(struct NO* no, tp_ingrediente ingredientes[], int *i) {
    if (no == NULL) return;
    copiar_ingredientes(no->esq, ingredientes, i);
    ingredientes[*i] = no->info;
    (*i)++;
    copiar_ingredientes(no->dir, ingredientes, i);
}

void ordena_ingredientes_por_uso(tp_estoque_arvore *estoque) {
    int n = 13;
    tp_ingrediente ingredientes[13];
    // Copia os ingredientes da árvore para um vetor
    int idx = 0;
    copiar_ingredientes(*estoque->raiz, ingredientes, &idx);
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(ingredientes[j].usados < ingredientes[j+1].usados) {
                tp_ingrediente temp = ingredientes[j];
                ingredientes[j] = ingredientes[j+1];
                ingredientes[j+1] = temp;
            }
        }
    }
    gravaRelatorioUsosIngredientes(ingredientes, n); // Grava o relatório de usos dos ingredientes
}

#endif