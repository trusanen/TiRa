#include "scene.h"
#include <assert.h>

void normalTest() {
    
    // Tämä testaa pinnan normaalien laskemista. Se luo perustilan,
    // josta se ottaa yksikkökuution viimeisimmän polygonin,
    // joka on toinen pohjatasoista. Tämän normaalin tulisi olla
    // vektori
    
    //     [ 0 ]
    // n = [ 0 ]
    //     [ 4 ]
    //     [ 1 ]
    
    scene* scn = newScene();
    
    object* unitCube = scn->objects->next;
    
    polygon* bottom2 = unitCube->mesh->polygons;
    
    matrix* normal = calculatePolygonNormal(bottom2);
    
    assert(normal->values[0][0] == 0);
    assert(normal->values[1][0] == 0);
    assert(normal->values[2][0] == 4);
    assert(normal->values[3][0] == 1);
    
    deleteMatrix(normal);
    deleteScene(scn);
}
