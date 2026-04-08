#include <stdio.h>
#include "contatos.h"
#include "arquivo.h"
#include <windows.h>

int main(){
    Contato contatos[MAX_CONTATOS];

    int n_contatos = 0, contatoID = 1, op;
    
    carregar_arquivo(contatos, &n_contatos, &contatoID);
    do {
        
        printf("===================================================\n");
        printf("|                AGENDA DE CONTATOS               |\n");
        printf("===================================================\n");
        printf("\n| 1 - Adicionar contatos.\n| 2 - Listar contatos.\n| 3 - Buscar contato.\n| 4 - Editar contato.\n| 5 - Remover contato da lista.\n| 0 - Sair da agenda.\n");
        
        
        printf("\nEscolha: ");
        while (scanf("%d", &op) != 1) {
            printf("Opcao invalida. Digite novamente: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');
        system("cls");

        switch(op) {
            case 1: {
                printf("\n=============== CADASTRO DE NOVO CONTATO ===============\n");
                int validar;
                validar = adicionar_contatos(contatos, &n_contatos, &contatoID);
                system("cls");
                if(!validar){
                    printf("\n\t\tCADASTRO CANCELADO\n\n");
                }
                else {
                    printf("\n\t\tCADASTRO REALIZADO\n\n");
                }
                break;
            }
            case 2:
                listar_contatos(contatos, &n_contatos);
                break;
            case 3:
                printf("===================================================\n");
                printf("|                 BUSCAR CONTATO                  |\n");
                printf("===================================================\n");
                buscar_contato(contatos, &n_contatos);
                break;
            case 4: 
                editar_contatos(contatos, &n_contatos);
                salvar_arquivo(contatos, &n_contatos, &contatoID);
                system("cls");
                break;
            case 5:
                remover_contatos(contatos, &n_contatos);
                salvar_arquivo(contatos, &n_contatos, &contatoID);
                system("cls");
                break;
        }

    } while(op != 0);
    

    return 0;
}
