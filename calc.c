#include "calc.h"

void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

Pilha* criarPilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi == NULL) return NULL;

    *pi = NULL;

    return pi;

}

void push(Pilha* pi, float valor){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;


    novo->valor_simb = 0;
    novo->valor = valor;

    if(*pi == NULL) novo->prox = NULL; 
    else novo->prox = *pi;

    *pi = novo;

}

void push_menos(Pilha* pi, float valor){
    if(pi == NULL) return;

    if(*pi != NULL && (*pi)->valor_simb == 1 && (*pi)->simb == '-' && ((*pi)->prox == NULL || (*pi)->prox->valor_simb != 0)) {

            No* temp = *pi;
            *pi = (*pi)->prox;
            free(temp);

            valor = valor * (-1);

    }
    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = 0;
    novo->valor = valor;
    
    novo->prox = *pi;
    *pi = novo;
}

void push_simb(Pilha* pi, char simb, int valor_simb){
    if(pi == NULL) return;

    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = valor_simb;
    novo->simb = simb;

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
            printf("%d- %.2f\n",cont,aux->valor);
        }else if(aux->valor_simb==1){
            printf("%d- %c\n",cont,aux->simb);
        }else if(aux->valor_simb==2){
            printf("%d- %c\n",cont,aux->simb);
        }else if(aux->valor_simb==3){
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

        printf("\nResultado = %.2f", aux->valor);
        
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
    if(c == '+'||c == '-'||c == '/' || c == '*' || c == '^' || c == 'r'){
        push_simb(pi,c,1);
        return true;
    }else{
        return false;
    }
}

bool ehAbrido(Pilha* pi, char c){
    if(c == '('||c == '['||c == '{'){
        push_simb(pi,c,2);
        return true;
    }else{
        return false;
    }
}

