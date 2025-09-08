#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#include <locale.h>
#define MAX 100

typedef char
	tp_item;
	
typedef struct {
	int topo;
	tp_item item[MAX][MAX];
}tp_pilha;

void inicializapilha(tp_pilha *p){
	p->topo = -1;
}

int pilhavazia(tp_pilha *p){
	if (p->topo == -1) return 1;
	return 0;
}

int pilhacheia(tp_pilha *p){
	if (p->topo == MAX-1) return 1;
	return 0;
}

int push(tp_pilha *p, tp_item e[20]){
	if (pilhacheia(p)==1) return 0;
	p->topo++;
	strcpy(p->item[p->topo], e);
	return 1;
}

int pop(tp_pilha *p, tp_item *e){
	if (pilhavazia(p)==1) return 0;
	strcpy(e, p->item[p->topo]);
	p->topo--;
	return 1;
}

int top(tp_pilha *p, tp_item *e){
    if (pilhavazia(p)== 1) return 0;
    strcpy(e, p->item[p->topo]);
    return 1;
}

int alturaPilha(tp_pilha *p) {
    return p->topo+1;
}

void imprimepilha(tp_pilha p){
    tp_item e[20];
    printf("\n");
    while (!pilhavazia(&p)){
        pop(&p, e);
        printf("%s\n", e);
    }
}

int pilhaigual(tp_pilha a, tp_pilha b){
	if (a.topo != b.topo) return 0;
	tp_item e, d;
	while(!pilhavazia(&a)){
		pop(&a, &e);
		pop(&b, &d);
		if (e!=d) return 0;
	}
	return 1;
}

#endif