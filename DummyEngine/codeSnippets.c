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

polygon* getLastPolygon(mesh* M) {
    
    // Hakee mallin M ensimmäiseksi lisätyn polygonin, eli linkitetyn listan
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

mesh* newUnitCubeOld() {
    
    // Luo yksikkökuution
    
    mesh* unitCube = newMesh();
    
    // Luodaan verteksit, NEU = NorthEastUpper, 
    // SWL = SouthWestLower jne...
    
    // TÄLLÄ HETKELLÄ VIELÄ MÄÄRITELTY KUVAKULMA-AVARUUDESSA!
    // VAIHDA MYÖHEMMIN!
    
    vertex* NEU = meshNewVertex(unitCube, -1, 1, 1);
    vertex* NWU = meshNewVertex(unitCube, 1, 1, 1);
    vertex* SEU = meshNewVertex(unitCube, -1, 1, -1);
    vertex* SWU = meshNewVertex(unitCube, 1, 1, -1);
    
    vertex* NEL = meshNewVertex(unitCube, -1, -1, 1);
    vertex* NWL = meshNewVertex(unitCube, 1, -1, 1);
    vertex* SEL = meshNewVertex(unitCube, -1, -1, -1);
    vertex* SWL = meshNewVertex(unitCube, 1, -1, -1);
    
    // Muodostetaan polygonit
    
    polygon* front1 = meshNewPolygon(unitCube, SEU, SWU, SWL);
    polygon* front2 = meshNewPolygon(unitCube, SWL, SEL, SEU);
    setPolygonColor(front1, 0xff000000);
    setPolygonColor(front2, 0xff000000);
    
    polygon* back1 = meshNewPolygon(unitCube, NEU, NWU, NWL);
    polygon* back2 = meshNewPolygon(unitCube, NWL, NEL, NEU);
    setPolygonColor(back1, 0x00ff0000);
    setPolygonColor(back2, 0x00ff0000);
    
    polygon* right1 = meshNewPolygon(unitCube, SEU, NEU, NEL);
    polygon* right2 = meshNewPolygon(unitCube, NEL, SEL, SEU);
    setPolygonColor(right1, 0x0000ff00);
    setPolygonColor(right2, 0x0000ff00);
    
    polygon* left1 = meshNewPolygon(unitCube, SWU, NWU, NWL);
    polygon* left2 = meshNewPolygon(unitCube, NWL, SWL, SWU);
    setPolygonColor(left1, 0xf0f0f000);
    setPolygonColor(left2, 0xf0f0f000);
    
    polygon* top1 = meshNewPolygon(unitCube, NEU, SEU, SWU);
    polygon* top2 = meshNewPolygon(unitCube, SWU, NWU, NEU);
    setPolygonColor(top1, 0x0f0f0f00);
    setPolygonColor(top2, 0x0f0f0f00);
    
    polygon* bottom1 = meshNewPolygon(unitCube, NEL, SEL, SWL);
    polygon* bottom2 = meshNewPolygon(unitCube, SWL, NWL, NEL);
    setPolygonColor(bottom1, 0xffffff00);
    setPolygonColor(bottom2, 0xffffff00);
    
    return unitCube;
}
