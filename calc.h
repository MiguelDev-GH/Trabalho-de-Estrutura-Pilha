#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct No{
    int valor_simb;
    char simb;
    float valor;
    struct No* interior;
    struct No* prox;
} No;

typedef struct No* Pilha;

Pilha* criarPilha();
void push(Pilha* pi, float valor);
void push_simb(Pilha* pi, char simb);
void pop(Pilha* pi);
bool pop_dos_2_primeiros(Pilha* pi);
void imprimirPilha(Pilha* pi);
void imprimirPilhaResultado(Pilha* pi);
bool ehNum(char c);
bool ehSimbolo(Pilha* pi, char c);
bool ehAbrido(Pilha* pi, char c);
void Caractere_invalido(char c);
bool ehFechado(Pilha* pi, char c);
void addnum(Pilha* pi,int* indice, char input[50]);
void calcularPiCalc(Pilha* pi,Pilha* pi_calc);
void InserirPiCalc(Pilha* pi, Pilha* pi_calc);
void verificacao(Pilha* pi);

#endif