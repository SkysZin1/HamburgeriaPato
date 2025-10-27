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
            printf("Dia %d\n", dia);
            printf("Prepare-se, os pedidos aparecerão apenas uma vez e voce precisara decora-los\n");
            Sleep(2 * 1000);
            gerar_pedidos(cardapio, dia, &pedidos);
            Sleep(dia * 2 * 1000);
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
                printf("Voce acertou %.2f%% do pedido! Com isso voce ganha %.2f moedas com essa entrega!\n", valor_recebido*100, ganho);
                printf("Total de moedas: %.2f\n", moedas);
                Sleep(3 * 1000);
                apagarPilha(&montado);
                apagarPilha(&esperado);
            }
            moedas -= dia * 15 * valorBase;
            printf("Seu %d dia acabou, voce teve um custo de operacao de %d\n", dia, dia * 15 * valorBase);
            printf("Agora voce sera redirecionado para a loja de ingredientes\n");
            Sleep(3 * 1000);
            interface_loja(&estoque, &moedas);
        }
    }

return 0;

}