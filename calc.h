
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

// Grafo

typedef struct ElementoGrafo{
    int vertice;
    struct ElementoGrafo *prox;
    
} ElementoGrafo;


typedef struct Grafo{
    int num_vertices;
    ElementoGrafo** adj;
} Grafo;

extern Pilha *pi_num;
extern Pilha *pi_simb;
extern Pilha *pi_verificacao;
extern PilhaHistorico *historico;

Pilha* criarPilha();
PilhaHistorico* criar_pilha_historico();
void push_historico(PilhaHistorico* pi_hist, char* input, float resultado);
void mostrar_historico(PilhaHistorico *pi_hist);
void calcular(char* input);
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
void Caractere_invalido(char c);
bool ehFechado(Pilha* pi, char c);
void addnum(Pilha* pi, int* indice, char input[50]);
void verificacao(Pilha* pi);
void verificacao_simbolo_sozinho(Pilha* pi);
void verificacao_simbolo_no_final(Pilha* pi);
void verificacao_loop(Pilha* pi);
void liberar_pilha(Pilha* pi);
void realizar_calculo(Pilha* pi_verificacao, Pilha* pi_num, Pilha* pi_simb);