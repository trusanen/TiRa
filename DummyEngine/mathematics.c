#include "mathematics.h"
#include <assert.h>
#include <stdlib.h>
#include "matrix.h"

int pointInFrontOfPolygon(polygon* P, matrix* coords) {
    
    // Funktio tarkistaa, onko 4x1-matriisilla määritelty
    // homogeenisen koordinaatiston piste polygonin P
    // etupuolella. Tämä tapahtuu laskemalla pisteen koordinaatit
    // polygonin tasovektoreiden ja normaalin muodostamassa kannassa
    // ja tutkimalla, onko z-koordinaatti positiivinen.
    
    // Funktio tarkistaa, että osoittimet eivät ole tyhjiä.
    
    assert(P != NULL && coords != NULL);
    
    vertex* V0 = P->verts[0];
    vertex* V1 = P->verts[1];
    vertex* V2 = P->verts[2];
    
    matrix* normal = calculatePolygonWorldNormal(P);
    
    matrix* basisInv = newMatrix(4, 4);
    
    float a = V1->world->values[0][0] - V0->world->values[0][0];
    float b = V2->world->values[0][0] - V0->world->values[0][0];
    float c = normal->values[0][0];
    
    float d = V1->world->values[1][0] - V0->world->values[1][0];
    float e = V2->world->values[1][0] - V0->world->values[1][0];
    float f = normal->values[1][0];
    
    float g = V1->world->values[2][0] - V0->world->values[2][0];
    float h = V2->world->values[2][0] - V0->world->values[2][0];
    float k = normal->values[2][0];
    
    
    basisInv->values[0][0] = e*k - f*h;
    basisInv->values[1][0] = -(d*k - f*g);
    basisInv->values[2][0] = d*h - e*g;
    
    basisInv->values[0][1] = -(b*k - c*h);
    basisInv->values[1][1] = a*k - c*g;
    basisInv->values[2][1] = -(a*h - b*g);
    
    basisInv->values[0][2] = b*f - c*e;
    basisInv->values[1][2] = -(a*f - c*d);
    basisInv->values[2][2] = a*e - b*d;
    
    // Lasketaan determinantti ja kerrotaan sillä kannanvaihtomatriisia
    
    float det = a*(e*k - f*h) - b*(k*d - f*g) + c*(d*h - e*g);
    
    matrixMultiplyScalar(basisInv, 1/det);
    
    // Siirretään koordinaatteja siten, että origoksi tulee polygonin
    // ensimmäinen verteksi
    
    matrix* translatedCoords = newMatrix(4, 1);
    translatedCoords->values[0][0] = coords->values[0][0]
            - V0->world->values[0][0];
    translatedCoords->values[1][0] = coords->values[1][0]
            - V0->world->values[1][0];
    translatedCoords->values[2][0] = coords->values[2][0]
            - V0->world->values[2][0];
    translatedCoords->values[3][0] = 1;
    
    // Lasketaan koordinaatit uudessa koordinaatistossa.
    
    matrix* newCoords = matrixMultiply(basisInv, translatedCoords);
    
    // Tutkitaan, onko z-koordinaatti positiivinen
    
    deleteMatrix(basisInv);
    deleteMatrix(translatedCoords);
    deleteMatrix(normal);
    
    if(newCoords->values[2][0] >= 0) {
        deleteMatrix(newCoords);
        return 1;
    }
    deleteMatrix(newCoords);
    return 0;
}

int isInFrontOfPolygon(polygon* target, polygon* origin) {
    
    // Funktio tarkistaa, onko target-polygoni origin-polygonin
    // etupuolella. 
    
    // Funktio tarkistaa, etteivät osoittimet ole tyhjiä ja että
    // polygonien maailmakoordinaatit on laskettu.
    
    assert(target != NULL && origin != NULL);
    assert(target->verts[0]->world != NULL && origin->verts[0]->world != NULL);
    
    // Tutkitaan, ovatko z-koordinaatit positiivisia
    
    int v0 = pointInFrontOfPolygon(origin, target->verts[0]->world);
    int v1 = pointInFrontOfPolygon(origin, target->verts[1]->world);
    int v2 = pointInFrontOfPolygon(origin, target->verts[2]->world);
    
    if(v0 && v1 && v2) {
        return 1;
    }    
    return 0;
}
