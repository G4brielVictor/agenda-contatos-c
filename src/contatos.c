#include "contatos.h"
#include "arquivo.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>

int adicionar_contatos(Contato *contato, int *contID, int *id){
    Contato *p = &contato[*contID];
    
    if(*contID >= MAX_CONTATOS){
        printf("Erro, maximo de contatos adicionados\n");
        return 0;
    }


    int nome_valido;
    do {
        printf("Nome: ");
        fgets(p->nome, MAX_NOME, stdin);
        p->nome[strcspn(p->nome, "\n")] = '\0';

        nome_valido = validar_nome(p->nome);

        if(!nome_valido){
            printf("Nome inválido, tente novamente\n");
        }
    }while(!nome_valido);


    int telefone_valido;
    do{
        printf("Telefone: ");
        fgets(p->telefone, MAX_TELEFONE, stdin);
        p->telefone[strcspn(p->telefone, "\n")] = '\0';

        telefone_valido = validar_telefone(p->telefone, contato, contID);

        if(!telefone_valido){
            printf("Numero invalido, tente novamente\n");
        }
    }while(!telefone_valido);


    int email_valido;
    do{
        printf("Email: ");
        fgets(p->email, MAX_EMAIL, stdin);
        p->email[strcspn(p->email, "\n")] = '\0';

        email_valido = validar_email(p->email);

        if(!email_valido){
            printf("Email invalido, tente novamente\n");
        }
    }while(!email_valido);

    p->id = *id;

    (*contID)++;
    (*id)++;
    
    int salvo = salvar_arquivo(contato, contID, id);
    if(salvo == 0){
        return 0;
    }

    return 1;    
}


int validar_nome(char *nome){
 //Aqui fiz um if para verificar se o ponteiro está null/vazio.
 //strlen mede o tamanho da string, se é 0 é vazio, invalido 
    if(nome == NULL || strlen(nome) == 0){
        return 0;
    } 
    
    nome[0] = toupper(nome[0]);
    //for percorrendo a string. O isalpha retorna verdadeiro se letra esta entre A-Z, a-z.
    //o isspace retornaa verdadeiro se é espaço.
    for(int i = 0; nome[i] != '\0'; i++){
        if(!isalpha(nome[i]) && !isspace(nome[i])){
            return 0;
        }
    }
    return 1;
}

int validar_telefone(const char *tel, Contato *contatos, int *contID){
    int tam;

    if(tel == NULL || strlen(tel) == 0){
        return 0;
    }

    tam = strlen(tel);
    if(tam < 12 || tam > 14){
        printf("teste\n");
        return 0;
    }

    if(tel[2] != ' ' || tel[8] != '-') {
        printf("Formato invalido. EX: XX 99999-9999\n");
        return 0;
    }

    for(int i = 0; tel[i] != '\0'; i++){
        if(i == 2 || i == 8) continue;

        if(!isdigit(tel[i])){
            return 0;
        }
    }

    for(int i = 0; i < *contID; i++){
        if(strcmp(tel, contatos[i].telefone ) == 0){
            printf("Telefone já cadastrado\n");
            return 0;
        }
    }   
    
    return 1;
}

int validar_email(const char *email){
    
    if(email == NULL || strlen(email) == 0){
        return 0;
    }

    
    if(!strchr(email, '@') || !strchr(email, '.')){
        return 0;
    }
    
    int tam = strlen(email);
    if('@' == email[0] || '@' == email[tam - 1]){
        return 0;
    }

    if('.' == email[0] || '.' == email[tam - 1]){
        return 0;
    }
    
    int arroba = 0, pos_ponto = -1, pos_arroba = -1;
    for(int i = 0; email[i] != '\0'; i++){
        

        if(email[i] == ' '){
            return 0;
        }

        if(email[i] == '@'){
            arroba++;
            pos_arroba = i;
            if(arroba != 1){
                return 0;
            }
        }

        if(email[i] == '.'){
            pos_ponto = i;
        }
    }

    if(pos_ponto < pos_arroba){
        return 0;
    }

    return 1;
}

void listar_contatos(Contato *contatos, int *contID){
    if(verificar_contato_existente(contatos, contID) == 0){
        printf("Sem contatos para listar.\n\n");
        return;
    }

    //Ordenação em ordem alfábetica A-Z
    Contato temp;
    for(int i = 0; i < *contID - 1; i++){
        for(int j = 0; j < *contID - i - 1; j++){
            if(strcmp(contatos[j].nome, contatos[j+1].nome) > 0){
                temp = contatos[j];
                contatos[j] = contatos[j+1];
                contatos[j+1] = temp;
            }
        }
    }

    printf("====================================================================\n");
    printf("|                LISTA DE CONTATOS                                 |\n");
    printf("====================================================================\n");
    printf("| %-2s | %-20s | %-13s | %-20s |\n", "ID", "NOME", "TELEFONE", "EMAIL");
    printf("---------------------------------------------------------------------\n");


    for(int i = 0; i < *contID; i++){    
        printf("| %-2d | %-20s | %-13s | %-20s |\n", 
        contatos[i].id, contatos[i].nome, contatos[i].telefone, contatos[i].email);
    }
    printf("====================================================================\n\n");

    char op;
    printf("Digite enter para retornar: ");
    scanf(" %c", &op);
    getchar();

    printf("Retornando...");

    printf("\n\n");
}

