#ifndef PEDIDOS_H
#define PEDIDOS_H
#include <stdio.h>
typedef struct {
    int id_hamburger;
    int quantidade;
} tp_pedido;
tp_pedido criar_pedido(int id_hamburger, int quantidade);

#endif