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
    struct No* prox;
} No;

typedef struct No* Pilha;

typedef struct NoHistorico{
    char input[50];
    float resultado;
    struct NoHistorico* prox;
} NoHistorico;

typedef struct NoHistorico* PilhaHistorico;

Pilha* criarPilha();
PilhaHistorico* criar_pilha_historico();
void push_historico(PilhaHistorico* pi_hist,char* input, float resultado);
void mostrar_historico(PilhaHistorico *pi_hist);
void calcular();
void push(Pilha* pi, float valor);
void push_menos(Pilha* pi, float valor);
void push_simb(Pilha* pi, char simb, int valor_simb);
void pop(Pilha* pi);
bool pop_dos_2_primeiros(Pilha* pi);
void imprimirPilha(Pilha* pi);
void imprimirPilhaResultado(Pilha* pi);
bool ehNum(char c);
bool ehSimbolo(Pilha* pi, char c);
bool ehAbrido(Pilha* pi, char c);
bool ehRaiz(Pilha* pi,char c);
void Caractere_invalido(char c);
bool ehFechado(Pilha* pi, char c);
void addnum(Pilha* pi,int* indice, char input[50]);
void calcularPiCalc(Pilha* pi,Pilha* pi_calc);
void InserirPiCalc(Pilha* pi, Pilha* pi_calc);
void verificacao(Pilha* pi);
void verificacao_simbolo_sozinho(Pilha* pi);
void verificacao_simbolo_no_final(Pilha* pi);
void verificacao_loop(Pilha* pi);

Pilha *pi = NULL;
Pilha *pi_calc = NULL;
Pilha *pi_verificacao = NULL;
PilhaHistorico *historico = NULL;

#endif