int buscar_contato(Contato *contatos, int *contID){   
    if(verificar_contato_existente(contatos, contID) == 0){
        printf("Sem contatos para buscar\n\n");
        return 0;
    }

    int pos, opcao;

    do {
        printf("\n| 1 - Buscar numero | 2 - Buscar nome | 3 - Buscar ID | 0 - Sair  |\nDigite: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        if(opcao == 1){
            char buscaTelefone[MAX_TELEFONE];
            do {
                printf("\nDigite um numero(Enter para cancelar): ");
                fgets(buscaTelefone, MAX_TELEFONE, stdin);
                buscaTelefone[strcspn(buscaTelefone, "\n")] = '\0';


                pos = buscar_contato_por_numero(buscaTelefone, contatos, contID);

                if(pos != -1){
                    printf("\n\t  CONTATO ENCONTRADO!\n");
                    printf("| %-15s | %-10s | %-18s |\n", "NOME", "TELEFONE", "EMAIL");
                    printf("----------------------------------------------------------------\n");
                    printf("| %-15s | %-10s | %-18s |\n\n", 
                    contatos[pos].nome, contatos[pos].telefone, contatos[pos].email);
                    printf("\n");
                    return pos;            
                }
                else {
                    printf("\tContato nao encontrado, digite novamente.\n\n");
                }
            } while(pos == -1);
        }

        else if(opcao == 2){
            char buscaNome[MAX_NOME];
            do {
                printf("\nDigite o nome do contato: ");
                fgets(buscaNome, MAX_NOME, stdin);
                buscaNome[strcspn(buscaNome, "\n")] = '\0';

                pos = buscar_contato_por_nome(buscaNome, contatos, contID);

                if(pos != -1){
                    printf("\nCONTATO ENCONTRADO!\n");
                    printf("| %-20s | %-13s | %-20s |\n", "NOME", "TELEFONE", "EMAIL");
                    printf("---------------------------------------------------------------\n");
                    printf("| %-20s | %-13s | %-20s |\n", 
                    contatos[pos].nome, contatos[pos].telefone, contatos[pos].email);
                    printf("\n");
                    return pos;
                }
                else {
                    printf("\tContato nao encontrado, digite novamente\n\n");
                }
            } while(pos == -1);
        }

        else if(opcao == 3){
            int buscaID;    
            do {
                printf("\nDigite o ID do contato: ");
                scanf("%d", &buscaID);
                while(getchar() != '\n');

                pos = buscar_contato_por_id(&buscaID, contatos, contID);
                if(pos != -1){
                    printf("\nCONTATO ENCONTRADO!\n");
                    printf("| %-20s | %-13s | %-20s |\n", "NOME", "TELEFONE", "EMAIL");
                    printf("---------------------------------------------------------------\n");
                    printf("| %-20s | %-13s | %-20s |\n", 
                    contatos[pos].nome, contatos[pos].telefone, contatos[pos].email);
                    printf("\n");
                    return pos;
                }
                else {
                    printf("\tContato nao encontrado, digite novamente\n\n");
                }
            } while(pos == -1);
        }

        else if(opcao == 0){
            printf("\n\n");
            return -1;
        }

        else {
            printf("Opcao invalida, tente novamente\n\n");
        }
    }while(opcao != 0);

    printf("\n");
    return -1;
}

int buscar_contato_por_nome(const char *buscaNome, Contato *contatos, int *contID){
    if(buscaNome[0] == '\0'){
        printf("\nEntrada vazia, tente novamente. \n");
        return -1;
    }

    for(int i = 0; i < *contID; i++){
        if(strstr(contatos[i].nome, buscaNome) != NULL){
            return i;
        }
    }
    return -1;
}

int buscar_contato_por_numero(const char *buscaNum, Contato *contatos, int *contID){
    if(buscaNum[0] == '\0'){
        printf("\nEntrada vazia, tente novamente. \n");
        return -1;
    }

    for(int i = 0; i < *contID; i++){
        if(strcmp(buscaNum, contatos[i].telefone) == 0){
            return i;
        }
    }
    return -1;
}

