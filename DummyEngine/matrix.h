/* 
 * File:   matrix.h
 * Author: topias
 *
 * Created on May 17, 2013, 12:23 PM
 */

#ifndef MATRIX_H
#define	MATRIX_H

typedef struct {
    int rows;
    int columns;
    float** values;
} matrix;

matrix* newMatrix(int rows, int columns);
void deleteMatrix(matrix* A);
void printMatrix(matrix* A);
matrix* matrixMultiply(matrix* A, matrix* B);

#ifdef	__cplusplus
extern "C" {
#endif
    


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

