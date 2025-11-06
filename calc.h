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
void pop(Pilha* pi);
void imprimirPilha(Pilha* pi);
void imprimirPilhaResultado(Pilha* pi);
bool ehNum(char c);
bool ehSimbolo_ou_Abrido(Pilha* pi, char c);
bool ehFechado(Pilha* pi, char c);
void addnum(Pilha* pi,int* indice, char input[50]);
void calcularPiCalc(Pilha* pi,Pilha* pi_calc);
void InserirPiCalc(Pilha* pi, Pilha* pi_calc);

#endif