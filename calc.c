#include "calc.h"

Pilha* criarPilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi == NULL) return NULL;

    *pi = NULL;

    return pi;

}

void push(Pilha* pi, int valor){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 0;
    novo->valor = valor;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

    if((*pi)->prox != NULL && (*pi)->prox->simb == '-' && (*pi)->valor_simb == 0){

        No* aux = *pi;
        while(aux->prox != NULL && aux->valor_simb != 0 && aux->valor_simb != 1){
            aux = aux->prox;
        }
        if(aux->valor_simb == 1){
            aux = (*pi)->prox;
            (*pi)->prox = (*pi)->prox->prox;
            free(aux);
        }else if(aux->valor_simb == 0){
            (*pi)->prox->simb = '+';
        }
        (*pi)->valor = (*pi)->valor * (-1);
    }

}

void push_simb(Pilha* pi, char simb){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 1;
    novo->simb = simb;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void push_parentesesAbrido(Pilha* pi, char simb){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 2;
    novo->simb = simb;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void push_parentesesFechado(Pilha* pi, char simb){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 3;
    novo->simb = simb;
    novo->interior = NULL;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void pop(Pilha* pi){
    if(pi == NULL) return;

    No* remover = *pi;

    *pi = remover->prox;

    free(remover);

}

void imprimirPilha(Pilha* pi){

    int cont = 1;

    No* aux = *pi;

    while(aux != NULL){

        if(aux->valor_simb==0){
            printf("%d- %d\n",cont,aux->valor);
        }else if(aux->valor_simb==1){
            printf("%d- %c\n",cont,aux->simb);
        }else if(aux->valor_simb==2){
            printf("%d- %c\n",cont,aux->simb);
        }
        
        cont++;
        aux = aux->prox;
    }

}

void imprimirPilhaResultado(Pilha* pi){

    int cont = 1;

    No* aux = *pi;

    while(aux != NULL){

        printf("\nResultado = %d", aux->valor);
        
        cont++;
        aux = aux->prox;
    }

}

bool ehNum(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }else{
        return false;
    }
}

bool ehSimbolo(Pilha* pi, char c){
    if(c == '+'||c == '-'||c == '/'||c == '*'){
        push_simb(pi,c);
        return true;
    }else{
        return false;
    }
}

bool ehAbrido(Pilha* pi, char c){
    if(c == '('||c == '['||c == '{'){
        push_parentesesAbrido(pi,c);
        return true;
    }else{
        return false;
    }
}

bool ehFechado(Pilha* pi, char c){
    if(c == ')' || c == ']' || c == '}'){
        push_parentesesFechado(pi,c);
        return true;
    }else{
        return false;
    }
}

bool pop_dos_2_primeiros(Pilha* pi){
    if(pi==NULL) return false;
    
    No* delete;
    No* delete_extra;

    if(*pi != NULL && (*pi)->prox != NULL){
        delete = *pi;
        delete_extra = (*pi)->prox;
    }else{
        printf("EXPRESSAO INVALIDA - Operacao aberta incorretamente");
        exit(1);
        return false;
    }

    if(delete_extra->prox == NULL){
    *pi = NULL;
    }else{
        *pi = delete_extra->prox;
    }
    free(delete);
    free(delete_extra);
    return true;
}

void Caractere_invalido(char c){
    if(c != '0'&&c != '1'&&c != '2'&&c != '3'&&c != '4'&&c != '5'&&c != '6'&&c != '7'&&
        c != '8'&&c != '9'&&c != '('&&c != '['&&c != '{'&&c != ')' && c != ']' && c != '}'&&
        c != '+'&&c != '-'&&c != '/'&&c != '*'&&c != ' '){
        printf("EXPRESSAO INVALIDA - Caractere invalido identificado");
        exit(1);
    }
}

void addnum(Pilha* pi,int* indice, char input[50]){
    int indice_temp = *indice;
    while(ehNum(input[indice_temp + 1])){
        indice_temp++;
    }
    indice_temp = (*indice) - indice_temp;

    if(indice_temp < 0)indice_temp = indice_temp * (-1);

    char input_temp[indice_temp + 1];
    int indice_input_temp = 0;

    for(int i = *indice; i < (*indice + indice_temp+1); i++){
        input_temp[indice_input_temp] = input[i];
        indice_input_temp++;
    }

    int num_push = atoi(input_temp);

    push(pi,num_push);

    *indice = *indice + indice_temp;
}

void calcularPiCalc(Pilha* pi,Pilha* pi_calc){

    if (pi_calc == NULL || *pi_calc == NULL) return; 
    
    No* aux = *pi_calc;
    while(aux->prox != NULL && aux->prox->prox != NULL){
        if((aux->prox->simb == '*' || aux->prox->simb == '/') && aux->valor_simb == 0 && aux->prox->valor_simb == 1 &&
         aux->prox->prox->valor_simb == 0 && aux->prox != NULL && aux->prox->prox != NULL){

            No* delete_simb = aux->prox;
            No* delete_num = aux->prox->prox;     

            if(aux->prox->simb == '*'){
            aux->valor = aux->valor * aux->prox->prox->valor;
            }else if(aux->prox->simb == '/'){

             if (aux->prox->prox->valor == 0) {
                printf("EXPRESSAO INVALIDA - Nao exite divisao por 0");
                exit(1);
                return;
            }
            aux->valor = aux->valor / aux->prox->prox->valor;
            }
            
            aux->prox = delete_num->prox;

            free(delete_simb);
            free(delete_num);

        }else{
        aux = aux->prox;
        }
    }
    aux = *pi_calc;

    while(aux->valor_simb == 0 && aux->prox != NULL && aux->prox->prox != NULL && aux->prox->valor_simb == 1 && aux->prox->prox->valor_simb == 0){

        No* delete_simb = aux->prox;
        No* delete_num = aux->prox->prox;

        if(aux->prox->simb == '+'){
            aux->valor = aux->valor + aux->prox->prox->valor;
        }else if(aux->prox->simb == '-'){
            aux->valor = aux->valor - aux->prox->prox->valor;
        }

        aux->prox = delete_num->prox;

        free(delete_simb);
        free(delete_num);
    }

    if(aux != NULL && aux->prox != NULL && aux->valor_simb == 1 && aux->prox->valor_simb == 0){
        if(aux->simb == '+'){
            push(pi,(aux->prox->valor));
            No* delete = aux->prox;
            free(aux);
            free(delete);
            *pi_calc = NULL;
        }else if(aux->simb == '-'){
            push(pi,(aux->prox->valor) * (-1));
            No* delete = aux->prox;
            free(aux);
            free(delete);
            *pi_calc = NULL;
        }else{
            printf("EXPRESSAO INVALIDA - Multiplicacao ou Divisao sozinha com um numero");
            exit(1);
        }
    }else{
        push(pi,aux->valor);
        free(aux);
        *pi_calc = NULL;
    }
}

void InserirPiCalc(Pilha* pi, Pilha* pi_calc){
    if(pi == NULL || pi_calc == NULL) return;

    No* aux = *pi;

    if((*pi)->valor_simb == 3){

        while(aux != NULL && aux->valor_simb != 2){
        
            if(aux->valor_simb == 0){
                push(pi_calc,aux->valor);

            }else if(aux->valor_simb == 1){
                push_simb(pi_calc,aux->simb);
            }
            
            No* no_delete = aux;

            if((*pi)->prox != NULL){
            *pi = (*pi)->prox;
            aux = aux->prox;
            }else{
                *pi = NULL;
                aux = NULL;
            }

            free(no_delete);
        }
        
        No* no_delete = *pi;
        *pi = (*pi)->prox;
        free(no_delete);
        calcularPiCalc(pi, pi_calc);
        
    }else{
        while(aux != NULL){

                if(aux->valor_simb == 0){
                    push(pi_calc,aux->valor);

                }else if(aux->valor_simb == 1){
                    push_simb(pi_calc,aux->simb);
                }
            
            No* no_delete = aux;

            if((*pi)->prox != NULL){
            *pi = (*pi)->prox;
            aux = aux->prox;
            }else{
                *pi = NULL;
                aux = NULL;
            }
            
            free(no_delete);
        }
        
        calcularPiCalc(pi, pi_calc);
    }
}

void verificacao(Pilha* pi){
    if(pi == NULL || *pi == NULL || (*pi)->prox == NULL) return;

    if(*pi != NULL && (*pi)->prox != NULL && (*pi)->prox->prox != NULL &&
    (*pi)->valor_simb == 0 && (*pi)->prox->valor_simb == 0){
        printf("EXPRESSAO INVALIDA! - dois numeros em sequencia");
        exit(1);

    }else if(*pi != NULL && (*pi)->prox != NULL && (*pi)->valor_simb == 1 && (*pi)->prox->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - dois simbolos em sequencia");
        exit(1);

    }else if(*pi != NULL && (*pi)->prox != NULL && (*pi)->prox->prox != NULL &&
        (*pi)->valor_simb == 2 &&(*pi)->prox->valor_simb == 1 && (*pi)->prox->prox->valor_simb == 3 ){
        printf("EXPRESSAO INVALIDA! - simbolo sozinho dentro de um parenteses");
        exit(1);
        
    }else if(*pi != NULL && (*pi)->valor_simb == 1 && (*pi)->prox == NULL){
        printf("EXPRESSAO INVALIDA! - simbolo no fim da opercacao");
        exit(1);

    }
}