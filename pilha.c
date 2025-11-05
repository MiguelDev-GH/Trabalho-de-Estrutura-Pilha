#include "pilha.h"

Pilha* criarPilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi == NULL) return NULL;

    *pi = NULL;

    return pi;

}

void push(Pilha* pi, int valor){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 0;
    novo->valor = valor;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void push_simb(Pilha* pi, char simb){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 1;
    novo->simb = simb;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void pop(Pilha* pi){
    if(pi == NULL) return;

    No* remover = *pi;

    *pi = remover->prox;

    free(remover);

}

// void apagarPilha(Pilha* pi){}

void imprimirPilha(Pilha* pi){

    int cont = 1;

    No* aux = *pi;

    while(aux != NULL){

        if(aux->valor_simb==0){
            printf("%d- %d\n",cont,aux->valor);
        }else{
            printf("%d- %c\n",cont,aux->simb);
        }
        
        cont++;
        aux = aux->prox;
    }

}


// void removerNo(){};