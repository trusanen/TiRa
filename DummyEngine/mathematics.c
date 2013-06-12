#include "mathematics.h"
#include <assert.h>
#include <stdlib.h>
#include "matrix.h"

int isInFrontOfPolygon(polygon* target, polygon* origin) {
    
    // Funktio tarkistaa, onko target-polygoni origin-polygonin
    // etupuolella. Tämä toteutetaan laskemalla target-polygonin
    // verteksien koordinaatit origin-polygonin verteksien ja normaalin
    // muodostamalla kannalla ja tutkimalla, että sen normaalia
    // vastaava koordinaatti on positiivinen.
    
    // Funktio tarkistaa, etteivät osoittimet ole tyhjiä.
    
    assert(target != NULL && origin != NULL);
    
    // Lasketaan kannanvaihtomatriisi laskemalla kantamatriisin
    // käänteismatriisi
    
    vertex* V0 = origin->verts[0];
    vertex* V1 = origin->verts[1];
    vertex* V2 = origin->verts[2];
    
    matrix* basisInv = newMatrix(4, 4);
    
    float a = V1->coords->values[0][0] - V0->coords->values[0][0];
    float b = V2->coords->values[0][0] - V0->coords->values[0][0];
    float c = origin->normal->values[0][0];
    
    float d = V1->coords->values[1][0] - V0->coords->values[1][0];
    float e = V2->coords->values[1][0] - V0->coords->values[1][0];
    float f = origin->normal->values[1][0];
    
    float g = V1->coords->values[2][0] - V0->coords->values[2][0];
    float h = V2->coords->values[2][0] - V0->coords->values[2][0];
    float k = origin->normal->values[2][0];
    
    
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
    
    // Siirretään tutkittavaa polygonia siten, että origoksi tulee
    // polygonin ensimmäinen verteksi.
    
    matrixMultiplyScalar(origin->verts[0]->coords, -1);
    
    matrix* translatedV0 = matrixSum(target->verts[0]->coords, origin->verts[0]->coords);
    matrix* translatedV1 = matrixSum(target->verts[1]->coords, origin->verts[0]->coords);
    matrix* translatedV2 = matrixSum(target->verts[2]->coords, origin->verts[0]->coords);
    
    // Palautetaan alkuperäisen verteksin koordinaatit
    
    matrixMultiplyScalar(origin->verts[0]->coords, -1);
    
    // Kerrotaan kannanvaihtomatriisilla koordinaattivektoria.
    
    matrix* newV0 = matrixMultiply(basisInv, translatedV0);
    matrix* newV1 = matrixMultiply(basisInv, translatedV1);
    matrix* newV2 = matrixMultiply(basisInv, translatedV2);
    
    // Tutkitaan, ovatko z-koordinaatit positiivisia
    
    if(newV0->values[2][0] > 0 && 
            newV1->values[2][0] > 0 &&
            newV2->values[2][0] > 0) {
        deleteMatrix(basisInv);
        deleteMatrix(translatedV0);
        deleteMatrix(translatedV1);
        deleteMatrix(translatedV2);
        deleteMatrix(newV0);
        deleteMatrix(newV1);
        deleteMatrix(newV2);
        return 1;
    }
    
    deleteMatrix(translatedV0);
    deleteMatrix(translatedV1);
    deleteMatrix(translatedV2);
    deleteMatrix(basisInv);
    deleteMatrix(newV0);
    deleteMatrix(newV1);
    deleteMatrix(newV2);
    
    return 0;
}
