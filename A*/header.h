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

int goal_matrix[N][N] =
{
    {1,2,3},
    {8,0,4},
    {7,6,5}
};

#endif