/* ------ TRABALHO 1 GRAFOS -------
   ALUNOS: 
   LUCAS VINICIUS DA COSTA (16885265)
   RYAN SULINO ARRUA (16900070)
   JOAO VITOR VALERIO SIMPLICIO (15744492)

*/ 
//

// bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// estrutura do grafo
typedef struct Graph {
    int n_vertices;
    int **matriz; // matriz 2x2 que representa a matriz de adjacencia   
} Graph;

// DECLARACAO DAS FUNCOES
Graph* create_graph(int N);

void add_edge(Graph* g, int v1, int v2, int peso);

int exist_edge(Graph* g, int v1, int v2);

int* neighbors(Graph* g, int v1, int *tam);

int remove_edge(Graph* g, int v1, int v2);

void print_info(Graph* g, int* vetor, int tam);

int max_neighbors(Graph* g);

void retorna_matriz(Graph* g);

void delete_graph(Graph* g);

// PONTO DE ENTRADA
int main() {
    int opcao, N, x, y, w;
    int res; // variavel que ira guardar possiveis respostas das funcoes
    bool print_status = 1; // controla a impressao da info do grafo
    Graph *g;
    g = NULL; // declara como NULL para evitar problemas de lixo
    bool res_valido = 0; // controla a impressao da var res

    scanf("%d", &opcao);
    

    while(opcao != -1) {
        switch (opcao)
        {
        case 0: // case 0 vai funcionar como o iniciador do grafo
            scanf("%d", &N);
            g = create_graph(N); // retorna um grafo com N nós
            break;

        case 1: // case 1 responsavel por adicionar arestas entre nós 
            scanf("%d %d %d", &x,&y,&w);
            add_edge(g, x, y, w);
            break;

        case 2: // case 2 é responsavel por imprimir se existe ou nao uma
                // aresta
            scanf("%d %d", &x, &y);
            res = exist_edge(g, x, y);
            res_valido = 1;
            print_status = 0;
            break;

        case 3: // case 3 chama a funcao que mostra quais vizinhos um certo 
                // nó tem
            scanf("%d", &x);

            int tam;
            int* viz = neighbors(g, x, &tam);

            print_info(g, viz, tam); // funcao print_info a qual pode 
            // imprimir os vertices e arestas e tambem os vizinhos do nó

            free(viz); // libera para garantir segurança
            res_valido = 0; // nao imprime o res
            print_status = 0; // nao imprime a info
            break;

        case 4: // case 4 é responsavel por remover uma aresta entre dois nós
            scanf("%d %d", &x, &y);
            // checagem da entrada, se nao estiver no range certo, retorna -1
            if (x < 1 || x > g->n_vertices || y < 1 || y > g->n_vertices) {
                res = -1;
                res_valido = 1;
                print_status = 0;
                break;
            }
            // se o x e y sao validos entao chama remove_edge e devolve a resposta em res
            res = remove_edge(g, x, y);
            // se o nó for removido com sucesso entao printa a info
            // senao printa -1
            // seta flags de impressao
            if (res == -1) {
                res_valido = 1;
                print_status = 0;
            } else {
                print_status = 1;
                res_valido = 0;
            }
            break;

        case 5: // case 5 responsavel por imprimir a matriz de adjacencia
            retorna_matriz(g);
            // seta as flags para nao impressao de infos do grafo
            print_status = 0;
            res_valido = 0;
            break;
        
        case 6: // case 6 responsavel por imprimir o vertice com maior numero de vizinhos
            res = max_neighbors(g); // chama a funcao com o retorno em res
            printf("max vertex: %d\n", res);
            // seta as flags para nao impressao de infos do grafo
            res_valido = 0;
            print_status = 0;
            break;
            
        default:
            printf("unrecognized option %d!\n", opcao);
            break;
        }

        scanf("%d", &opcao);
    }

    // quando o usuario quiser sair do programa com -1 serao checadas as variaveis que comandam a impressao, e sera impresso corretamente as informações
    if(opcao == -1) {
        if(print_status) {
            print_info(g, NULL, 0);
    }else if (res_valido) {
        printf("%d\n", res);
    }
}
    delete_graph(g); // deleta o grafo quando o programa acaba
    return 0;
}


