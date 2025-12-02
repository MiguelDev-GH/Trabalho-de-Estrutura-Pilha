#include "calc.h"

Pilha *pi_num = NULL;
Pilha *pi_simb = NULL;
Pilha *pi_verificacao = NULL;
PilhaHistorico *historico = NULL;

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
    novo->prox = *pi;
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
    push(pi,valor);
}

void push_simb(Pilha* pi, char simb, int valor_simb){
    if(pi == NULL) return;
    No* novo = malloc(sizeof(No));
    if(novo == NULL) return;

    novo->valor_simb = valor_simb;
    novo->simb = simb;
    novo->prox = *pi;
    *pi = novo;
}

void pop(Pilha* pi){
    if(pi == NULL || *pi == NULL) return;
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
        }else {
            printf("%d- %c\n",cont,aux->simb);
        }
        cont++;
        aux = aux->prox;
    }
}

void imprimirPilhaResultado(Pilha* pi){
    No* aux = *pi;
    while(aux != NULL){
        printf("\nResultado = %.2f\n", aux->valor);
        aux = aux->prox;
    }
}

bool ehNum(char c){
    return (c >= '0' && c <= '9') || c == '.';
}

bool ehSimbolo(Pilha* pi, char c){
    if(c == '+'||c == '-'||c == '/' || c == '*' || c == '^' || c == 'r'){
        push_simb(pi,c,1);
        return true;
    }
    return false;
}

bool ehAbrido(Pilha* pi, char c){
    if(c == '('||c == '['||c == '{'){
        push_simb(pi,c,2);
        return true;
    }
    return false;
}

bool ehFechado(Pilha* pi, char c){
    if(c == ')' || c == ']' || c == '}'){
        push_simb(pi,c,3);
        return true;
    }
    return false;
}

bool pop_dos_2_primeiros(Pilha* pi){
    if(pi==NULL || *pi == NULL) return false;
    
    No* delete = *pi;
    No* delete_extra = (*pi)->prox;

    if(delete_extra == NULL){
        printf("EXPRESSAO INVALIDA - Operacao aberta incorretamente\n");
        exit(1);
    }

    if((delete->simb == ')' && delete_extra->simb != '(') ||
       (delete->simb == ']' && delete_extra->simb != '[') ||
       (delete->simb == '}' && delete_extra->simb != '{')){
        printf("EXPRESSAO INVALIDA - Simbolos nao correspondem\n");
        exit(1);
    }

    *pi = delete_extra->prox;
    free(delete);
    free(delete_extra);
    return true;
}

void Caractere_invalido(char c){
    if(!ehNum(c) && 
       c != '(' && c != '[' && c != '{' && c != ')' && c != ']' && c != '}' &&
       c != '+' && c != '-' && c != '/' && c != '*' && c != ' ' && c != '^' && c != 'r' && c != '\n' && c != '\0'){
        printf("EXPRESSAO INVALIDA - Caractere invalido identificado: %c\n", c);
        exit(1);
    }
}

void addnum(Pilha* pi, int* indice, char input[50]) {
    int indice_inicio = *indice;
    int indice_atual = *indice;

    while (ehNum(input[indice_atual + 1])) {
        indice_atual++;
    }

    int len = (indice_atual - indice_inicio) + 1;
    char buffer[50]; 
    
    int j = 0;
    for (int i = indice_inicio; i <= indice_atual; i++) {
        buffer[j++] = input[i];
    }
    buffer[j] = '\0';
    
    float num_push = (float)atof(buffer);

    push_menos(pi, num_push); 

    *indice = indice_atual;
}

void verificacao(Pilha* pi){
    if(pi == NULL || *pi == NULL || (*pi)->prox == NULL) return;

    if((*pi)->valor_simb == 0 && (*pi)->prox->valor_simb == 0){
        printf("EXPRESSAO INVALIDA! - Dois numeros seguidos sem operador\n");
        exit(1);
    }else if((*pi)->valor_simb == 1 && (*pi)->prox->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - Dois operadores seguidos\n");
        exit(1);
    }
}

void verificacao_simbolo_sozinho(Pilha* pi){
    if(*pi != NULL && (*pi)->prox != NULL && (*pi)->prox->prox != NULL &&
     (*pi)->valor_simb == 3 && (*pi)->prox->valor_simb == 1 && (*pi)->prox->prox->valor_simb == 2){
        printf("EXPRESSAO INVALIDA! - Operador sozinho entre parenteses\n");
        exit(1);
    }
}

void verificacao_simbolo_no_final(Pilha* pi){
    if(*pi != NULL && (*pi)->valor_simb == 1){
        printf("EXPRESSAO INVALIDA! - Terminou com operador\n");
        exit(1);
    }
}

void verificacao_loop(Pilha* pi){
    if(pi == NULL || *pi == NULL) return;
    No* aux = *pi;
    while(aux->prox != NULL){
        if(aux->valor_simb == 0 && aux->prox->valor_simb == 0){
            printf("EXPRESSAO INVALIDA! - Falta operador entre numeros\n");
            exit(1);
        }
        aux = aux->prox;
    }
}

void liberar_pilha(Pilha* pi){
    if(pi == NULL) return;
    while(*pi != NULL){
        pop(pi);
    }
}

PilhaHistorico* criar_pilha_historico(){
    PilhaHistorico* pi_hist = (PilhaHistorico*) malloc(sizeof(PilhaHistorico));
    if(pi_hist == NULL) return NULL;
    *pi_hist = NULL;
    return pi_hist;
}

