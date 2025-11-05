#include "calc copy.c"

int main(){
    char input[50];
    int indice = 0;
    Pilha *pi = criarPilha();
    printf(">>> ");

    fgets(input,sizeof(input),stdin);
    char caractere = input[indice];

    //Ler todo o input
    // Reconhecer cada caractere {
    // Pegar o "(", "[" ou "{"
    // Quando achar o primeiro símbolo, criar uma pilha.
    // A pilha vai receber o resultado da operação que estiver dentro dela até achar a versão fechada do símbolo.


    while(caractere != '\n'){

        //printf("%d- %c ",indice,input[*indice]);

        if(ehNum(caractere)){
            addnum(pi,&indice,input);
        }
        if(ehSimbolo(pi,caractere));


        if(caractere == '(' || caractere == '[' || caractere == '{');
            //acharInternos(&indice, caractere, &input[50]);


        indice++;
        caractere = input[indice];

        //printf("\n");

    }

    imprimirPilha(pi);
    
    return 0;

}