// ==== FUNCOES ====
Graph* create_graph(int N) {
    Graph* g = malloc(sizeof(Graph));
    g->n_vertices = N;

    // alocacao da matriz
    g->matriz = malloc((N+1) * sizeof(int*));
    // aloca de 1 ate N pois é 1-based
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
    if (g == NULL) return;
    // poe nas celulas correspondentes da matriz o peso que foi informado
    g->matriz[v1][v2] = peso;
    g->matriz[v2][v1] = peso;
}

int exist_edge(Graph* g, int v1, int v2) {
    // grafo é NULL
    if (g == NULL) return -1;
    // vertice fora do limite 
    if (v1 < 1 || v1 > g->n_vertices ||
        v2 < 1 || v2 > g->n_vertices
    ) return 0;
    // caso de sucesso, checa se o valor na matriz é diferente de -1
    if (g->matriz[v1][v2] != -1) return 1;
    return 0; // caso onde a celula é -1
}

int* neighbors(Graph* g, int v1, int *tam) {
    // testar na matriz se ha celulas que nao sao -1 na linha ou coluna do v1
    int* vetor = malloc((g->n_vertices)*sizeof(int));
    int contador = 0;
    for (int i = 1; i <= g->n_vertices; i++)
    {
        // preenche o vetor com o valor que na matriz é diferente de -1
        if (g->matriz[v1][i] != -1) {
            vetor[contador] = i;
            contador++;
        }
    }
    // coloca o valor que o contador acumulou no tam 
    *tam = contador;
    return vetor;
}

int remove_edge(Graph* g, int v1, int v2){
    // checa se g é null para poder remover
    if (g == NULL) return -1;
    // checa os vertices para ver se estao nos limites
    if (v1 < 1 || v1 > g->n_vertices || v2 < 1 || v2 > g->n_vertices) 
        return -1;
    // se o peso foi nulo ainda (-1) entao nao existe a aresta
    if (g->matriz[v1][v2] == -1) return -1;
    
    // caso de sucesso, preenche novamente com -1 e retorna 1 
    g->matriz[v1][v2] = -1;
    g->matriz[v2][v1] = -1;

    return 1;
}

void print_info(Graph* g, int* vetor, int tam) {
    // garante que o grafo e o array nao seja NULL
    if (g == NULL && vetor == NULL) return;
    // caso de o vetor existir, ele imprime o vetor
    if (vetor != NULL) {
        for (int i = 0; i < tam; i++) {
            printf("%d", vetor[i]);
            if (i < tam - 1) printf(" ");
        }
        printf("\n");
        return; // retorna da funcao e nao imprime os V e A
    }
    // imprime os vertices da forma desejada
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
    if (g == NULL) return -1;

    int maior = -1;
    int vertice_maior;
    // vai checando em cada vertices os seus vizinhos e assinalando o maior numero a cada loop
    // retorna o vertice que tem mais vizinhos
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

void retorna_matriz(Graph* g) {
    if (g == NULL) return;

    printf("Adjacency Matrix:\n");

    // cria dois laços para mostrar cada item da matriz de adjacencia
    for (int i = 1; i <= g->n_vertices; i++)
    {
        for (int j = 1; j <= g->n_vertices; j++)
        {
            if (g->matriz[i][j] == -1) { // se for -1 imprime zero, como o caso do run codes quer
                printf("%3d ", 0);
            } else printf("%3d ", g->matriz[i][j]);
        }
        printf("\n");
    } 
}

void delete_graph(Graph* g) {
    if (g == NULL) return;
    // da free nas colunas da matriz
    for (int i = 1; i <= g->n_vertices; i++)
    {
        free(g->matriz[i]);
    }
    // free na linha 
    free(g->matriz);
    free(g);
}
