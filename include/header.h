#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3 // Tamanho da matriz "tamanho do Puzzle"
#define ERROR 0
#define OK 1

typedef int** Matrix;

struct WayStruct{
    int direction;
    struct WayStruct *next;
};

typedef struct WayStruct WaySt;
typedef struct WayStruct* Way;

struct NodeStruct{
    int hn;
    int ef;
    Way* wa;
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
int** swap_void_matrix(Node no, int posi_x, int posi_y, int sum_x, int sum_y);
void sons(List* li, Node no, int profundidade);
int ja_foi(Node atual, List* li2);
int solve(List* li, List* li2);
List* create_list();
int insert_list_ordered(List* li, Node data);
int remove_list_ini(List* li);
void release_list(List* li);
int insert_list_end(List* li, Node data);
Way* create_way_list();
int insert_way_list_end(Way* li, char direc);
void imprime_way_list(Way* li);
Way* clone_way_list_end(Way* li2, int new_direc);
void release_way_list(Way* li);

#endif