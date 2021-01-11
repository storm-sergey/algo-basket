#include <stdlib.h>
#include <stdio.h>

void mtranspose(int **matrix, int **t_matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            t_matrix[j][i] = matrix[i][j];
        }
    }
}

// testing
int main()
{
    // initialisation
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
    
    // filling
    int num = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = num++;
        }
    }
    
    //
    mtranspose(matrix, t_matrix, rows, cols);
    
    // result printing
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
    
    // mem freeing
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    for (int i = 0; i < cols; i++)
    {
        free(t_matrix[i]);
    }
    free(t_matrix);
    return 0;
}
