#include "header.h"

int main(){

    int **matrix;
    alloc_matrix(&matrix);

   matrix[0][0] = 2;
   matrix[0][1] = 8;
   matrix[0][2] = 3;
   matrix[1][0] = 1;
   matrix[1][1] = 6;
   matrix[1][2] = 4;
   matrix[2][0] = 7;
   matrix[2][1] = 0;
   matrix[2][2] = 5;

    Node node1;
    node1.matrix = matrix;
    node1.hn = hn(node1.matrix);
    node1.ef = node1.hn;
    node1.wa = (char*)malloc(sizeof(char)*1); 
    //printf("\nh(n): %d\n\n",node1.hn);

    List* li = create_list();
    insert_list_ordered(li, node1);

    List* li2 = create_list();

    solve(li, li2);

    Elem *no = *li;
    for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                printf("%d ",no->node.matrix[i][j]);
            }
            printf("\n");
    }
    printf("\n");
    printf("h(n) = %d\n", no->node.hn);
    printf("ef(n) = %d + %d\n", ((no->node.ef) - (no->node.hn)), no->node.hn);
    printf("ef(n) = %d\n",no->node.ef);
    printf("\n");

    int tam_string = strlen(no->node.wa);

    printf("movimentos: ");
    for (int i = 0; i < tam_string; i++){
        printf("%c ", no->node.wa[i]);
    }
    printf("\n");
    //imprime_way_list(no->node.wa);


    free_matrix(&matrix);

    return 0;
}