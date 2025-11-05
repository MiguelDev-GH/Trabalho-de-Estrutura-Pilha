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
            percorreEspaco(pi,&indice,input);
        }
        /*x
        if(caractere == '(' || caractere == '[' || caractere == '{'){
            percorrerAte(*indice,caractere); 
        }
        */

        indice++;
        caractere = input[indice];

        //printf("\n");

    }

    imprimirPilha(pi);
    
    return 0;

}