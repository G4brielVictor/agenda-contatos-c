#include "contatos.h"
#include "arquivo.h"
#include <stdio.h>


int salvar_arquivo(Contato *contatos, int *contID, int *id){
    FILE *file;
    file = fopen("contatos.dat", "wb");

    if(file == NULL){
        printf("Error no codigo!\n");
        return 0;
    }

    fwrite(contID, sizeof(int), 1, file);

    fwrite(id, sizeof(int), 1, file);

    fwrite(contatos, sizeof(Contato), *contID, file);

    fclose(file);
    return 1;
}

int carregar_arquivo(Contato *contatos, int *contID, int *id){
    FILE *file;
    file = fopen("contatos.dat", "rb");

    if(file == NULL){
        *contID = 0;
        *id = 1;
        return 0;
    }

    fread(contID, sizeof(int), 1, file);

    fread(id, sizeof(int), 1, file);

    fread(contatos, sizeof(Contato), *contID, file);

    return 1;
}