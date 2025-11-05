#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor_simb;
    char simb;
    int valor;
    struct No* interior;
    struct No* prox;
} No;

typedef struct No* Pilha;

Pilha* criarPilha();
void push(Pilha* pi, int valor);
void push_simb(Pilha* pi, char simb);
void imprimirPilha(Pilha* pi);

#endif