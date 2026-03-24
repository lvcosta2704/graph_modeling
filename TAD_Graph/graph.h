#ifndef GRAFO_H
#define GRAFO_H


// Estrutura do Grafo
typedef struct Graph {
    int n_vertices;
    int **matriz;
} Graph;

Graph* create_graph(int N);

void add_edge(Graph* g, int v1, int v2, int peso);

int exist_edge(Graph* g, int v1, int v2);

int* neighbors(Graph* g, int v1, int *tam);

void remove_edge(Graph* g, int v1, int v2);

void print_info(Graph* g);

int max_neighbors(Graph* g);

int** retorna_matriz(Graph* g);

void delete_graph(Graph* g);


#endif