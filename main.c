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

        printf("=---= Calculadora com Pilha e Grafo =---=\n");
        printf("\n1- Fazer um calculo (Pilha)\n");
        printf("2- Calcular com Grafo (BFS/DFS)\n");
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

                printf("Escolha a forma de calcular com Grafo: \n\n");
                printf("1- BFS (Breadth-First Search - Visualizar Niveis)\n");
                printf("2- DFS (Depth-First Search - Calcular)\n\n");

                fgets(op,sizeof(op),stdin);

                switch (atoi(op)){
                    case 1:
                        system("cls");
                        printf("\nDigite a expressao: \n");
                        printf(">>> ");
                        fgets(input,sizeof(input),stdin);
                        input[strcspn(input, "\n")] = 0;

                        GrafoNo* grafoBFS = construir_grafo_expressao(input, 0, strlen(input)-1);
                        if(grafoBFS) {
                            mostrar_grafo_bfs(grafoBFS);
                            float res = calcular_grafo_dfs(grafoBFS); 
                            printf("\n>>> Resultado Final: %.2f\n", res);
                            push_historico(historico, input, res, "BFS");
                            liberar_grafo(grafoBFS);
                        } else {
                            printf("Erro ao construir grafo.\n");
                        }

                        printf("\nPressione ENTER para voltar ao menu\n");
                        getchar();
                        break;

                    case 2:
                        system("cls");
                        printf("\nDigite a expressao: \n");
                        printf(">>> ");
                        fgets(input,sizeof(input),stdin);
                        input[strcspn(input, "\n")] = 0;

                        GrafoNo* grafoDFS = construir_grafo_expressao(input, 0, strlen(input)-1);
                        if(grafoDFS) {
                            printf("\n--- Passo a Passo DFS ---\n");
                            float res = calcular_grafo_dfs(grafoDFS);
                            printf("-------------------------\n");
                            printf("\n>>> Resultado Final: %.2f\n", res);
                            push_historico(historico, input, res, "DFS");
                            liberar_grafo(grafoDFS);
                        } else {
                            printf("Erro ao construir grafo.\n");
                        }

                        printf("\nPressione ENTER para voltar ao menu\n");
                        getchar();
                        break;
                    
                    default:
                        system("cls");
                        printf("Digite um opção válida\n");
                        printf("\nPressione ENTER para voltar ao menu...");
                        getchar(); 
                        break;
                }
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