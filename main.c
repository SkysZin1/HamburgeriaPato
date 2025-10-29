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

int main(){
    system("chcp 65001");
    system("cls");
    srand(time(NULL));

    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    tp_estoque_lista estoque;
    inicializa_estoque_lista(&estoque);
    tp_fila pedidos;
    inicializaFila(&pedidos);
    int r;
    while(r!=1 && r!=2){
        r = explicacao();
    }
    if (r == 1){

    }
    else if(r==2){
        tp_pilha esperado, montado;
        inicializapilha(&esperado);
        inicializapilha(&montado);
        float moedas = 100.0;
        for(int dia = 1; dia<10; dia++){
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
            gerar_pedidos(cardapio, dia, &pedidos);
            Sleep(dia * 3 * 1000);
            system("cls");
            while(!filaVazia(&pedidos)){
                tp_itemf id;
                removeFila(&pedidos, &id);
                esperado = cardapio[id].ingrediente;
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
                float ganho = valor_recebido * cardapio[id].valor;
                moedas += ganho;
                printf("+------------------------------ ENTREGA ------------------------------+\n");
                printf("| Você acertou %6.2f%% do pedido! Ganhou R$ %8.2f nesta entrega.         |\n", valor_recebido*100, ganho);
                printf("| Total de moedas: R$ %-44.2f |\n", moedas);
                printf("-----------------------------------------------------------------------\n");
                Sleep(3 * 1000);
                apagarPilha(&montado);
                apagarPilha(&esperado);
            }
            moedas -= dia * 15 * valorBase;
            printf("+------------------------------ FIM DO DIA %d ------------------------------+\n", dia);
            printf("| Custo de operação: R$ %-44.2f |\n", dia * 15 * valorBase);
            printf("| Agora você será redirecionado para a loja de ingredientes.           |\n");
            printf("------------------------------------------------------------------------\n");
            Sleep(3 * 1000);
            interface_loja(&estoque, &moedas);
        }
    }

return 0;

}