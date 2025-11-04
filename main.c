#include "pilha.c"

int main(){

    Pilha* minhaPi = criarPilha();

    for(int i = 0; i < 5; i++){
        push(minhaPi,i);
    }

    pop(minhaPi);

    imprimirPilha(minhaPi);

    return 0;
}