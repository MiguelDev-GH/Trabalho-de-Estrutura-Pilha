#include "calc.c"

int main(){
    char input[50];
    int indice = 0;
    int indice_prox = 1;
    Pilha *pi = criarPilha();
    Pilha *pi_calc = criarPilha();
    Pilha *pi_verificacao = criarPilha();
    printf("\nDigite a expressao: \n");
    printf(">>> ");

    fgets(input,sizeof(input),stdin);
    char caractere = input[indice];
    int existe_num = 0;
    while(caractere != '\n'){
        
        if(ehAbrido(pi_verificacao,caractere)){     
        }else if(ehFechado(pi_verificacao,caractere)){
            pop_dos_2_primeiros(pi_verificacao);
        }else if(ehNum(caractere)){
            existe_num = 1;
        }

        Caractere_invalido(caractere);

        indice++;
        indice_prox++;
        caractere = input[indice];

    }

    if(existe_num == 0){
        printf("EXPRESSAO INVALIDA - nenhum numero existente");
        exit(1);
    }

    if(*pi_verificacao != NULL){
        printf("EXPRESSAO INVALIDA - Operacao nao fechada corretamente");
        exit(1);
    }else{
        free(pi_verificacao);
    }

    indice = 0;
    caractere = input[indice];

    while(caractere != '\n'){

        if(ehNum(caractere)){

            addnum(pi,&indice,input);
            verificacao(pi);
        }else if(ehSimbolo(pi,caractere)){
            verificacao(pi);
        }else if(ehAbrido(pi,caractere)){
            verificacao(pi);
        }else if(ehFechado(pi,caractere)){ 
            verificacao_simbolo_sozinho(pi);
            verificacao(pi);
            InserirPiCalc(pi,pi_calc);
        }

        indice++;
        caractere = input[indice];

    }
    verificacao_loop(pi);

    verificacao_simbolo_no_final(pi);
    
    InserirPiCalc(pi,pi_calc);
    
    printf("Expressao escrita de forma CORRETA!\n");
    imprimirPilhaResultado(pi);

    return 0;
    
}