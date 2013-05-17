#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"

matrix* newMatrix(int rows, int columns) {
    
    assert(rows > 0 && columns > 0);
    
    matrix* A = malloc(sizeof(matrix));
    
    A->rows = rows;
    A->columns = columns;
    
    A->values = malloc(sizeof(float*) * rows);
    
    int j = 0;
    
    for(j ; j < columns ; j++) {
        A->values[j] = malloc(sizeof(float) * columns);
    }
    
    return A;
}

void deleteMatrix(matrix* A) {
    
    int j = 0;
    
    for(j ; j < A->columns ; j++) {
        free(A->values[j]);
    }
    free(A->values);
    free(A);
}

void printMatrix(matrix* A) {
    
    assert(A != NULL);
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        printf("[ ");
        for(j ; j < A->columns ; j++) {
            printf("%.2f ", A->values[i][j]);
        }
        j = 0;
        printf("]\n");
    }
    
    printf("\n");
}

matrix* matrixSum(matrix* A, matrix* B) {
    
    assert(A->rows == B->rows && A->columns == B->columns);
    
    matrix* C = newMatrix(A->rows, A->columns);
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        for(j ; j < A->columns ; j++) {
            C->values[i][j] = A->values[i][j] + B->values[i][j];
        }
        j = 0;
    }
    
    return C;
}

matrix* matrixMultiply(matrix* A, matrix* B) {
    
    assert(A->rows == B->columns);
    
    matrix* C = newMatrix(A->columns, B->rows);
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    float value;
    
    for(i ; i < C->rows ; i++) {
        for(j ; j < C->columns ; j++) {
            value = 0;
            for(k ; k < A->rows ; k++) {
                value += A->values[i][k] * B->values[k][j];
            }
            k = 0;
            C->values[i][j] = value;
        }
        j = 0;
    }
    
    return C;
}