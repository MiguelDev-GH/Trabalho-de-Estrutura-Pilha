#include "calc.c"

char op[3];

int main(){

    pi_num = criarPilha();
    pi_simb = criarPilha();
    pi_verificacao = criarPilha();
    historico = criar_pilha_historico();

    int opMenu = 0;
    char input[50];

    int mainLoop = true;

    while(mainLoop){
        system("cls");

        printf("=---= Calculadora com Pilha =---=\n");
        printf("\n1- Fazer um calculo\n");
        printf("2- Calcular com BFS ou DFS\n");
        printf("3- Historico\n");
        printf("0- Sair\n");
        printf(">>> ");

        scanf("%d",&opMenu);
        limpar_buffer();

        switch (opMenu){
            case 0:
                mainLoop = false;
                break;
            
            case 1:
                while(true){
                    system("cls");
                    printf("\nDigite a expressao: \n");
                    printf(">>> ");
                    fgets(input,sizeof(input),stdin);
                    
                    calcular(input);

                    printf("\nDeseja fazer outro calculo? (S/N): ");
                    fgets(op,sizeof(op),stdin);

                    if(op[1] != '\n'){
                        printf("OPÇÃO INVALIDA!");
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar(); 
                        break;
                    }else if(op[0] == 'S' || op[0] == 's'){
                        continue;
                    } else if(op[0] == 'N' || op[0] == 'n'){
                        break; 
                    }else{
                        printf("OPÇÃO INVALIDA!");
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar(); 
                        break;
                    }

                }
                break;

            case 2:
                system("cls");

                printf("Escolha a forma de calcular: \n\n");
                printf("1- BFS (Breadth-First Search)\n");
                printf("2- DFS (Depth-First Search)\n\n");

                fgets(op,sizeof(op),stdin);

                // Aqui tem que adicionar as coisa


                break;

            case 3:
                mostrar_historico(historico);
                break;

            default:
                printf("Opcao invalida.\n");
                getchar();
                break;

            }
    }

    liberar_pilha(pi_num);
    liberar_pilha(pi_simb);
    liberar_pilha(pi_verificacao);
    free(pi_num);
    free(pi_simb);
    free(pi_verificacao);
    free(historico);

    system("cls");
    printf("\nPrograma finalizado\n\n");
    return 0;
}