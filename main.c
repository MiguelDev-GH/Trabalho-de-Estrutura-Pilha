#include "calc.c"

/*
Arrumar:

- Negativos
- Expressões como 1 + (2)

*/


int main(){
    char input[50];
    int indice = 0;
    int indice_prox = 1;
    Pilha *pi = criarPilha();
    Pilha *pi_calc = criarPilha();
    Pilha *pi_verificacao = criarPilha();
    printf(">>> ");

    fgets(input,sizeof(input),stdin);
    char caractere = input[indice];

    while(caractere != '\n'){
        
        if(ehAbrido(pi_verificacao,caractere));

        if(ehFechado(pi_verificacao,caractere)){
            if(!pop_dos_2_primeiros(pi_verificacao)){
                exit(1);
            }
        };

        Caractere_invalido(caractere);

        indice++;
        indice_prox++;
        caractere = input[indice];

    }

    if(*pi_verificacao != NULL){
        printf("EXPRESSAO INVALIDA");
        exit(1);
    }else{
        free(pi_verificacao);
    }

    indice = 0;
    caractere = input[indice];

    while(caractere != '\n'){

        if(ehNum(caractere)) addnum(pi,&indice,input);
        
        if(ehSimbolo(pi,caractere)){
    
        };

        if(ehAbrido(pi,caractere));

        if(ehFechado(pi,caractere)) InserirPiCalc(pi,pi_calc);

        indice++;
        caractere = input[indice];

    }

    InserirPiCalc(pi,pi_calc);
    
    imprimirPilhaResultado(pi);

    return 0;
    
}
