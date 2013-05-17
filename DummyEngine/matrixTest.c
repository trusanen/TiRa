#include "matrix.h"

void matrixTest() {
    
    matrix* A = newMatrix(3,3);
    matrix* B = newMatrix(3,3);
    
    A->values[0][2] = 1.1;
    B->values[2][0] = 1.1;
    
    printMatrix(A);
    printMatrix(B);
    
    matrix* C = matrixSum(A,B);
    
    printMatrix(C);
    
    matrix* D = matrixMultiply(A,B);
    
    printMatrix(D);
    
    matrix* E = newMatrix(5, 5);
    
    matrixFill(E, 5.0);
    
    printMatrix(E);
    
    matrix* vector = newMatrix(3, 1);
    
    matrixFill(vector, 1.9);
    
    printMatrix(vector);
    
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(D);
    deleteMatrix(E);
    deleteMatrix(vector);
}
