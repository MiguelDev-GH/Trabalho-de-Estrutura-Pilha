#include "calc.c"

int main(){
    char input[50];
    int indice = 0;
    Pilha *pi = criarPilha();
    Pilha *pi_calc = criarPilha();
    printf(">>> ");

    fgets(input,sizeof(input),stdin);
    char caractere = input[indice];

    while(caractere != '\n'){

        if(ehNum(caractere)) addnum(pi,&indice,input);
        
        if(ehSimbolo(pi,caractere));

        if(ehAbrido(pi,caractere));

        if(ehFechado(pi,caractere)) InserirPiCalc(pi,pi_calc);

        indice++;
        caractere = input[indice];

    }

    InserirPiCalc(pi,pi_calc);
    
    imprimirPilhaResultado(pi);

    return 0;
    
}
