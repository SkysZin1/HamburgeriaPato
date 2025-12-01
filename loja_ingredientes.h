#ifndef LOJA_INGREDIENTES_H
#define LOJA_INGREDIENTES_H
#include "estoque.h"
#include "lista_loja.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Interface da loja de ingredientes (usando lista encadeada como interface)
void interface_loja(tp_estoque_arvore* estoque, float* moedas) {
    // Inicializa a lista da loja
    tp_lista_loja loja;
    inicializa_lista_loja(&loja, estoque);

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

                // Atualiza a lista com dados atuais do estoque
                // (a lista apenas referencia nomes, dados vêm da árvore)

                // Exibe a lista
                if (opcao == 1) {
                    imprime_lista_loja(&loja, estoque);
                } else {
                    imprime_lista_loja_venda(&loja, estoque);
                }

                printf("\nDigite o número do ingrediente (0-%d) ou 99 para voltar: ", loja.qtd_ingredientes - 1);
                scanf("%d", &id_ingrediente);

                if (id_ingrediente == 99) {
                    opcao = -1; // Força voltar ao menu principal
                    break;
                }
            }

            if (id_ingrediente >= 0 && id_ingrediente < 13) {
                // Obtém o nome do ingrediente selecionado da lista
                const char* nome_selecionado = obtem_nome_ingrediente_loja(&loja, id_ingrediente);
                
                if (nome_selecionado == NULL) {
                    opcao = -1;
                    continue;
                }
                
                // Busca o ingrediente na árvore para obter dados atualizados
                struct NO* ing_arvore = encontra_ingrediente_na_arvore(estoque->arvore, nome_selecionado);
                if (ing_arvore == NULL) {
                    opcao = -1;
                    continue;
                }
                
                int quantidade = 0;
                while (quantidade <= 0) {
                    printf("\nQuantidade desejada (ou 0 para cancelar): ");
                    scanf("%d", &quantidade);
                    if (quantidade == 0) {
                        opcao = -1; // Volta ao menu principal
                        break;
                    }
                }

                float valor_total = ing_arvore->info.valor * quantidade;

                if (opcao == 1) { // Compra
                    if (valor_total > *moedas) {
                        printf("\nMoedas insuficientes! Necessário: %.2f, Disponível: %.2f\n", 
                            valor_total, *moedas);
                        Sleep(2000);
                        continue;
                    }
                    // Atualiza quantidade no estoque (árvore)
                    ing_arvore->info.quantidade += quantidade;
                    *moedas -= valor_total;
                    printf("\nComprado %d unidades de %s por %.2f moedas\n", 
                        quantidade, ing_arvore->info.nome, valor_total);
                } else { // Venda
                    if (quantidade > ing_arvore->info.quantidade) {
                        printf("\nEstoque insuficiente! Disponível: %d\n", 
                            ing_arvore->info.quantidade);
                        Sleep(2000);
                        continue;
                    }
                    ing_arvore->info.quantidade -= quantidade;
                    *moedas += valor_total * 0.7; // Venda por 70% do valor
                    printf("\nVendido %d unidades de %s por %.2f moedas\n", 
                        quantidade, ing_arvore->info.nome, valor_total * 0.7);
                }
                Sleep(2000);
            }
        }
    }

    // Libera a lista da loja
    libera_lista_loja(&loja);
}

#endif