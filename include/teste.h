#ifndef TESTE_H
#define TESTE_H

typedef struct _pessoa P;

P* add(int idade, const char *nome);
void print(const P *pessoa);
int destroy(P **pessoa);
P** create_data(int size);

#endif