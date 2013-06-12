#include "mathematics.h"
#include <assert.h>
#include <stdlib.h>
#include "matrix.h"

int isInFrontOfPolygon(polygon* target, polygon* origin) {
    
    // Funktio tarkistaa, onko target-polygoni origin-polygonin
    // etupuolella. Tämä toteutetaan laskemalla target-polygonin
    // verteksien koordinaatit origin-polygonin suuntavektoreiden 
    // ja normaalin muodostamalla kannalla ja tutkimalla, että sen 
    // normaalia vastaava koordinaatti on positiivinen.
    
    // Funktio tarkistaa, etteivät osoittimet ole tyhjiä. Funktio
    // myös olettaa, että polygonien maailmakoordinaatit on laskettu.
    
    assert(target != NULL && origin != NULL);
    assert(target->verts[0]->world != NULL && origin->verts[0]->world != NULL);
    
    // Lasketaan kannanvaihtomatriisi laskemalla kantamatriisin
    // käänteismatriisi
    
    vertex* V0 = origin->verts[0];
    vertex* V1 = origin->verts[1];
    vertex* V2 = origin->verts[2];
    
    matrix* normal = calculatePolygonWorldNormal(origin);
    
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
    
    // Siirretään tutkittavaa polygonia siten, että origoksi tulee
    // polygonin ensimmäinen verteksi.
    
    matrix* translatedV[3];
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        translatedV[i] = newMatrix(4, 1);
        translatedV[i]->values[0][0] = target->verts[i]->world->values[0][0]
                - V0->world->values[0][0];
        translatedV[i]->values[1][0] = target->verts[i]->world->values[1][0]
                - V0->world->values[1][0];
        translatedV[i]->values[2][0] = target->verts[i]->world->values[2][0]
                - V0->world->values[2][0];
        translatedV[i]->values[3][0] = 1;
    }
    
    // Kerrotaan kannanvaihtomatriisilla koordinaattivektoria.
    
    matrix* newV0 = matrixMultiply(basisInv, translatedV[0]);
    matrix* newV1 = matrixMultiply(basisInv, translatedV[1]);
    matrix* newV2 = matrixMultiply(basisInv, translatedV[2]);
    
    // Tutkitaan, ovatko z-koordinaatit positiivisia
    
    if(newV0->values[2][0] >= 0 && 
            newV1->values[2][0] >= 0 &&
            newV2->values[2][0] >= 0) {
        deleteMatrix(basisInv);
        deleteMatrix(translatedV[0]);
        deleteMatrix(translatedV[1]);
        deleteMatrix(translatedV[2]);
        deleteMatrix(newV0);
        deleteMatrix(newV1);
        deleteMatrix(newV2);
        return 1;
    }
    
    deleteMatrix(translatedV[0]);
    deleteMatrix(translatedV[1]);
    deleteMatrix(translatedV[2]);
    deleteMatrix(basisInv);
    deleteMatrix(newV0);
    deleteMatrix(newV1);
    deleteMatrix(newV2);
    
    return 0;
}
