#ifndef LOJA_INGREDIENTES_H
#define LOJA_INGREDIENTES_H
#include "estoque.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Interface da loja de ingredientes (mantém a interação original, mas usando array+árvore)
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

                // Lista de ingredientes (ordem por ID)
                for (int i = 0; i < 13; i++) {
                    printf("%-3d %-20s", i, estoque->itens[i].nome);
                    if (opcao == 1) {
                        printf("R$%-10.2f", estoque->itens[i].valor);
                    } else {
                        printf("R$%-10.2f", estoque->itens[i].valor * 0.7);
                    }
                    printf("%-3d\n", estoque->itens[i].quantidade);
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

                float valor_total = estoque->itens[id_ingrediente].valor * quantidade;

                if (opcao == 1) { // Compra
                    if (valor_total > *moedas) {
                        printf("\nMoedas insuficientes! Necessário: %.2f, Disponível: %.2f\n", 
                            valor_total, *moedas);
                        Sleep(2000);
                        continue;
                    }
                    estoque->itens[id_ingrediente].quantidade += quantidade;
                    *moedas -= valor_total;
                    printf("\nComprado %d unidades de %s por %.2f moedas\n", 
                        quantidade, estoque->itens[id_ingrediente].nome, valor_total);
                } else { // Venda
                    if (quantidade > estoque->itens[id_ingrediente].quantidade) {
                        printf("\nEstoque insuficiente! Disponível: %d\n", 
                            estoque->itens[id_ingrediente].quantidade);
                        Sleep(2000);
                        continue;
                    }
                    estoque->itens[id_ingrediente].quantidade -= quantidade;
                    *moedas += valor_total * 0.7; // Venda por 70% do valor
                    printf("\nVendido %d unidades de %s por %.2f moedas\n", 
                        quantidade, estoque->itens[id_ingrediente].nome, valor_total * 0.7);
                }
                Sleep(2000);
            }
        }
    }
}

#endif