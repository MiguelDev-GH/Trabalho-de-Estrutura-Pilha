#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char input[50];

int indice = 0;
char caractere = ' ';

char Numeros = {'0','1','2','3','4','5','6','7','8','9'};

//pilha *pi = criar_pilha();

bool ehNum(char* c){
    if(*c == '0'||*c == '1'||*c == '2'||*c == '3'||*c == '4'||*c == '5'||*c == '6'||*c == '7'||*c == '8'||*c == '9'){
        return true;
    }else{
        return false;
    }
}

int percorreEspaço(int indice){
    int indice_temp = indice;
    while(ehNum(input[indice_temp])){
        indice_temp++;
    }
    indice_temp = indice - indice_temp;

    char input_temp[indice_temp];
    int indice_input_temp = 0;

    for(int i = indice; i < (indice + indice_temp); i++){
        input_temp[indice_input_temp] = input[i];
        indice_input_temp++;
    }

    int num_push = atoi(input_temp);

    //push(*pi,num_push);

    return indice + indice_temp;
}

char percorrerAte(int indice){

    printf(">>> ");

    if(caractere == '('){

        for(int i = indice+1; i < sizeof(input);i++){
            printf(" %c ",input[i]);
        }

    }

    printf(" <<<");
}