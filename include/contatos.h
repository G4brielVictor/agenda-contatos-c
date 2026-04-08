#ifndef CONTATOS_H
#define CONTATOS_H

#define MAX_CONTATOS 50
#define MAX_TELEFONE 20
#define MAX_EMAIL 50
#define MAX_NOME 50

typedef struct {
    int id;
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char email[MAX_EMAIL];
} Contato;

int adicionar_contatos(Contato *contato, int *contD, int *id);
int validar_nome(char *nome);
int validar_telefone(const char *tel, Contato *contato, int *id);
int validar_email(const char *email);

void listar_contatos(Contato *contatos, int *contID);
void mostrar_contatos(Contato *p);

int buscar_contato(Contato *contatos, int *contID);
int buscar_contato_por_nome(const char *buscaNome, Contato *contatos, int *contID);
int buscar_contato_por_numero(const char *buscaNum, Contato *contatos, int *contID);  

int editar_contatos(Contato *contatos, int *contID);
void editar_nome(Contato *p);
void editar_telefone(Contato *p,int *id);
void editar_email(Contato *p);

int remover_contatos(Contato *contatos, int *contID);

int verificar_contato_existente(Contato *contatos, int *id);
void limpar_linha(char *buffer);

#endif