#include "pedidos.h"
#include <stdio.h>
tp_pedido criar_pedido(int id_hamburger, int quantidade) {
    tp_pedido p;
    p.id_hamburger = id_hamburger;
    p.quantidade = quantidade;
    return p;
}