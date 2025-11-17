#include "calc.c"

char op[2];

int main(){
    int opMenu = 0;
    char input[50];
    Pilha *pi = criarPilha();
    Pilha *pi_calc = criarPilha();
    Pilha *pi_verificacao = criarPilha();
    PilhaHistorico *historico = criar_pilha_historico();
    

    while(1){
        system("cls");

        printf("=---= Calculadora com Pilha =---=\n");
        printf("\n1- Fazer um calculo\n");
        printf("2- Historico\n");
        printf("3- Fazer calculo mostrando detalhes com PILHA\n\n");
        printf("0- Sair\n");

        scanf("%d",&opMenu);
        limpar_buffer();

        switch (opMenu){
            case 0:
                return 0;
            case 1:
                exec(input,sizeof(input),pi,pi_calc,pi_verificacao,historico);
                break;
            case 2:
                mostrar_historico(historico);
                break;
            
            default:
                system("cls");
                printf("Digite um caractere valido!\n");
                printf("\nAperte ENTER para voltar");
                getchar();
                break;
            }
    }

    free(pi);
    free(pi_calc);
    free(pi_verificacao);
    free(historico);

    return 0;
    
}