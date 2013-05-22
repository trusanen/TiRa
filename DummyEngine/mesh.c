#include "mesh.h"
#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static float transR1[] = {1, 0, 0, 0};
static float transR2[] = {0, 1, 0, 0};
static float transR3[] = {0, 0, 1, 0};
static float transR4[] = {0, 0, 0, 1};
static float* transMatrixRowPointerArray[] = {
    transR1,
    transR2,
    transR3,
    transR4
};
static matrix translationMatrixStruct = {
    4,
    4,
    transMatrixRowPointerArray
};
static matrix* translationMatrix = &translationMatrixStruct;

vertex* newVertex(float x, float y, float z) {
    
    // Luo uuden verteksin (pisteen avaruudessa).
    
    vertex* V = malloc(sizeof(vertex));
    
    V->coords = newMatrix(3, 1);
    
    V->coords->values[0][0] = x;
    V->coords->values[1][0] = y;
    V->coords->values[2][0] = z;
    
    return V;
}

void deleteVertex(vertex* V) {
    
    // Poistaa verteksin, tarkistaa, että annettu osoitin ei ole tyhjä.
    
    assert(V != NULL);
    
    deleteMatrix(V->coords);
    
    free(V);
}

polygon* newPolygon(vertex* A, vertex* B, vertex* C) {
    
    // Luo uuden polygonin (kolmio kolmiulotteisessa avaruudessa). Tarkistaa,
    // että annetut pisteet eivät ole tyhjiä.
    
    assert(A != NULL && B != NULL && C != NULL);
    
    polygon* P = malloc(sizeof(polygon));
    
    P->verts[0] = A;
    P->verts[1] = B;
    P->verts[2] = C;
    
    P->next = NULL;
    
    return P;
}

void deletePolygon(polygon* P) {
    
    // Poistaa polygonin, tarkistaa, että annettu osoitin ei ole tyhjä.
    
    assert(P != NULL);
    
    deleteVertex(P->verts[0]);
    deleteVertex(P->verts[1]);
    deleteVertex(P->verts[2]);
    
    free(P);
}

mesh* newMesh() {
    
    // Luo uuden 3D-mallin, joka on aluksi tyhjä. Malli koostuu polygoneista,
    // jotka tallennetaan yksisuuntaisena linkitettynä listana.
    
    mesh* M = malloc(sizeof(mesh));
    
    M->coords = newMatrix(4,1);
    matrixFill(M->coords, 0);
    M->coords->values[3][0] = 1.0;
    
    M->rotation = identityMatrix(4);
    
    M->polygons = NULL;
    
    return M;
}

void deleteMesh(mesh* M) {
    
    // Poistaa mallin poistamalla kaikki sen polygonit. Tarkistaa, että
    // malli ei ole tyhjä.
    
    assert(M != NULL);
    
    deleteMatrix(M->coords);
    deleteMatrix(M->rotation);
    
    polygon* P = M->polygons;
    
    while(P != NULL) {
        deletePolygon(P);
        P = P->next;
    }
    
    free(M);
}

polygon* getLastPolygon(mesh* M) {
    
    // Hakee mallin M viimeiseksi lisätyn polygonin, eli linkitetyn listan
    // viimeisen alkion. Tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    if(M->polygons != NULL) {
        polygon* P = M->polygons;
        while(P->next != NULL) {
            P = P->next;
        }
        return P;
    }
    return NULL;
}

void addPolygon(mesh* M, polygon* P) {
    
    // Lisää polygonin P malliin M lisäämällä sen linkitetyn listan viimeiseksi.
    // Tarkistaa, että malli ja polygoni eivät ole tyhjiä.
    
    assert(M != NULL && P != NULL);
    
    if(M->polygons == NULL) {
        M->polygons = P;
    }
    else {
        polygon* P0 = getLastPolygon(M);

        P0->next = P;
    }
}

void meshTranslate(mesh* M, float x, float y, float z) {
    
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
    
    // Asetetaan staattiseen siirtomatriisiin oikeat arvot
    
    translationMatrix->values[0][3] = x;
    translationMatrix->values[1][3] = y;
    translationMatrix->values[2][3] = z;
    
    // Suoritetaan matriisikertolasku
    
    matrix* result = matrixMultiply(translationMatrix, M->coords);
    
    // Poistetaan alkuperäinen koordinaattimatriisi ja asetetaan
    // uusi laskettu tilalle.
    
    deleteMatrix(M->coords);
    
    M->coords = result;
}

void meshRotate(mesh* M, float xRotation, float yRotation, float zRotation) {
    
    
    
}
