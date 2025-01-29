#include "graph.h"

typedef struct {
    int chave;
}Registro;

typedef struct aux {
    Registro reg;
    struct aux *prox;
}Elemento, *PONT;


typedef struct _fila {
    Elemento *head;
    Elemento *tail;
    unsigned int size;
}Fila;

int inserirNaFila(Fila *f, Registro reg) {
    PONT novo = (PONT) malloc(sizeof(Elemento));
    novo->reg = reg;
    novo->prox = NULL;
    if (f->head == NULL) f->head = novo;
    else f->tail->prox = novo;
    f->tail = novo;
    f->size++;
    return true;
}

void excluirDaFila(Fila *f, Registro *reg) {
    if (!f->head) return false;
    *reg = f->head->reg;
    PONT apaga = f->head;
    f->head = f->head->prox;
    free(apaga);
    if (!f->head) f->tail = NULL;
    return true;
}

void inicializarFila(Fila *f) {
    f->head = NULL;
    f->size = 0;
    f->tail = NULL;
}

Grafo *criaGrafo(int v) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    
    g->vertices = v;
    g->arestas = 0;
    g->adj = (Vertice*) malloc(v * sizeof(Vertice));
    int i;
    for (i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    return g;
}

Adjacencia *criaAdj(int v, int peso) {
    Adjacencia *temp = (Adjacencia*) malloc(sizeof(Adjacencia));
    
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

// Cria arestas dirigidas
Bool criaAresta(Grafo *gr, int vi,int  vf, TIPOPESO p) {
    if (!gr) return false;
    if (vf < 0 || vf >= gr->vertices) return false;
    if (vi < 0 || vi >= gr->vertices) return false;

    Adjacencia *novo =criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

void imprime(Grafo *gr) {
    if (!gr) return;
    
    printf("Vértices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
    int i;
    for (i = 0; i < gr->vertices; i++) {
        printf("V%d: ", i);
        Adjacencia *ad = gr->adj[i].cab;
        while (ad) {
            printf("V%d(%d)\n", ad->vertice, ad->peso);
            ad = ad->prox;
        }
    }
    printf("\n");
}

void profundidade(Grafo *g) {
    int cor[g->vertices];
    int u;
    for (u = 0; u < g->vertices; u++) {
        cor[u] = BRANCO;
    }
    for (u = 0; u < g->vertices; u++) {
        if (cor[u] == BRANCO)
            visitaP(g, u, cor);
    }
}

void visitaP(Grafo *g, int u, int *cor) {
    cor[u] = AMARELO;
    Adjacencia *v = g->adj[u].cab;
    while (v) {
        if (cor[v->vertice] == BRANCO) {
            visitaP(g, v, cor);
        }
        v = v->prox;
    }
    cor[u] = VERMELHO;
}

void largura(Grafo *g) {
    int expl[g->vertices];
    int u;
    for (u = 0; u < g->vertices; u++)
        expl[u] = false;
    
    for (u = 0; u < g->vertices; u++) {
        if (!expl[u]) {
            visitaL(g, u, expl);
        }
    }
}

void visitaL(Grafo *g, int s, int *expl) {
    Fila f;
    inicializarFila(&f);
    expl[s] = true;
    Registro *u = (Registro*) malloc(sizeof(Registro));
    u->chave = s;
    inserirNaFila(&f, *u);
    while (f.head) {
        excluirDaFila(&f, u);
        Adjacencia *v = g->adj[u->chave].cab;
        
        while (v) {
            if (!expl[v->vertice]) {
                expl[v->vertice] = true;
                u->chave = v->vertice;
                inserirNaFila(&f, *u);
            }
            v = v->prox;
        }
    }
    free(u);
}

void inicializaD(Grafo *g, int *d, int *p, int s) {
    int v;
    for (v = 0; v < g->vertices; v++) {
        d[v] = INT_MAX/2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxa(Grafo *g, int *d, int *p, int u, int v) {
    Adjacencia *ad = g->adj[u].cab;
    while (ad && ad->vertice != v) 
        ad = ad->prox;
    if (ad) {
        if (d[v] > d[u] + ad->peso) {
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }
}

int existeAberto(Grafo *g,int *aberto) {
    int i = 0;
    for (; i < g->vertices; i++) {
        if (aberto[i] == true)
            return 1;
    }
    return 0;
}

int menorDist(Grafo *g, int *aberto, int *d) {
    int i;
    for (i = 0; i < g->vertices; i++)
        if (aberto[i] == true) break;
    if (i == g->vertices) return -1;
    int menor = i;
    for (i = menor+1; i < g->vertices; i++) {
        if (aberto[i] && (d[menor] > d[i]))
            menor = i;
    }
    return menor;
}

int *dijkstra(Grafo *g, int a) {
    int *d = (int *) malloc(g->vertices * sizeof(int));
    int p[g->vertices];
    int aberto[g->vertices];
    inicializaD(g, d, p, a);

    int i;
    for (i = 0; i < g->vertices; i++)
        aberto[i] = true;

    while (existeAberto(g, aberto)) {
        int u = menorDist(g, aberto, d);
        aberto[u] = false;
        Adjacencia *ad = g->adj[u].cab;
        while (ad) {
            relaxa(g, d, p, u, ad->vertice);
            ad = ad->prox;
        }
    }
    return d;
}