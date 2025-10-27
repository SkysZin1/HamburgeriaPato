#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "pilha.h"
#include "cardapio.h"
#include "montagem.h"


int main(){
    system("chcp 65001");
    system("cls");
    srand(time(NULL));

    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    tp_ingrediente estoque[13];
    inicializaestoque(estoque);
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
        for(int dia = 1; dia<10; dia++){
            apagarPilha(&montado);
            apagarPilha(&esperado);
            system("cls");
            printf("Dia %d\n", dia);
            printf("Prepare-se, os pedidos aparecerão apenas uma vez e voce precisara decora-los\n");
            sleep(2);
            gerar_pedidos(cardapio, dia, &pedidos);
            sleep(dia*2);
            while(!filaVazia(&pedidos)){
                tp_itemf id;
                removeFila(&pedidos, &id);
                esperado = cardapio[id].ingrediente;
                int opcao = 15;
                while (opcao != 14){
                    system("cls");
                    opcao = interface(montado);
                    if(opcao == 13){
                        abrirCardapio(&cardapio);
                    }else{
                        adicionarIngrediente(opcao, &montado, &estoque);
                    }
                }
                float valor_recebido = compara_hamburger(&montado, cardapio, id);
                system("cls");
                printf("Voce acertou %.2f%% do pedido! Com isso voce ganha %.2f moedas com essa entrega!\n", valor_recebido*100, valor_recebido*cardapio[id].valor);
                sleep(3);
            }
            printf("Seu %d dia acabou, agora voce tera acesso a loja de ingredientes para se reabastecer\n", dia);
            sleep(3);
        }
    }    
return 0;
}