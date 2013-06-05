#include "scene.h"
#include <assert.h>

void normalTest() {
    
    // Testataan pinnan normaalien laskemista
    
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
