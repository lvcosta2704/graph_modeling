#include <stdio.h>
#include "graph.h"
#include <stdbool.h>


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
            res = max_neighbors(g);
            printf("max vertex: %d\n", res);
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
    }  else if (res_valido) {
        printf("%d\n", res);
    }
}
    delete_graph(g); // deleta o grafo quando o programa acaba
    return 0;
}
