#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* create_graph(int N) {
    Graph* g = malloc(sizeof(Graph));
    g->n_vertices = N;

    // alocacao da matriz
    g->matriz = malloc(N * sizeof(int*));

    for(int i = 0; i < N; i++) {
        g->matriz[i] = malloc(N*sizeof(int));
    }
    // poe -1 em tudo
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            g->matriz[i][j] = -1;
        }   
    }
    return g;
}

void add_edge(Graph* g, int v1, int v2, int peso) {
    g->matriz[v1][v2] = peso;
    g->matriz[v2][v1] = peso;
}

int exist_edge(Graph* g, int v1, int v2) {
    if (g == NULL) return -1;
    if (v1 < 0 || v1 >= g->n_vertices ||
        v2 < 0 || v2 >= g->n_vertices
    ) return 0;
    if (g->matriz[v1][v2] != -1) return 1;
    return 0; // caso onde a celula é -1
}

int* neighbors(Graph* g, int v1, int *tam) {
    // testar na matriz se ha celulas que nao sao -1 na linha ou coluna do v1
    int* vetor = malloc((g->n_vertices)*sizeof(int));
    int contador = 0;
    for (int i = 0; i < g->n_vertices; i++)
    {
        if (g->matriz[v1][i] != -1) {
            vetor[contador] = i;
            contador++;
        }
    }
    *tam = contador;
    return vetor;
}

void remove_edge(Graph* g, int v1, int v2){
    if (g == NULL) return;
    g->matriz[v1][v2] = -1;
    g->matriz[v2][v1] = -1;
}

void print_info(Graph* g) {
    printf("V = [");
    for (int i = 0; i < g->n_vertices; i++)
    {
        printf("%d", i+1);
        if (i < g->n_vertices -1) {
            printf(", ");
        }
    }
    printf("]\n");

    // parte da impressao das arestas
    printf("E = [");
    int first = 1;

    for (int i = 0; i < g->n_vertices; i++) {
        for (int j = i + 1; j < g->n_vertices; j++) {
            if (g->matriz[i][j] != -1) {
            
                if (!first) {
                    printf(", ");
                }
                printf("(%d,%d)", i, j);
                first = 0;
            }
        }
    }
    printf("]\n");
}


int max_neighbors(Graph* g) {
    int maior = -1;
    int vertice_maior;

    for (int i = 0; i < g->n_vertices; i++)
    {
        int count = 0;

        for (int j = 0; j < g->n_vertices; j++)
        {
            if(g->matriz[i][j] != -1) {
                count++;
            }
        }
        if (count > maior) {
            maior = count;
            vertice_maior = i;
        }
    }
    return vertice_maior;
}

int** retorna_matriz(Graph* g) {
    return g->matriz;
}

void delete_graph(Graph* g) {
    if (g == NULL) return;

    for (int i = 0; i < g->n_vertices; i++)
    {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}