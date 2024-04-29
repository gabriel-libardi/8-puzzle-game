#include "header.h"

int hn(int **matrix){
    int value = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if((matrix[i][j] != goal_matrix[i][j]) && (matrix[i][j] != 0)){
                value++;
            }
        }
    }

    return value;
}

void alloc_matrix(int ***matrix){
    *matrix =  (int**)malloc(N * sizeof(int*));

    for(int i = 0; i < N; ++i){
        (*matrix)[i] = (int*)malloc(N * sizeof(int));
    }
}

int** swap_void_matrix(Node no, int posi_x, int posi_y, int sum_x, int sum_y){
    int** new_matrix;
    alloc_matrix(&(new_matrix));

    for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                new_matrix[i][j] = no.matrix[i][j];
            }
    }
    
    int aux;
    
    aux = (new_matrix[posi_x + sum_x][posi_y  + sum_y]);
    new_matrix[posi_x + sum_x][posi_y  + sum_y] = 0;
    new_matrix[posi_x][posi_y] = aux;

    return new_matrix;
}

void sons(List* li, Node no, int profundidade){
    int posi_void_x, posi_void_y, void_position;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if((no.matrix[i][j]) == 0){
                posi_void_x = i;
                posi_void_y = j;

                void_position = ((i * 3) + j);
            }
        }
    }

    //NodeWay* father = create_way_list();
    //copia_list_matrix(father, no->way);
    //way_matrix();
    Node teste, teste2, teste3, teste4;

    if (posi_void_x > 0) {  // Mover para cima
        teste.wa = clone_way_list_end(no.wa, 'w');
        teste.matrix = (swap_void_matrix(no,posi_void_x, posi_void_y, -1, 0));
        teste.hn = hn(teste.matrix);
        teste.ef = profundidade + teste.hn;
        insert_list_ordered(li,teste);
    }
    if (posi_void_y > 0) {  // Mover para a esquerda
        teste2.wa = clone_way_list_end(no.wa, 'a');
        teste2.matrix = (swap_void_matrix(no,posi_void_x, posi_void_y, 0, -1));
        teste2.hn = hn(teste2.matrix);
        teste2.ef = profundidade + teste2.hn;
        insert_list_ordered(li,teste2);
    }
    if (posi_void_x < N - 1) {  // Mover para baixo
        teste3.wa = clone_way_list_end(no.wa, 's');
        teste3.matrix = (swap_void_matrix(no,posi_void_x, posi_void_y, 1, 0));
        teste3.hn = hn(teste3.matrix);
        teste3.ef = profundidade + teste3.hn;
        insert_list_ordered(li,teste3);
    }
    if (posi_void_y < N - 1) {  // Mover para a direita
        teste4.wa = clone_way_list_end(no.wa, 'd');
        teste4.matrix = (swap_void_matrix(no,posi_void_x, posi_void_y, 0, 1));
        teste4.hn = hn(teste4.matrix);
        teste4.ef = profundidade + teste4.hn;
        insert_list_ordered(li,teste4);
    }
}

int ja_foi(Node atual, List* li2){
    Elem* no = *li2;

    int aux = 0;
    while (no != NULL){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if((atual.matrix[i][j]) == (no->node.matrix[i][j]) && (atual.matrix[i][j] != 0)){
                    aux++;
                }
            }
        }
        if(aux == 8){
            break;
        }
        else{
            aux = 0;
        }
        no = no->next;
    }

    if (aux){
        return 1;
    }

    return 0;
}

int solve(List* li, List* li2){
    if((li == NULL) || (*li == NULL)){
        return ERROR;
    }


    Elem* no = *li;
    if(no->node.hn == 0){
            return OK;
    }
    else{
        if(ja_foi(no->node,li2)){
            remove_list_ini(li);
            return (solve(li, li2));
        }
        else{
            insert_list_end(li2, no->node);
            Elem *no2 = *li;
            ///*
            for(int i = 0; i < N; i++){
                    for(int j = 0; j < N; j++){
                        printf("%d ",no2->node.matrix[i][j]);
                    }
                    printf("\n");
            }
            printf("\n");
            printf("h(n) = %d\n", no2->node.hn);
            printf("ef(n) = %d + %d\n", ((no2->node.ef) - (no2->node.hn)), no2->node.hn);
            printf("ef(n) = %d\n",no2->node.ef);
            printf("\n");
            //*/
            //char a;
            //scanf("%c", &a);
            remove_list_ini(li);
            sons(li, no->node, (((no2->node.ef) - (no2->node.hn)) + 1));
            return (solve(li, li2));
        }
    }
}

