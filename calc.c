#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pilha.c"

//pilha *pi = criar_pilha();

bool ehNum(char c){
    if(c == '0'||c == '1'||c == '2'||c == '3'||c == '4'||c == '5'||c == '6'||c == '7'||c == '8'||c == '9'){
        return true;
    }else{
        return false;
    }
}

bool ehSimbolo(Pilha* pi, char c){
    if(c == '+'||c == '-'||c == '/'||c == '*'){
        push_simb(pi,c);
        return true;
    }else{
        return false;
    }
}

bool ehAbrido(Pilha* pi, char c){
    if(c == '('||c == '['||c == '{'){
        push_simb(pi,c);
        return true;
    }else{
        return false;
    }
}

bool ehFechado(Pilha* pi, char c){
    if(c == ')' || c == ']' || c == '}'){
        push_simb(pi,c);
        return true;
    }else{
        return false;
    }
}


void addnum(Pilha* pi,int* indice, char input[50]){
    int indice_temp = *indice;
    while(ehNum(input[indice_temp + 1])){
        indice_temp++;
    }
    indice_temp = (*indice) - indice_temp;

    if(indice_temp < 0)indice_temp = indice_temp * (-1);

    char input_temp[indice_temp + 1];
    int indice_input_temp = 0;

    for(int i = *indice; i < (*indice + indice_temp+1); i++){
        input_temp[indice_input_temp] = input[i];
        indice_input_temp++;
    }

    int num_push = atoi(input_temp);

    push(pi,num_push);

    *indice = *indice + indice_temp;
}

void calculo(Pilha* pi, Pilha* pi_calc){
    if(pi == NULL || pi_calc == NULL) return;

    No* aux = *pi;

    if((*pi)->simb == ')' || (*pi)->simb == ']' || (*pi)->simb == '}'){

        aux = aux->prox;

        while(aux != NULL && aux->simb != '(' && aux->simb != '[' && aux->simb != '{'){
            if(aux->valor_simb == 0){
                push(pi_calc,aux->valor);
            }else if(aux->simb != '(' || aux->simb != '[' || aux->simb != '{'||aux->simb != ')' || aux->simb != ']' || aux->simb != '}'){
                push_simb(pi_calc,aux->simb);
            }
            
            *pi = (*pi)->prox;
            No* no_delete = aux;
            aux = aux->prox;
            free(no_delete);
        }
        
        No* no_delete = *pi;
        *pi = (*pi)->prox;
        free(no_delete);
        
    }
}