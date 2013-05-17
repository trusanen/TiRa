/* 
 * File:   main.c
 * Author: topias
 *
 * Created on May 17, 2013, 11:57 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
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
    
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(D);
    
    return (EXIT_SUCCESS);
}

