#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[50];

int indice = 0;
char caractere = 'a';

char Numeros = {'0','1','2','3','4','5','6','7','8','9'} ;

void ehNum(char* c){}

char percorrerAte(int indice){

    printf(">>> ");

    if(caractere == '('){

        for(int i = indice+1; i < sizeof(input);i++){
            printf(" %c ",input[i]);
        }

    }

    printf(" <<<");
}

int main(){

    printf(">>> ");

    fgets(input,sizeof(input),stdin);

    //Ler todo o input
    // Reconhecer cada caractere {
    // Pegar o "(", "[" ou "{"
    // Quando achar o primeiro símbolo, criar uma pilha.
    // A pilha vai receber o resultado da operação que estiver dentro dela até achar a versão fechada do símbolo.


    while(caractere != '\n'){

        printf("%d- %c ",indice,input[indice]);

        if(caractere == '(' || caractere == '[' || caractere == '{'){
            percorrerAte(indice); 
        }

        indice++;
        caractere = input[indice];

        printf("\n");

    }

    return 0;

}