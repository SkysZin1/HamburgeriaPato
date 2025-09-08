#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "pilha.h"
#include "cardapio.h"
#include "fila.h"
#include "pedidos.h"
#include "pedidos.c"


int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");


    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    imprimecardapio(cardapio);
    int dia = 1;
    printf("\n\n\nGerando pedidos aleatórios com base no dia:\n");
    for(int i=0; i<5; i++){
        printf("\n%d dia\n", dia);
        pedidos(cardapio, dia);
        dia++;
    }
    /*
    tp_fila fila_pedidos;                
    inicializaFila(&fila_pedidos);
    tp_pedido p = criar_pedido(145, 2);
    insereFila(&fila_pedidos, p);
    */
    return 0;
}
