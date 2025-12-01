#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#undef interface
#include "pilha.h"
#include "cardapio.h"
#include "montagem.h"
#include "loja_ingredientes.h"
#include "aloca.h"

int main(){
    system("chcp 65001");
    system("cls");
    srand(time(NULL));
    apagaRelatorio();
    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    tp_estoque_arvore estoque;
    inicializa_estoque_lista(&estoque);
    tp_fila pedidos;
    inicializaFila(&pedidos);
    tp_pilha montado;
    inicializapilha(&montado);
    float moedas = 100.0, ganho, recebido_total = 0.0;
    int num_pedidos;
    explicacao();
    int dia;
    for(dia = 1; dia<=10; dia++){
        system("cls");
        printf("+------------------------------------- DIA %d ----------------------------------+\n", dia);
        printf("| %-66s |\n", "Prepare-se, os pedidos aparecerão apenas uma vez e voce precisará decorá-los");
        printf("| %-78s |\n", "Você começa o dia com:");
        printf("| Moedas: R$ %-65.2f |\n", moedas);
        printf("-------------------------------------------------------------------------------\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
        printf("\nBoa sorte!\n");
        Sleep(1000);
        system("cls");
        num_pedidos = gerar_pedidos(cardapio, dia, &pedidos);
        Sleep(num_pedidos * 3 * 1000);
        system("cls");
        while(!filaVazia(&pedidos)){
            tp_itemf id;
            removeFila(&pedidos, &id);
            int opcao = 16;
            while (opcao != 15){
                opcao = interface(montado);
                if(opcao == 13){
                    abrirCardapio(cardapio);
                }
                if(opcao == 14){
                    imprime_estoque_lista(&estoque);
                }
                else{
                    adicionarIngrediente_lista(opcao, &montado, &estoque);
                }
            }
            float valor_recebido = compara_hamburger(&montado, cardapio, id);
            system("cls");
            ganho = valor_recebido * cardapio[id].valor;
            recebido_total += ganho;
            moedas += ganho;
            printf("+------------------------------ ENTREGA ------------------------------+\n");
            printf("| Você acertou %.2f%% do pedido! Ganhou R$ %8.2f nesta entrega.         |\n", valor_recebido*100, ganho);
            printf("| Total de moedas: R$ %-44.2f |\n", moedas);
            printf("-----------------------------------------------------------------------\n");
            Sleep(3 * 1000);
            apagarPilha(&montado);
        }
        gravaRelatorioDia(dia, num_pedidos, ganho); // erro ao abrir no senai: permissao negada
        float custo = num_pedidos * 10 * valorBase;
        moedas -= custo;
        printf("+------------------------------ FIM DO DIA %d ------------------------------+\n", dia);
        printf("| Custo de operação: R$ %-44.2f |\n", custo);
        if (moedas <= 0){
            printf("\nVocê ficou sem moedas! Fim de jogo.\n");
            imprimeRelatorio();
            break;
        }
        else{
            printf("| Saldo final do dia: R$ %-46.2f |\n", moedas);
        }
        printf("| Agora você será redirecionado para a loja de ingredientes.           |\n");
        printf("------------------------------------------------------------------------\n");
        Sleep(3 * 1000);
        interface_loja(&estoque, &moedas);
    }
    if(dia == 10 && moedas > 0){
        printf("\nParabéns! Você conseguiu completar todos os dias de trabalho!\n");
        imprimeRelatorio();
    }
return 0;

}