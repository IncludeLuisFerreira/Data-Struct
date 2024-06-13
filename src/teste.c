#include "../include/teste.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********Código privado*******/

struct _pessoa {
    char nome[100];
    int idade;
};

/******************************/


/// @brief Cria uma nova memória que salva o tipo pessoa
/// @param idade idade da pessoa
/// @param nome  nome da pessoa
/// @return retorna o ponteiro para essa memória
P* add(int idade, const char *nome) {
    P *nova_pessoa = (P*)calloc(1, sizeof(P));
    if (nova_pessoa == NULL) {
        printf("Erro: faild to alocate memory!\n");
        exit(EXIT_FAILURE);
    }

    nova_pessoa->idade = idade;
    strcpy(nova_pessoa->nome, nome);

    return nova_pessoa;
}

void print(const P *pessoa) {
    printf("Nome: %s\n", pessoa->nome);
    printf("Idade: %d\n", pessoa->idade);
}

int destroy(P **pessoa) {
    P *aux = *pessoa;
    free(aux);
    *pessoa = NULL;
    return 1;
}

P** create_data(int size) {
    P **vec = (P**)calloc(size, sizeof(P*));
    
    for (int i = 0; i < size; i++)
       vec[i] = add(0, "None"); 

    return vec;
}

