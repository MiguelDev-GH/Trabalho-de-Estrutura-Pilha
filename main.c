#include "calc.c"

int main(){
    char input[50];
    int indice = 0;
    Pilha *pi = criarPilha();
    Pilha *pi_calc = criarPilha();
    printf(">>> ");

    fgets(input,sizeof(input),stdin);
    char caractere = input[indice];

    //Ler todo o input
    // Reconhecer cada caractere {
    // Pegar o "(", "[" ou "{"
    // Quando achar o primeiro símbolo, criar uma pilha.
    // A pilha vai receber o resultado da operação que estiver dentro dela até achar a versão fechada do símbolo.


    while(caractere != '\n'){

        if(ehNum(caractere)) addnum(pi,&indice,input);
        
        if(ehSimbolo(pi,caractere));

        if(ehAbrido(pi,caractere));

        if(ehFechado(pi,caractere)) calculo(pi,pi_calc);

        indice++;
        caractere = input[indice];

    }

    calculo(pi,pi_calc);

    imprimirPilha(pi);

    printf("\n === Pi Calc ===\n");

    imprimirPilha(pi_calc);
    
    return 0;
    
}
