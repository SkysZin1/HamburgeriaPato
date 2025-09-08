#include "pedidos.h"
#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef tp_pedido tp_itens;

typedef struct{
	tp_itens item[MAX];
	int ini, fim;
}tp_fila;

void inicializaFila (tp_fila *f){
	f->ini = f->fim = MAX - 1;	
}

int filaVazia (tp_fila *f){
	if(f->ini == f->fim) return 1;
	return 0;
}

int proximo (int pos){
	if(pos == MAX-1) return 0;
	return ++pos;
}

int filaCheia (tp_fila *f){
	if(proximo(f->fim)==f->ini) return 1;
	return 0;
}

int insereFila (tp_fila *f, tp_itens e){
	if(filaCheia(f)) return 0;
	f->fim = proximo(f->fim);
	f->item[f->fim]=e;
	return 1;
}

int removeFila (tp_fila *f, tp_itens *e){
	if(filaVazia(f)) return 0;
	f->ini = proximo(f->ini);
	*e= f->item[f->ini];
	return 1;
}

void imprimeFila(tp_fila f, tp_hamburger *cardapio, int tamanho_cardapio){
    tp_itens e;
    while(!filaVazia(&f)){
        removeFila(&f, &e);
        const char* nome = "Desconhecido";
        for(int i=0; i<tamanho_cardapio; i++){
            if(cardapio[i].id == e.id_hamburger){
                nome = cardapio[i].nome;
                break;
            }
        }
        printf("\nHambúrguer: %s\nquantidade: %d", nome, e.quantidade);
    }
}

int tamanhoFila (tp_fila f){
	int cont=0;
	tp_itens e;
	while(!filaVazia(&f)){
		removeFila(&f, &e);
		cont++;
	}
	return cont;
}


#endif				