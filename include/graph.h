#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0

typedef int Bool;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

#if MATRIZ_ADJ
    typedef struct _grafo {
        int vertices;
        int arestas;
        TIPOPESO **adj;
    }Grafo;

#else 
// Lista de Adjacências
    typedef struct _adjacencia {
        int vertice;
        TIPOPESO peso;
        struct _adjacencia *prox;
    }Adjacencia;

    typedef struct _vertice {
        // Dado armazenados
        Adjacencia *cab;
    }Vertice;

    typedef struct _grafo {
        int vertices;
        int arestas;
        Vertice *adj;
    }Grafo;

#endif

Grafo *criaGrafo(int v);
Bool criaAresta(Grafo *gr, int vi,int  vf, TIPOPESO p);
void imprime(Grafo *gr);
#endif