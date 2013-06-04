#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"

matrix* newMatrix(int rows, int columns) {
    
    // Luo uuden matriisin, jonka alkiot alustetaan nollaksi.
    // Tarkistaa, että rivejä ja sarakkeita on enemmän kuin 0.
    
    assert(rows > 0 && columns > 0);
    
    matrix* A = malloc(sizeof(matrix));
    
    A->rows = rows;
    A->columns = columns;
    
    // Varaa muistin oikealle määrälle floateja. Values-attribuutti on määritelty
    // kaksoisosoittimeksi, sillä matriisin kokoa ei ole ennalta määrätty. 
    // Käytännössä ne tulevat olemaan 3x1, 3x3, 4x1, 4x4. Matriisin alkioita
    // voidaan myöhemmin kutsua A->values[rivi][sarake].
    
    // Varataan ensin riviosoittimille tila
    A->values = malloc(sizeof(float*) * rows);
    
    
    // Tämän jälkeen varataan tila oikealle määrälle floateja.
    int j = 0;
    
    for(j ; j < rows ; j++) {
        A->values[j] = malloc(sizeof(float) * columns);
    }
    
    // Alustetaan matriisin alkiot vielä nollaksi
    matrixFill(A, 0);
    
    return A;
}

void deleteMatrix(matrix* A) {
    
    // Poistaa matriisin vapauttamalla varatun muistin. Tarkistaa, että
    // matriisi ei ole tyhjä
    
    assert(A != NULL);
    
    int j = 0;
    
    for(j ; j < A->rows ; j++) {
        free(A->values[j]);
    }
    free(A->values);
    free(A);
}

void printMatrix(matrix* A) {
    
    // Tulostaa matriisin muodossa
    //
    // [ a11, a12, a13 ]
    // [ a21, a22, a23 ]
    // [ a31, a32, a33 ]
    //
    // Tarkistaa, että matriisi ei ole tyhjä.
    
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

matrix* identityMatrix(int dim) {
    
    // Luo dim x dim -kokoisen identiteettimatriisin, eli matriisin, jonka
    // diagonaalialkiot ovat ykkösiä ja muut nollia. Tarkistaa, että
    // dimensio on suurempaa kuin nolla.
    
    assert(dim > 0);
    
    matrix* I = newMatrix(dim, dim);
    matrixFill(I, 0);
    
    int i = 0;
    
    for(i ; i < dim ; i++) {
        I->values[i][i] = 1;
    }
    
    return I;    
}

void matrixFill(matrix* A, float value) {
    
    // Asettaa matriisin kaikki alkiot annetuksi arvoksi. Tarkistaa, että
    // matriisi ei ole tyhjä.
    
    assert(A != NULL);
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        for(j ; j < A->columns; j++) {
            A->values[i][j] = value;
        }
        j = 0;
    }
}

void matrixMultiplyScalar(matrix* A, float scalar) {
    
    // Kertoo kaikkia matriisin alkioita jollain skalaarilla, tarkistaa, että
    // matriisi ei ole tyhjä.
    
    assert(A != NULL);
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        for(j ; j < A->columns ; j++) {
            A->values[i][j] = A->values[i][j] * scalar;
        }
        j = 0;
    }
}

matrix* matrixSum(matrix* A, matrix* B) {
    
    // Laskee kahden matriisin summan. Tarkistaa, että molemmat matriisit
    // eivät ole tyhjiä ja että ne ovat samankokoisia.
    
    assert(A != NULL && B != NULL);
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
    
    // Laskee kahden matriisin tulon (järjestyksessä A*B). Tarkistaa,
    // että matriisit eivät ole tyhjiä ja että matriisissa A on
    // yhtä paljon rivejä kuin matriisissa B sarakkeita.
    
    assert(A != NULL && B != NULL);
    assert(A->columns == B->rows);
    
    matrix* C = newMatrix(A->rows, B->columns);
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    float value;
    
    for(i ; i < C->rows ; i++) {
        for(j ; j < C->columns ; j++) {
            value = 0;
            for(k ; k < A->columns ; k++) {
                value += A->values[i][k] * B->values[k][j];
            }
            k = 0;
            C->values[i][j] = value;
        }
        j = 0;
    }
    
    return C;
}

matrix* matrixTranspose(matrix* A) {
    
    // Palauttaa matriisin transpoosin eli rivit ja sarakkeet vaihdettuina
    // keskenään. Tarkistaa, että matriisi ei ole tyhjä.
    
    assert(A != NULL);
    
    matrix* AT = newMatrix(A->columns, A->rows);
    
    int i = 0;
    int j = 0;
    
    for(i ; i < A->rows ; i++) {
        for(j ; j < A->columns ; j++) {
            AT->values[j][i] = A->values[i][j];
        }
        j = 0;
    }
    
    return AT;
}

float matrixDotProd(matrix* u, matrix* v) {
    
    // Laskee vektorien u ja v pistetulon, tarkistaa, että 
    // molemmat ovat 4x1 -matriiseja eli neliulotteisia vektoreita.
    
    assert(u->rows == 4 && u->columns == 1);
    assert(v->rows == 4 && v->columns == 1);
    
    float dotProduct = u->values[0][0]*v->values[0][0]
        + u->values[1][0]*v->values[1][0]
        + u->values[2][0]*v->values[2][0]
        + u->values[3][0]*v->values[3][0];
    
    return dotProduct;
}