#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "pilha.h"
#include "cardapio.h"


int main(){
    system("chcp 65001");
    system("cls");
    srand(time(NULL));

    tp_hamburger cardapio[10];
    inicializacardapio(cardapio);
    tp_ingrediente estoque[13];
    inicializaestoque(estoque);
    imprimecardapio(cardapio);
    // sleep(2); exemplo de uso da função sleep
    int dia = 1;
    printf("\n\n\nGerando pedidos aleatórios com base no dia:\n");
    for(int i=0; i<5; i++){
        printf("\n%d dia\n", dia);
        pedidos(cardapio, dia);
        dia++;
    }
    return 0;
}
