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

void percorreEspaco(Pilha* pi,int* indice, char input[50]){
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

char percorrerAte(int indice,char caractere, char input[50]){

    printf(">>> ");

    if(caractere == '('){

        for(int i = indice+1; i < sizeof(input[50]);i++){
            printf(" %c ",input[i]);
        }

    }

    printf(" <<<");
}