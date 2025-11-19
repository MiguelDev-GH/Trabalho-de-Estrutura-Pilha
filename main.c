#include "calc.c"

char op[2];



int main(){

    pi_num = criarPilha();
    pi_simb = criarPilha();
    pi_verificacao = criarPilha();
    historico = criar_pilha_historico();

    int opMenu = 0;
    char input[50];

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
                system("cls");
                printf("\nDigite a expressao: \n");
                printf(">>> ");
                fgets(input,sizeof(input),stdin);
                calcular(input,sizeof(input));
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

    free(pi_num);
    free(pi_simb);
    free(pi_verificacao);
    free(historico);

    return 0;
    
}