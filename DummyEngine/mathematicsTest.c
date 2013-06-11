#include "mesh.h"
#include <assert.h>

void mathematicsTest() {
    
    // Tämä testi tarkistaa, matematiikkakirjastoon liittyviä funktioita
    
    // Luodaan verteksit
    
    vertex* V0 = (vertex*)malloc(sizeof(vertex));
    vertex* V1 = (vertex*)malloc(sizeof(vertex));
    vertex* V2 = (vertex*)malloc(sizeof(vertex));
    
    V0->coords = newMatrix(4, 1);
    V1->coords = newMatrix(4, 1);
    V2->coords = newMatrix(4, 1);
    
    V0->coords->values[0][0] = 0;
    V0->coords->values[1][0] = 0;
    V0->coords->values[2][0] = 0;
    V0->coords->values[3][0] = 1;
    
    V1->coords->values[0][0] = 0;
    V1->coords->values[1][0] = 0;
    V1->coords->values[2][0] = 1;
    V1->coords->values[3][0] = 1;
    
    V2->coords->values[0][0] = 0;
    V2->coords->values[1][0] = 1;
    V2->coords->values[2][0] = 0;
    V2->coords->values[3][0] = 1;
    
    vertex* targetV0 = (vertex*)malloc(sizeof(vertex));
    vertex* targetV1 = (vertex*)malloc(sizeof(vertex));
    vertex* targetV2 = (vertex*)malloc(sizeof(vertex));
    
    targetV0->coords = newMatrix(4, 1);
    targetV1->coords = newMatrix(4, 1);
    targetV2->coords = newMatrix(4, 1);
    
    targetV0->coords->values[0][0] = 1;
    targetV0->coords->values[1][0] = 0;
    targetV0->coords->values[2][0] = 0;
    targetV0->coords->values[3][0] = 1;
    
    targetV1->coords->values[0][0] = 1;
    targetV1->coords->values[1][0] = 0;
    targetV1->coords->values[2][0] = 1;
    targetV1->coords->values[3][0] = 1;
    
    targetV2->coords->values[0][0] = 1;
    targetV2->coords->values[1][0] = 1;
    targetV2->coords->values[2][0] = 0;
    targetV2->coords->values[3][0] = 1;
    
    // Liitetään verteksit polygoniin
    
    polygon* origin = (polygon*)malloc(sizeof(polygon));
    
    origin->verts[0] = V0;
    origin->verts[1] = V1;
    origin->verts[2] = V2;
    
    origin->normal = calculatePolygonNormal(origin);
    
    polygon* target = (polygon*)malloc(sizeof(polygon));
    
    target->verts[0] = targetV0;
    target->verts[1] = targetV1;
    target->verts[2] = targetV2;
    
    target->normal = calculatePolygonNormal(target);
    
    // Tarkistetaan, että target on origin-polygonin edellä
    
    assert(isInFrontOfPolygon(target, origin) == 1);
    
    // Poistetaan luodut tietorakenteet
    
    deleteMatrix(target->normal);
    deleteMatrix(origin->normal);
    free(target);
    free(origin);
    deleteMatrix(V0->coords);
    deleteMatrix(V1->coords);
    deleteMatrix(V2->coords);
    deleteMatrix(targetV0->coords);
    deleteMatrix(targetV1->coords);
    deleteMatrix(targetV2->coords);
    free(V0);
    free(V1);
    free(V2);
    free(targetV0);
    free(targetV1);
    free(targetV2);
}
