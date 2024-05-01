#include "header.h"

int main(void){

    int** matrix;
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

    char *solution = solve_A_star(matrix);
    printf("The solution is: %s\n", solution);

    free_matrix(&matrix);
    free(solution);

    return 0;
}