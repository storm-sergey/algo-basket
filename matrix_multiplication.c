#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define A_ROWS 2
#define A_COLS 4
#define B_ROWS 4
#define B_COLS 2

typedef struct Matrix_size {
    int rows;
    int cols;
} msize;

void mmultiply(msize a, msize b, int **A, int **B, int **AB)
{
    if (a.rows != b.cols) {
        printf("These matrices cannot be multiplied");
        return;
    }
    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            AB[row][col] = 0;
            for (int k = 0; k < a.cols; k++) {
                AB[row][col] += A[row][k] * B[k][col];
            }
        }
    }
}

// testing
int main()
{
    // initialisation
    int **A, **B, **AB;
    msize a, b;
    a.rows = A_ROWS;
    a.cols = A_COLS;
    b.rows = B_ROWS;
    b.cols = B_COLS;
    
    // mem allocation
    A = malloc(a.rows * sizeof *A);
    for (int row = 0; row < a.rows; row++) {
        A[row] = malloc(a.cols * sizeof *A[row]);
    }
    B = malloc(b.rows * sizeof *B);
    for (int row = 0; row < b.rows; row++) {
        B[row] = malloc(b.cols * sizeof *B[row]);
    }
    AB = malloc(a.rows * sizeof *AB);
    for (int row = 0; row < a.rows; row++) {
        AB[row] = malloc(b.cols * sizeof *AB[row]);
    }

    // rand filling and printing
    srand(time(0));
    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < a.cols; col++) {
            A[row][col] = rand() % 10;
            printf("%d ", A[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    for (int row = 0; row < b.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            B[row][col] = rand() % 10;
            printf("%d ", B[row][col]);
        }
        printf("\n");
    }
    printf("\n");

    // multiplication and result printing
    mmultiply(a, b, A, B, AB);
    for (int row = 0; row < a.rows; row++) {
        for (int col = 0; col < b.cols; col++) {
            printf("%d ", AB[row][col]);
        }
        printf("\n");
    }

    // mem freeing
    for (int row = 0; row < a.rows; row++) {
        free(AB[row]);
    }
    free(AB);
    for (int row = 0; row < b.rows; row++) {
        free(B[row]);
    }
    free(B);
    for (int row = 0; row < a.rows; row++) {
        free(A[row]);
    }
    free(A);
    return 0;
}