void push_historico(PilhaHistorico* pi_hist, char* input, float resultado){
    if(pi_hist == NULL) return;
    NoHistorico* novo = malloc(sizeof(NoHistorico));
    if(novo == NULL) return;

    novo->resultado = resultado;
    size_t len = strlen(input);
    if(len > 0 && input[len-1] == '\n') input[len-1] = '\0';
    
    strcpy(novo->input, input);
    novo->prox = *pi_hist;
    *pi_hist = novo;
}

void mostrar_historico(PilhaHistorico *pi_hist){
    system("cls");
    printf("=---= HISTORICO =---=\n");
    if(pi_hist == NULL || *pi_hist == NULL){
        printf("\nSem calculos ainda!\n");
    } else {
        NoHistorico* aux = *pi_hist;
        while(aux != NULL){
            printf(">>> %s = %.2f\n", aux->input, aux->resultado);
            aux = aux->prox;
        }
    }
    printf("\nAperte ENTER para voltar");
    getchar();
}

int get_prioridade(char op) {
    if (op == '^' || op == 'r') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void inverter_pilha_aux(Pilha* pi) {
    if (pi == NULL || *pi == NULL) return;
    No* atual = *pi;
    No* anterior = NULL;
    No* seguinte = NULL;
    while (atual != NULL) {
        seguinte = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = seguinte;
    }
    *pi = anterior;
}

void calcular_topo(Pilha* pi_num, Pilha* pi_simb) {
    if (*pi_simb == NULL || *pi_num == NULL) return;

    char op = (*pi_simb)->simb;
    pop(pi_simb);

    if (*pi_num == NULL) return; 
    float val2 = (*pi_num)->valor;
    pop(pi_num);

    if (*pi_num == NULL) {
        push(pi_num, val2); 
        return; 
    }
    float val1 = (*pi_num)->valor;
    pop(pi_num);

    float res = 0;

    if (op == '+') res = val1 + val2;
    else if (op == '-') res = val1 - val2;
    else if (op == '*') res = val1 * val2;
    else if (op == '/') {
        if (val2 == 0) { printf("\nERRO: Divisao por zero.\n"); exit(1); }
        res = val1 / val2;
    }
    else if (op == '^') res = pow(val1, val2);
    else if (op == 'r') res = pow(val1, 1.0/val2);

    push(pi_num, res);
}

void realizar_calculo(Pilha* pi_verificacao, Pilha* pi_num, Pilha* pi_simb) {
    liberar_pilha(pi_num);
    liberar_pilha(pi_simb);

    inverter_pilha_aux(pi_verificacao);

    No* aux = *pi_verificacao;

    while (aux != NULL) {
        if (aux->valor_simb == 0) {
            push(pi_num, aux->valor);
        }
        else if (aux->valor_simb == 2) {
            push_simb(pi_simb, aux->simb, 2);
        }
        else if (aux->valor_simb == 3) {
            while (*pi_simb != NULL && (*pi_simb)->simb != '(' && (*pi_simb)->simb != '[' && (*pi_simb)->simb != '{') {
                calcular_topo(pi_num, pi_simb);
            }
            pop(pi_simb); 
        }
        else if (aux->valor_simb == 1) {
            while (*pi_simb != NULL && (*pi_simb)->valor_simb == 1 && 
                   get_prioridade((*pi_simb)->simb) >= get_prioridade(aux->simb)) {
                calcular_topo(pi_num, pi_simb);
            }
            push_simb(pi_simb, aux->simb, 1);
        }
        aux = aux->prox;
    }

    while (*pi_simb != NULL) {
        calcular_topo(pi_num, pi_simb);
    }
}

void calcular(char* input){
    liberar_pilha(pi_num);
    liberar_pilha(pi_simb);
    liberar_pilha(pi_verificacao);

    int indice = 0;
    char caractere = input[indice];
    int existe_num = 0;

    while(caractere != '\n' && caractere != '\0'){
        if(ehAbrido(pi_verificacao, caractere)){     
        }else if(ehFechado(pi_verificacao, caractere)){
            pop_dos_2_primeiros(pi_verificacao);
        }else if(ehNum(caractere)){
            existe_num = 1;
        }
        Caractere_invalido(caractere);
        indice++;
        caractere = input[indice];
    }

    if(existe_num == 0){
        printf("EXPRESSAO INVALIDA - Nenhum numero existente\n");
        return; 
    }

    if(*pi_verificacao != NULL){
        printf("EXPRESSAO INVALIDA - Parenteses nao fecham\n");
        return;
    }

    liberar_pilha(pi_verificacao);

    indice = 0;
    caractere = input[indice];

    while(caractere != '\n' && caractere != '\0'){
        if(caractere == ' '){
        } else if(ehNum(caractere)){
            addnum(pi_verificacao, &indice, input);
            verificacao(pi_verificacao);
        } else if(ehSimbolo(pi_verificacao, caractere)){
            verificacao(pi_verificacao);
        } else if(ehAbrido(pi_verificacao, caractere)){
            verificacao(pi_verificacao);
        } else if(ehFechado(pi_verificacao, caractere)){ 
            verificacao_simbolo_sozinho(pi_verificacao);
            verificacao(pi_verificacao);
        }
        
        if (!ehNum(caractere)) {
             indice++;
        } else {
             indice++;
        }
        caractere = input[indice];
    }

    verificacao_loop(pi_verificacao);
    verificacao_simbolo_no_final(pi_verificacao);

    realizar_calculo(pi_verificacao, pi_num, pi_simb);
    
    printf("Calculo Realizado com Sucesso!\n");
    
    if (*pi_num != NULL) {
        imprimirPilhaResultado(pi_num);
        push_historico(historico, input, (*pi_num)->valor);
    }
}