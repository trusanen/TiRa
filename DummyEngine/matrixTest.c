#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define epsilon 0.01

float absoluteValue(float x) {
    if(x < 0) {
        return -x;
    }
    return x;
}

float matrixNorm(matrix* A, matrix* B) {
    
    // Palauttaa matriisinormin, jonka avulla voidaan tutkia kahdesta
    // samankokoisesta matriisista, ovatko ne samat.
    
    // Tarkistaa, että annetut matriisit eivät ole tyhjiä.
    
    assert(A != NULL && B != NULL);
    assert(A->rows == B->rows && A->columns == B->columns);
    
    float a;
    float b;
    float diff = 0;
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        for(j ; j < A->columns ; j++) {
            a = A->values[i][j];
            b = B->values[i][j];
            if(absoluteValue(a-b) > diff) {
                diff = absoluteValue(a-b);
            }
        }
        j = 0;
    }
    
    return diff;
}

void matrixTest() {
    
    // Määritellään vastausmatriisit
    
    matrix* sumResult = newMatrix(3, 3);
    sumResult->values[0][2] = 1.1;
    sumResult->values[2][0] = 1.1;
    
    matrix* mulResult = newMatrix(3,3);
    mulResult->values[0][0] = 1.1*1.1;
    
    matrix* fillResult = newMatrix(2,2);
    fillResult->values[0][0] = 5.0;
    fillResult->values[0][1] = 5.0;
    fillResult->values[1][0] = 5.0;
    fillResult->values[1][1] = 5.0;
    
    // Aloitetaan testit
    
    matrix* A = newMatrix(3,3);
    matrix* B = newMatrix(3,3);
    
    A->values[0][2] = 1.1;
    B->values[2][0] = 1.1;
    
    matrix* C = matrixSum(A,B);
    assert(matrixNorm(C, sumResult) == 0);
    
    matrix* D = matrixMultiply(A,B);
    assert(matrixNorm(D, mulResult) == 0);
    
    matrix* E = newMatrix(2, 2);
    matrixFill(E, 5.0);
    assert(matrixNorm(E, fillResult) == 0);
    
    matrix* vector = newMatrix(3, 1);
    
    matrixFill(vector, 1.9);
    
    printMatrix(vector);
    
    matrix* vectorTranspose = matrixTranspose(vector);
    
    printMatrix(vectorTranspose);
    
    matrix* F = newMatrix(7, 7);
    matrixFill(F, 7.0);
    
    matrixMultiplyScalar(F, 0.5);
    
    printMatrix(F);
    
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(D);
    deleteMatrix(E);
    deleteMatrix(vector);
    deleteMatrix(vectorTranspose);
    deleteMatrix(F);
    
    deleteMatrix(sumResult);
    deleteMatrix(mulResult);
}
