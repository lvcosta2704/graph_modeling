#include <stdio.h>
#include "graph.h"
#include <stdbool.h>


int main() {
    int opcao, N, x, y, w;
    int res;
    bool print_status = 1;
    Graph *g;
    g == NULL;

    scanf("%d", &opcao);
    

    while(opcao != -1) {
        switch (opcao)
        {
        case 0:
            scanf("%d", &N);
            g = create_graph(N);
            break;
        case 1:
            scanf("%d %d %d", &x,&y,&w);
            add_edge(g, x, y, w);
            break;

        case 2:
            scanf("%d %d", &x, &y);
            res = exist_edge(g, x, y);
            print_status = 0;
            break;
        default:
            printf("unrecognized option %d!\n", opcao);
            break;
        }
        scanf("%d", &opcao);
    }

    if(opcao == -1){
        if(print_status) {
            print_info(g);
        } else {
            printf("%d\n", res);
        }
    }
    delete_graph(g);
    return 0;
}