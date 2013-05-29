#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define epsilon 0.01

float absoluteValue(float x) {
    
    // Palauttaa float-tyyppisen muuttujan itseisarvon, fabs() ei
    // jostain syystä toiminut, vaan palautti integerin.
    
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
    
    // Tämä testi testaa matriisiluokan toimivuutta.
    
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
    
    matrix* transposeResult = newMatrix(1, 3);
    transposeResult->values[0][0] = 1.9;
    transposeResult->values[0][1] = 1.9;
    transposeResult->values[0][2] = 1.9;
    
    matrix* scalarMulResult = newMatrix(7,7);
    matrixFill(scalarMulResult, 3.5);
    
    matrix* identity = newMatrix(4, 4);
    identity->values[0][0] = 1;
    identity->values[1][1] = 1;
    identity->values[2][2] = 1;
    identity->values[3][3] = 1;
    
    // Aloitetaan testit
    
    // Matriisien summan testaus
    
    matrix* A = newMatrix(3,3);
    matrix* B = newMatrix(3,3);
    
    A->values[0][2] = 1.1;
    B->values[2][0] = 1.1;
    
    matrix* C = matrixSum(A,B);
    assert(matrixNorm(C, sumResult) == 0);
    
    // Matriisien tulon testaus
    
    matrix* D = matrixMultiply(A,B);
    assert(matrixNorm(D, mulResult) == 0);
    
    // Matriisin täyttöalgoritmin testaus
    
    matrix* E = newMatrix(2, 2);
    matrixFill(E, 5.0);
    assert(matrixNorm(E, fillResult) == 0);
    
    // Matriisin transpoosin testaus
    
    matrix* vector = newMatrix(3, 1);
    matrixFill(vector, 1.9);
    matrix* vectorTranspose = matrixTranspose(vector);
    
    assert(matrixNorm(vectorTranspose, transposeResult) == 0);
    
    // Matriisin skalaarilla kertomisen testaus
    
    matrix* F = newMatrix(7, 7);
    matrixFill(F, 7.0);
    matrixMultiplyScalar(F, 0.5);
    
    assert(matrixNorm(F, scalarMulResult) == 0);
    
    // Identiteettimatriisialgoritmin testaus
    
    matrix* G = identityMatrix(4);
    
    assert(matrixNorm(G, identity) == 0);
    
    // Poistetaan matriisit
    
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(D);
    deleteMatrix(E);
    deleteMatrix(vector);
    deleteMatrix(vectorTranspose);
    deleteMatrix(F);
    deleteMatrix(G);
    
    deleteMatrix(sumResult);
    deleteMatrix(mulResult);
    deleteMatrix(fillResult);
    deleteMatrix(transposeResult);
    deleteMatrix(scalarMulResult);
    deleteMatrix(identity);
}