int buscar_contato_por_id(const int *buscaID, Contato *contatos, int *contID){
    if(buscaID == NULL){
        printf("\nEntrada vazia, tente novamente. \n");
        return -1;
    }

    for(int i = 0; i < *contID; i++){
        if(*buscaID == contatos[i].id){
            return i;
        }
    }
    return -1;
}

int editar_contatos(Contato *contatos, int *contID){
    if(verificar_contato_existente(contatos, contID) < 1){
        printf("Sem contatos para editar.\n\n");
        return 0;
    }

    printf("===================================================\n");
    printf("|                 EDITAR CONTATOS                  |\n");
    printf("===================================================\n");

    int opcao, pos;
    char escolha = 'N';
    do {
        printf("1 - Editar telefone\n");
        printf("2 - Editar nome\n");
        printf("3 - Editar Email\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        while(getchar() != '\n');

        if(opcao == 0) break;
        
        if(escolha == 'N') pos = buscar_contato(contatos, contID);

        if(pos == -1) continue;

        switch(opcao){
            case 1:
                printf("==== Editar Telefone ====\n");
                editar_telefone(&contatos[pos], contID);
                mostrar_contatos(&contatos[pos]);
                printf("\n");
                break;
            case 2:
                printf("==== Editar Nome ====\n");
                editar_nome(&contatos[pos]);
                mostrar_contatos(&contatos[pos]);
                printf("\n");
                break;
            case 3:
                printf("==== Editar Email ====\n");
                editar_email(&contatos[pos]);
                mostrar_contatos(&contatos[pos]);
                printf("\n");
                break;
            default: 
                printf("Opcao incorreta, tente novamente\n");
        }

        printf("Deseja editar o mesmo contato? S - sim | N - Nao\nEscolha: ");
        do {
            scanf(" %c", &escolha);
            escolha = toupper(escolha);
        }while(escolha != 'S' && escolha != 'N');
        
    }while(opcao != 0); 
    return 0;
}

void editar_nome(Contato *p){
    char novoNome[MAX_NOME];
    int valido;

    do {
        printf("Nome atual: %s\n", p->nome);
        printf("Digite o novo nome: ");
        
        fgets(novoNome, MAX_NOME, stdin);
        limpar_linha(novoNome);

        valido = validar_nome(novoNome);
        if(!valido){
            printf("Nome invalido, tente novamente.\n");
        }
    }while(!valido);

    printf("\n\nNOME EDITADO!\n");
    strcpy(p->nome, novoNome);
}

void editar_telefone(Contato *p, int *id){
    char novoTel[MAX_TELEFONE];
    int valido;
    do {
        printf("Telefone atual: %s\n", p->telefone);
        printf("Digite o novo telefone: ");

        fgets(novoTel, MAX_TELEFONE, stdin);
        limpar_linha(novoTel);

        valido = validar_telefone(novoTel, p, id);
        if(!valido){
            printf("Telefone invalido, tente novamente.\n");
        }
    }while(!valido);

    printf("\n\nCONTATO EDITADO!\n");
    strcpy(p->telefone, novoTel);
}

void editar_email(Contato *p){
    char novoEmail[MAX_EMAIL];
    int valido;

    do{
        printf("Email atual: %s\n", p->email);
        printf("Digite o novo email: ");

        fgets(novoEmail, MAX_EMAIL, stdin);
        limpar_linha(novoEmail);

        valido = validar_email(novoEmail);
        if(!valido){
            printf("Email invalido, tente novamente.\n");
        }
    }while(!valido);

    printf("\n\nEMAIL EDITADO!\n");
    strcpy(p->email, novoEmail);
}

int remover_contatos(Contato *contatos, int *contID){
    if(verificar_contato_existente(contatos, contID) == 0){
        printf("Sem contatos para remover\n");
        return 0;
    }

    printf("===================================================\n");
    printf("|                REMOVER CONTATOS                  |\n");
    printf("===================================================\n");

    int pos = buscar_contato(contatos, contID);
    
    if(pos == -1) return 0;

    int op;
    printf("Deseja remover o contato? S - Sim | N - Nao\nEscolha: ");
    scanf(" %c", &op);
    getchar();

    if(toupper(op) == 'N'){
        return 0;
    }

    for(int i = pos; i < *contID - 1; i++){
        contatos[i] = contatos[i + 1];
    }

    (*contID)--;
    printf("Contato removido com sucesso!\n");

    return 1;
}

int verificar_contato_existente(Contato *contatos, int *id){
    if(*id == 0){
        return 0;
    }
    return 1;
}

void mostrar_contatos(Contato *p){
    printf("| %-20s | %-13s | %-20s |\n", "NOME", "TELEFONE", "EMAIL");
    printf("---------------------------------------------------------------\n");
    printf("| %-20s | %-13s | %-20s |\n", p->nome, p->telefone, p->email);
}

void limpar_linha(char *buffer){
    buffer[strcspn(buffer, "\n")] = '\0';
}
