#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* create_graph(int N) {
    Graph* g = malloc(sizeof(Graph));
    g->n_vertices = N;

    // alocacao da matriz
    g->matriz = malloc((N+1) * sizeof(int*));

    for(int i = 1; i <= N; i++) {
        g->matriz[i] = malloc((N+1)*sizeof(int));
    }
    // poe -1 em tudo
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
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
    if (v1 < 1 || v1 > g->n_vertices ||
        v2 < 1 || v2 > g->n_vertices
    ) return 0;
    if (g->matriz[v1][v2] != -1) return 1;
    return 0; // caso onde a celula é -1
}

int* neighbors(Graph* g, int v1, int *tam) {
    // testar na matriz se ha celulas que nao sao -1 na linha ou coluna do v1
    int* vetor = malloc((g->n_vertices)*sizeof(int));
    int contador = 0;
    for (int i = 1; i <= g->n_vertices; i++)
    {
        if (g->matriz[v1][i] != -1) {
            vetor[contador] = i;
            contador++;
        }
    }
    *tam = contador;
    return vetor;
}

int remove_edge(Graph* g, int v1, int v2){
    if (g == NULL) return -1;


    if (v1 < 1 || v1 > g->n_vertices || v2 < 1 || v2 > g->n_vertices) 
        return -1;

    if (g->matriz[v1][v2] == -1) return -1;

    g->matriz[v1][v2] = -1;
    g->matriz[v2][v1] = -1;

    return 1;
}

void print_info(Graph* g, int* vetor, int tam) {
    if (g == NULL && vetor == NULL) return;

    if (vetor != NULL) {
        for (int i = 0; i < tam; i++) {
            printf("%d", vetor[i]);
            if (i < tam - 1) printf(" ");
        }
        printf("\n");
        return;
    }
    
    printf("V = [");
    for (int i = 1; i <= g->n_vertices; i++)
    {
        printf("%d", i);
        if (i < g->n_vertices) {
            printf(", ");
        }
    }
    printf("]\n");

    // parte da impressao das arestas
    printf("E = [");
    int first = 1;
    // pelos casos de teste é visivel que quem esta no loop externo é o j
    // por isso esse for loop esta invertido
    for (int j = 1; j <= g->n_vertices; j++) {
        for (int i = 1; i < j; i++) {
            if (g->matriz[i][j] != -1) {
            
                if (!first) {
                    printf(", ");
                }
                printf("(%d, %d)", i, j);
                first = 0;
            }
        }
    }
    printf("]\n");
}


int max_neighbors(Graph* g) {
    int maior = -1;
    int vertice_maior;

    for (int i = 1; i <= g->n_vertices; i++)
    {
        int count = 0;

        for (int j = 1; j <= g->n_vertices; j++)
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

    for (int i = 1; i <= g->n_vertices; i++)
    {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}