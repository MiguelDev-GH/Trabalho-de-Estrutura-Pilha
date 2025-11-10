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

    while(caractere != '\n'){
        
        if(ehAbrido(pi_verificacao,caractere));

        if(ehFechado(pi_verificacao,caractere)){
            pop_dos_2_primeiros(pi_verificacao);
        }

        Caractere_invalido(caractere);

        indice++;
        indice_prox++;
        caractere = input[indice];

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
        }
        
        if(ehSimbolo(pi,caractere)){
            verificacao(pi);
        }

        if(ehAbrido(pi,caractere)){
            verificacao(pi);
        }

        if(ehFechado(pi,caractere)){ 
            verificacao_simbolo_sozinho_em_parenteses(pi);
            verificacao(pi);
            InserirPiCalc(pi,pi_calc);
        }

        indice++;
        caractere = input[indice];

    }

    verificacao_simbolo_no_final(pi);
    
    InserirPiCalc(pi,pi_calc);
    
    printf("Expressao escrita de forma CORRETA!\n");
    imprimirPilhaResultado(pi);

    return 0;
    
}