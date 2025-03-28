#include "dictionary.h"

int main(int argc, char **argv) {
    
    Dict *luis = initDict(1);
    insertDict(luis, "idade", (void*) 19);
    insertDict(luis, "sexo", (void*) "masculino");
    insertDict(luis, "cursa", (void*) "Engenharia de computacao");
    insertDict(luis, "nascimento", (void*) 2005);
    insertDict(luis, "fav", (void*) "Kiriko");
    insertDict(luis, "gostade", (void*) "animacao");
    insertDict(luis, "dinheiro", (void*) 50);
    printf("teste");

    insertDict(luis, "gostade", (void*) "Lobo");
    printf("Dicionario Luis:\n");
    printf("Idade: %d\n", (int) search(luis, "idade"));
    printf("Sexo: %s\n", (char*) search(luis, "sexo"));
    printf("Cursa: %s\n", (char*) search(luis, "cursa"));
    printf("Nascimento: %d\n", (int) search(luis, "nascimento"));
    printf("Personagem favorito de overwatch: %s\n", (char*)search(luis, "fav"));
    printf("Gosta de %s\n", (char*) search(luis, "gostade"));
    printf("Dinheiro que tem nesse momento: %d\n", (int) search(luis, "dinheiro"));

    printfDict(luis);

    char **allkeys = getAllKeys(luis);
   
    if (allkeys) {
        for (int i = 0; i < sizeof(allkeys)/sizeof(allkeys[0]); i++) {
            printf("Chave %d: %s\n", i, allkeys[i]);
        }
    }
    
    if (contains(luis, "lobo"))
        printf("O dicionario possui a chave lobo\n");
    else
        printf("O dicionario não possui essa chave\n");


    clear(luis);
    printfDict(luis);



    printf("Executado com sucesso!\n");
    return 0;
}