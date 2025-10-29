#ifndef LOJA_INGREDIENTES_H
#define LOJA_INGREDIENTES_H
#include "cardapio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    tp_ingrediente ingrediente;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
} tp_estoque_lista;

// Inicializa o estoque em lista encadeada com valores padrão
void inicializa_estoque_lista(tp_estoque_lista* estoque) {
    estoque->inicio = NULL;

    // Set de todos os ingredientes com seus valores e quantidades iniciais
    tp_ingrediente itens[13] = {
        {"Pao", valorBase*3, 5},
        {"Queijo", valorBase*5, 5},
        {"Alface", valorBase*3, 5},
        {"Tomate", valorBase*3, 5},
        {"Carne", valorBase*8, 5},
        {"Bacon", valorBase*6, 5},
        {"Carne de Falafel", valorBase*10, 5},
        {"Frango Empanado", valorBase*7, 5},
        {"Maionese Temperada", valorBase*3, 5},
        {"BBQ", valorBase*4, 5},
        {"Cebola Crispy", valorBase*5, 5},
        {"Ovo", valorBase*5, 5},
        {"Cheddar", valorBase*4, 5}
    };

    // Insere todos os itens na lista (inserção no início é suficiente, buscamos por nome quando necessário)
    for (int i = 0; i < 13; ++i) {
        No* novo_no = (No*)malloc(sizeof(No));
        if (novo_no == NULL) {
            printf("Erro ao alocar memória para o novo nó!\n");
            exit(1);
        }
        novo_no->ingrediente = itens[i];
        novo_no->proximo = estoque->inicio;
        estoque->inicio = novo_no;
    }
}

// Função auxiliar: encontra nó do ingrediente por nome
No* encontra_no_por_nome(tp_estoque_lista* estoque, const char* nome) {
    No* atual = estoque->inicio;
    while (atual != NULL) {
        if (strcmp(atual->ingrediente.nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}



// Imprime estoque (interface melhorada, sem ID)
void imprime_estoque_lista(tp_estoque_lista* estoque) {
    int opcao = 1;
    while (opcao != 0) {
        system("cls");
        printf("\n+-------------------- Estoque de Ingredientes --------------------+\n");
        printf("| %-30s | %8s |\n", "INGREDIENTE", "QUANT.");
        printf("---------------------------------------------------------------\n");

        No* atual = estoque->inicio;
        while (atual != NULL) {
            printf("| %-30s | %8d |\n", atual->ingrediente.nome, atual->ingrediente.quantidade);
            atual = atual->proximo;
        }
        printf("---------------------------------------------------------------\n");
        printf("Digite 0 para sair\n");
        scanf("%d", &opcao);
    }
    system("cls");
}

// Libera memória
 void libera_estoque_lista(tp_estoque_lista* estoque) {
    No* atual = estoque->inicio;
    while (atual != NULL) {
        No* proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    estoque->inicio = NULL;
}

// Interface unificada da loja de ingredientes
void interface_loja(tp_estoque_lista* estoque, float* moedas) {
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
                    No* no_encontrado = encontra_no_por_nome(estoque, nomes[i]);
                    if (no_encontrado) {
                        printf("%-3d %-20s", i, nomes[i]);
                        if (opcao == 1) {
                            printf("R$%-10.2f", no_encontrado->ingrediente.valor);
                        } else {
                            printf("R$%-10.2f", no_encontrado->ingrediente.valor * 0.7);
                        }
                        printf("%-3d\n", no_encontrado->ingrediente.quantidade);
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
            
            No* no_encontrado = encontra_no_por_nome(estoque, nomes[id_ingrediente]);
            if (no_encontrado) {
                float valor_total = no_encontrado->ingrediente.valor * quantidade;
                
                if (opcao == 1) { // Compra
                    if (valor_total > *moedas) {
                        printf("\nMoedas insuficientes! Necessário: %.2f, Disponível: %.2f\n", 
                            valor_total, *moedas);
                        Sleep(2000);
                        continue;
                    }
                    no_encontrado->ingrediente.quantidade += quantidade;
                    *moedas -= valor_total;
                    printf("\nComprado %d unidades de %s por %.2f moedas\n", 
                        quantidade, nomes[id_ingrediente], valor_total);
                } else { // Venda
                    if (quantidade > no_encontrado->ingrediente.quantidade) {
                        printf("\nEstoque insuficiente! Disponível: %d\n", 
                            no_encontrado->ingrediente.quantidade);
                        Sleep(2000);
                        continue;
                    }
                    no_encontrado->ingrediente.quantidade -= quantidade;
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

// Adiciona ingrediente ao pedido a partir de um índice (mesma ordem interface)
int adicionarIngrediente_lista(int opcao, tp_pilha *montado, tp_estoque_lista *estoque) {
    const char* nomes[13] = {
        "Pao","Queijo","Alface","Tomate","Carne","Bacon",
        "Carne de Falafel","Frango Empanado","Maionese Temperada","BBQ",
        "Cebola Crispy","Ovo","Cheddar"
    };
    if (opcao >= 0 && opcao <= 12) {
        const char* nome = nomes[opcao];
        No* no_encontrado = encontra_no_por_nome(estoque, nome);
        if (no_encontrado->ingrediente.quantidade <= 0) {
            printf("Sem estoque de %s!\n", nome);
            return 0;
        }
        push(montado, no_encontrado->ingrediente.nome);
        no_encontrado->ingrediente.quantidade--;
        system("cls");
        printf("\nIngrediente %s adicionado ao pedido!\n", no_encontrado->ingrediente.nome);
        return 1;
    }
    return 0;
}

#endif