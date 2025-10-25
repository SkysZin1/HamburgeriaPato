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
        printf("Bem vindo a hamburgueria Pato Burger, hoje voce sera um de nossos montadores\n");
        printf("O que voce deseja fazer?\n1- Carregar um jogo salvo\n2- Iniciar um novo jogo\n");
        scanf("%d", &r);
    }
    if (r == 1){

    }
    else if(r==2){
        for(int dia = 1; dia<10; dia++){
            tp_hamburger esperado, montado;
            inicializapilha(&esperado.ingrediente);
            inicializapilha(&montado.ingrediente);
            printf("Dia %d\n", dia);
            printf("Prepare-se, os pedidos aparecerão apenas uma vez e voce precisara decora-los\n");
            sleep(2);
            gerar_pedidos(cardapio, dia, &pedidos);
            sleep(10);
            system("cls");
            while(!filaVazia(&pedidos)){
                tp_itemf e;
                removeFila(&pedidos, &e);
                esperado.ingrediente = cardapio[e].ingrediente;
            }
        }
    }    



    /*
    imprimecardapio(cardapio);
    sleep(2); // exemplo de uso da função sleep
    int dia = 1;
    printf("\n\n\nGerando pedidos aleatórios com base no dia:\n");
    for(int i=0; i<5; i++){
        printf("\n%d dia\n", dia);
        gerar_pedidos(cardapio, dia);
        dia++;
    }
        */
return 0;
}