bool ehFechado(Pilha* pi, char c){
    if(c == ')' || c == ']' || c == '}'){
        push_simb(pi,c,3);
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

    if(delete->simb == ')'&&delete_extra->simb != '('){
        printf("EXPRESSAO INVALIDA - Operacao com simbolos incorretos %c != %c",delete_extra->simb,delete->simb);
        exit(1);
        return false;
    
    }else if(delete->simb == ']'&&delete_extra->simb != '['){
        printf("EXPRESSAO INVALIDA - Operacao com simbolos incorretos %c != %c",delete_extra->simb,delete->simb);
        exit(1);
        return false;
    }else if(delete->simb == '}'&&delete_extra->simb != '{'){
        printf("EXPRESSAO INVALIDA - Operacao com simbolos incorretos %c != %c",delete_extra->simb,delete->simb);
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
        c != '+'&&c != '-'&&c != '/'&&c != '*'&&c != ' ' && c != '^'&& c != 'r'){
        printf("EXPRESSAO INVALIDA - Caractere invalido identificado");
        exit(1);
    }
}

void addnum(Pilha* pi, int* indice, char input[50]) {
    int indice_inicio = *indice;
    int indice_ultimo_digito = *indice;

    while (ehNum(input[indice_ultimo_digito + 1])) {
        indice_ultimo_digito++;
    }

    int num_len = (indice_ultimo_digito - indice_inicio) + 1;

    char input_temp[num_len ]; 
    int indice_input_temp = 0;

    for (int i = indice_inicio; i <= indice_ultimo_digito; i++) {
        input_temp[indice_input_temp] = input[i];
        indice_input_temp++;
    }
    
    int num_push = atoi(input_temp);

    push_menos(pi, (float)num_push); 

    *indice = indice_ultimo_digito;
}

void calcularPiCalc(Pilha* pi,Pilha* pi_calc){

    if (pi_calc == NULL || *pi_calc == NULL) return; 
    
    No* aux = *pi_calc;

    if(aux != NULL && aux->prox != NULL && aux->prox->prox == NULL && aux->valor_simb == 0 && aux->prox->valor_simb == 1){
        printf("EXPRESSAO INVALIDA - Numero seguido de simbolo sem nada depois");
        exit(1);
    }

    while(aux->prox != NULL && aux->prox->prox != NULL) {
        if((aux->prox->simb == '^' || aux->prox->simb == 'r') && aux->valor_simb == 0 && aux->prox->valor_simb == 1 &&
         aux->prox->prox->valor_simb == 0 && aux->prox != NULL && aux->prox->prox != NULL){

            No* delete_simb = aux->prox;
            No* delete_num = aux->prox->prox;     

            if(aux->prox->simb == '^'){ 
                aux->valor = pow((double)aux->valor,(double)aux->prox->prox->valor);
            } else if(aux->prox->simb == 'r'){
                if(aux->prox->prox->valor<=0){
                    printf("EXPRESSAO INVALIDA - Nao existe raiz de indice negativo ou zero");
                    exit(1);
                }else if(aux->valor<0 && ((int)aux->prox->prox->valor % 2) == 0){
                    printf("EXPRESSAO INVALIDA - Nao existe raiz de numero negativo e com o indice par");
                    exit(1);
                }else if(aux->valor<0 && ((int)aux->prox->prox->valor % 2) != 0){

                    aux->valor = aux->valor * (-1);
                    aux->valor = pow(aux->valor, 1.0 / (double)aux->prox->prox->valor);
                    aux->valor = aux->valor * (-1);

                }else{
                    aux->valor = pow((double)aux->valor,1/(double)aux->prox->prox->valor);
                }
            }
            aux->prox = delete_num->prox;

            free(delete_simb);
            free(delete_num);

        }else{
        aux = aux->prox;
        }
    }

    aux = *pi_calc;
    
    while(aux->prox != NULL && aux->prox->prox != NULL) {
        if((aux->prox->simb == '*' || aux->prox->simb == '/') && aux->valor_simb == 0 && aux->prox->valor_simb == 1 &&
         aux->prox->prox->valor_simb == 0 && aux->prox != NULL && aux->prox->prox != NULL){

            No* delete_simb = aux->prox;
            No* delete_num = aux->prox->prox;     

            if(aux->prox->simb == '*'){
                aux->valor = aux->valor * aux->prox->prox->valor;

            }else if(aux->prox->simb == '/'){
                if (aux->prox->prox->valor == 0)
                 {
                    printf("EXPRESSAO INVALIDA - Nao existe divisao por 0 (Zero)");
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
             printf("EXPRESSAO INVALIDA - Multiplicacao, Divisao ou Potenciacao sozinha com um numero");
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
                push_simb(pi_calc,aux->simb,1);
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
                    push_simb(pi_calc,aux->simb,1);
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

    if(*pi != NULL && (*pi)->prox != NULL &&
    (*pi)->valor_simb == 0 && (*pi)->prox->valor_simb == 0){
        printf("EXPRESSAO INVALIDA! - Dois numeros ou simbolos em sequencia");
        exit(1);

    }else if(*pi != NULL && (*pi)->prox != NULL && (*pi)->valor_simb == 1 && (*pi)->prox->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - Dois simbolos em sequencia");
        exit(1);

    }
}

void verificacao_simbolo_sozinho(Pilha* pi){
    if(*pi != NULL && (*pi)->prox != NULL && (*pi)->prox->prox != NULL &&
     (*pi)->valor_simb == 3 && (*pi)->prox->valor_simb == 1 && (*pi)->prox->prox->valor_simb == 2){
        printf("EXPRESSAO INVALIDA! - Simbolo sozinho dentro de um parenteses");
        exit(1);
    }
}

void verificacao_simbolo_no_final(Pilha* pi){
    if(*pi != NULL && (*pi)->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - Simbolo no fim da opercacao");
        exit(1);
    }
}

void verificacao_loop(Pilha* pi){
    if(pi == NULL || *pi == NULL || (*pi)->prox == NULL) return;

    No* aux = *pi;

    while(aux->prox != NULL){
    if(aux != NULL && aux->prox != NULL &&
    aux->valor_simb == 0 && aux->prox->valor_simb == 0){
        printf("EXPRESSAO INVALIDA! - Dois numeros ou simbolos em sequencia");
        exit(1);

    }else if(aux != NULL && aux->prox != NULL && aux->valor_simb == 1 && aux->prox->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - Dois simbolos em sequencia");
        exit(1);

    }
    aux = aux->prox;
    }
}

void liberar_pilha(Pilha* pi){
    if(pi == NULL) return;

    No* aux = *pi;
    No* excluir = aux;

    while(aux != NULL){
        excluir = aux;
        aux = aux->prox;
        free(excluir);
    }
    *pi = NULL;
}

// Funções histórico: Aqui só vai ter funções para o histórico

PilhaHistorico* criar_pilha_historico(){
    PilhaHistorico* pi_hist = (PilhaHistorico*) malloc(sizeof(PilhaHistorico));
    if(pi_hist == NULL) return NULL;

    *pi_hist = NULL;

    return pi_hist;
}

void push_historico(PilhaHistorico* pi_hist,char* input, float resultado){
    if(pi_hist == NULL) return;

    NoHistorico* novo = malloc(sizeof(NoHistorico));
    if(novo == NULL) return;

    novo->resultado = resultado;
    strcpy(novo->input, input);

    if(*pi_hist == NULL) novo->prox = NULL; 
    else novo->prox = *pi_hist;

    *pi_hist = novo;
}

void mostrar_historico(PilhaHistorico *pi_hist){
    if(pi_hist == NULL) return;

    system("cls");

    printf("=---= HISTORICO =---=\n");

    if(*pi_hist == NULL){
        printf("\nSem calculos ainda!\n");
        printf("\nAperte ENTER para voltar");
        getchar();
        return;
    }

    NoHistorico* aux = *pi_hist;

    while(aux != NULL){
        printf("\n>>> %s Resultado: %.2f\n", aux->input, aux->resultado);
        aux = aux->prox;
    }

    printf("\nAperte ENTER para voltar");
    getchar();
}
// Cabou as funções sobre o histórico

void separar_num_simb(Pilha* pi_verificacao, Pilha* pi_num, Pilha* pi_simb){
    if(pi_num == NULL ||pi_simb == NULL ||pi_verificacao == NULL) return;
    No* aux = *pi_verificacao;
    while(aux != NULL){
        if(aux->valor_simb == 0){
            push(pi_num,aux->valor);
        }else{
            push_simb(pi_simb,aux->simb,aux->valor_simb);
        }
        aux = aux->prox;
    }
}

void calcular(char* input,int input_size){

    liberar_pilha(pi_num);
    liberar_pilha(pi_simb);
    liberar_pilha(pi_verificacao);

    int indice = 0;
    int indice_prox = 1;

    char op[2];

    system("cls");

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
        printf("EXPRESSAO INVALIDA - Nenhum numero existente");
        exit(1);
    }

    if(*pi_verificacao != NULL){
        printf("EXPRESSAO INVALIDA - Operacao nao fechada corretamente");
        exit(1);
    }

    indice = 0;
    caractere = input[indice];

    indice = 0;
    caractere = input[indice];

    while(caractere != '\n'){

        if(caractere == ' '){
            indice++;
            caractere = input[indice];
        }else if(ehNum(caractere)){
            addnum(pi_verificacao,&indice,input);
            verificacao(pi_verificacao);
        }else if(ehSimbolo(pi_verificacao,caractere)){
            verificacao(pi_verificacao);
        }else if(ehAbrido(pi_verificacao,caractere)){
            verificacao(pi_verificacao);
        }else if(ehFechado(pi_verificacao,caractere)){ 
            verificacao_simbolo_sozinho(pi_verificacao);
            verificacao(pi_verificacao);
        }

        indice++;
        caractere = input[indice];

    }
    verificacao_loop(pi_verificacao);

    verificacao_simbolo_no_final(pi_verificacao);
    
    //InserirPiCalc(pi,pi_calc);
    
    printf("Expressao escrita de forma CORRETA!\n");
    imprimirPilhaResultado(pi_num);

    push_historico(historico,input,(*pi_num)->valor);

    printf("\nDeseja fazer outro calculo? (Digite > S < para continuar)\n");

    fgets(op,sizeof(op),stdin);

    limpar_buffer();

    if(strcmp(op,"S") == 0 || strcmp(op,"s") == 0){
        system("cls");
        printf("\nDigite a expressao: \n");
        printf(">>> ");
        fgets(input,sizeof(input),stdin);
        calcular(input,input_size);
    }
}