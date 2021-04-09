#include <stdlib.h>
#include <stdio.h>

void transpose(int **matrix, int **t_matrix, int rows, int cols);

int main()
{
    const int rows = 3, cols = 3;
    int **matrix;
    int **t_matrix;

    // mem allocation
    matrix = malloc(rows * sizeof *matrix);
    t_matrix = malloc(cols * sizeof *t_matrix);
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = malloc(cols * sizeof *matrix[i]);
    }
    for (int i = 0; i < cols; i++)
    {
        t_matrix[i] = malloc(rows * sizeof *t_matrix[i]);
    }
    
    // the matrix filling
    int num = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = num++;
        }
    }
    
    transpose(matrix, t_matrix, rows, cols);
    
    // output 
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", t_matrix[i][j]);
        }
        printf("\n");
    }
    
    // free mem
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    for (int i = 0; i < cols; i++)
    {
        free(t_matrix[i]);
    }
    free(matrix);
    free(t_matrix);
    return 0;
}

void transpose(int **matrix, int **t_matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            t_matrix[j][i] = matrix[i][j];
        }
    }
}
