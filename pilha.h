#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* interior;
    struct No* prox;
} No;

typedef struct No* Pilha;

Pilha* criarPilha();
void push();
void imprimirPilha();

#endif