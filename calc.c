#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pilha.c"

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

    // Se achar parenteses fechando, voltar até onde ele abre e substituir pelo valor da operação


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

void calcularPiCalc(Pilha* pi,Pilha* pi_calc){

    if (pi_calc == NULL || *pi_calc == NULL) return; 
    
    No* aux = *pi_calc;

    while(aux->valor_simb == 0 && aux->prox != NULL && aux->prox->prox != NULL && aux->prox->valor_simb == 1 && aux->prox->prox->valor_simb == 0){

        No* delete_simb = aux->prox;
        No* delete_num = aux->prox->prox;

        if(aux->prox->simb == '+'){
            aux->valor = aux->valor + aux->prox->prox->valor;
        } else if (aux->prox->simb == '-'){
            aux->valor = aux->valor - aux->prox->prox->valor;
        } else if (aux->prox->simb == '/'){
            
            if (aux->prox->prox->valor == 0) {
                printf("nao exite divisao por ");
                return;
            }
            aux->valor = aux->valor / aux->prox->prox->valor;

        } else if(aux->prox->simb == '*'){
            aux->valor = aux->valor * aux->prox->prox->valor;
        }
        aux->prox = delete_num->prox;

        free(delete_simb);
        free(delete_num);
    }
    if(aux->prox != NULL){
        printf("tu é burro em pai, sabe nem escrever direito");
    }else{
        push(pi,aux->valor);
        free(aux);
        *pi_calc = NULL;
    }
}

void InserirPiCalc(Pilha* pi, Pilha* pi_calc){
    if(pi == NULL || pi_calc == NULL) return;

    No* aux = *pi;

    if((*pi)->simb == ')' || (*pi)->simb == ']' || (*pi)->simb == '}'){

        while(aux != NULL && aux->simb != '(' && aux->simb != '[' && aux->simb != '{'){

            if(aux->valor_simb == 0){
                push(pi_calc,aux->valor);

            }else if(aux->simb != '(' && aux->simb != '[' && aux->simb != '{' && aux->simb != ')' && aux->simb != ']' && aux->simb != '}'){
                push_simb(pi_calc,aux->simb);
            }
            
            No* no_delete = aux;

            if((*pi)->prox != NULL){
            *pi = (*pi)->prox;
            aux = aux->prox;
            }else{
                *pi = NULL;
                aux = NULL;
            }

            free(no_delete);
        }
        
        No* no_delete = *pi;
        *pi = (*pi)->prox;
        free(no_delete);
        calcularPiCalc(pi, pi_calc);
        
    }else{
        while(aux != NULL){

            if(aux->valor_simb == 0){
                push(pi_calc,aux->valor);

            }else if(aux->simb != '(' && aux->simb != '[' && aux->simb != '{' && aux->simb != ')' && aux->simb != ']' && aux->simb != '}'){
                push_simb(pi_calc,aux->simb);
            }
            
            No* no_delete = aux;

            if((*pi)->prox != NULL){
            *pi = (*pi)->prox;
            aux = aux->prox;
            }else{
                *pi = NULL;
                aux = NULL;
            }
            
            free(no_delete);
        }
        
        calcularPiCalc(pi, pi_calc);
    }
}