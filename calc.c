#include "calc copy.c"

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

        if(ehNum(caractere)){
            indice = (percorreEspaço(indice));
        }

        if(caractere == '(' || caractere == '[' || caractere == '{'){
            percorrerAte(indice); 
        }

        indice++;
        caractere = input[indice];

        printf("\n");

    }

    return 0;

}