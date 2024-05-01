#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 3 // Tamanho da matriz "tamanho do Puzzle"
#define ERROR 0
#define OK 1

typedef int** Matrix;

struct NodeStruct{
    int hn;
    int ef;
    char* wa;
    Matrix matrix;
};

typedef struct NodeStruct Node;
//typedef struct NodeStruct* NodeWay;

struct element{
    Node node;
    struct element *next;
};

typedef struct element Elem;
typedef struct element* List;

extern int goal_matrix[N][N];

int hn(int **matrix);
void alloc_matrix(int ***matrix);
void free_matrix(int ***matrix);

int** swap_void_matrix(Node no, int posi_x, int posi_y, int sum_x, int sum_y);
void sons(List* li, Node no, int profundidade);
int ja_foi(Node atual, List* li2);
int solve(List* li, List* li2);
List* create_list();
int insert_list_ordered(List* li, Node data);
int remove_list_ini(List* li);
void release_list(List* li);
int insert_list_end(List* li, Node data);


char* solve_A_star(int** initial_position);

#endif