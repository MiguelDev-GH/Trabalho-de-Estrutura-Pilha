#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char input[50];

    printf(">>> ");

    fgets(input,sizeof(input),stdin);

    //Ler todo o input

    // Reconhecer cada caractere {
    // Pegar o "(", "[" ou "{"
    // Quando achar o primeiro símbolo, criar uma pilha.
    // A pilha vai receber o resultado da operação que estiver dentro dela até achar a versão fechada do símbolo.

    int indice = 0;
    char caractere = 'a';

    while(caractere != '\n'){

        printf("%d- %c ",indice,input[indice]);

        if(caractere == '(') printf("Simbolo");

        indice++;
        caractere = input[indice];

        printf("\n");

    }

    return 0;

}