#include <assert.h>
#include "mesh.h"
#include <stdlib.h>
#include <stdio.h>

// Tästä tiedostosta löytyy koodinpätkiä, joita saatan tarvita ehkä vielä joskus.

void meshTranslateOld(mesh* M, float x, float y, float z) {
    
    // Siirtää mallia M x-, y- ja z-akselien suuntaisesti. Tarkistaa, että
    // malli ei ole tyhjä.
    
    assert(M != NULL);
    
    // Siirtomatriisi on seuraavanlainen:
    //
    // [ 1 0 0 x ]
    // [ 0 1 0 y ]
    // [ 0 0 1 z ]
    // [ 0 0 0 1 ]
    //
    // Kun tällä kerrotaan koordinaattimatriisia, saadaan
    //
    // [ x0 + x ]
    // [ y0 + y ]
    // [ z0 + z ]
    // [   1    ]
    //
    // eli mallia on siirretty x:n, y:n ja z:n verran akseleita pitkin.
    
    // Luodaan siirtomatriisi
    
    matrix* translationMatrix = newMatrix(4, 4);
    matrixFill(translationMatrix, 0);
    
    translationMatrix->values[0][0] = 1;
    translationMatrix->values[1][1] = 1;
    translationMatrix->values[2][2] = 1;
    translationMatrix->values[3][3] = 1;
    
    translationMatrix->values[0][3] = x;
    translationMatrix->values[1][3] = y;
    translationMatrix->values[2][3] = z;
    
    // Suoritetaan matriisikertolasku
    
    matrix* result = matrixMultiply(translationMatrix, M->coords);
    
    // Poistetaan alkuperäinen koordinaattimatriisi ja asetetaan
    // uusi laskettu tilalle. Vapautetaan myös siirtomatriisin käyttämä
    // tila.
    
    free(M->coords);
    
    M->coords = result;
    
    free(translationMatrix);
}
