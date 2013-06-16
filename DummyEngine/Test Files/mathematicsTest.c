#include "../Header files/mesh.h"
#include <assert.h>

void mathematicsTest() {
    
    // Tämä testi tarkistaa, matematiikkakirjastoon liittyviä funktioita
    
    // Luodaan verteksit. Arvot on keksitty Blenderillä leikkiessä,
    // lopputuloksena tulisi olla kaksi polygonia, jotka osoittavat
    // toisiaan kohti.
    
    vertex* V0 = (vertex*)malloc(sizeof(vertex));
    vertex* V1 = (vertex*)malloc(sizeof(vertex));
    vertex* V2 = (vertex*)malloc(sizeof(vertex));
    
    V0->world = newMatrix(4, 1);
    V1->world = newMatrix(4, 1);
    V2->world = newMatrix(4, 1);
    
    V0->world->values[0][0] = 0;
    V0->world->values[1][0] = 3;
    V0->world->values[2][0] = 2;
    V0->world->values[3][0] = 1;

    V1->world->values[0][0] = 1;
    V1->world->values[1][0] = 3;
    V1->world->values[2][0] = 3;
    V1->world->values[3][0] = 1;

    V2->world->values[0][0] = 0;
    V2->world->values[1][0] = 4;
    V2->world->values[2][0] = 2;
    V2->world->values[3][0] = 1;
    
    vertex* targetV0 = (vertex*)malloc(sizeof(vertex));
    vertex* targetV1 = (vertex*)malloc(sizeof(vertex));
    vertex* targetV2 = (vertex*)malloc(sizeof(vertex));
    
    targetV0->world = newMatrix(4, 1);
    targetV1->world = newMatrix(4, 1);
    targetV2->world = newMatrix(4, 1);
    
    targetV0->world->values[0][0] = 2;
    targetV0->world->values[1][0] = 5;
    targetV0->world->values[2][0] = 0;
    targetV0->world->values[3][0] = 1;
    
    targetV1->world->values[0][0] = 2;
    targetV1->world->values[1][0] = 5;
    targetV1->world->values[2][0] = 1;
    targetV1->world->values[3][0] = 1;
    
    targetV2->world->values[0][0] = 3;
    targetV2->world->values[1][0] = 4;
    targetV2->world->values[2][0] = 1;
    targetV2->world->values[3][0] = 1;
    
    // Liitetään verteksit polygoniin
    
    polygon* origin = (polygon*)malloc(sizeof(polygon));
    
    origin->verts[0] = V0;
    origin->verts[1] = V1;
    origin->verts[2] = V2;
    
    polygon* target = (polygon*)malloc(sizeof(polygon));
    
    target->verts[0] = targetV0;
    target->verts[1] = targetV1;
    target->verts[2] = targetV2;
    
    // Tarkistetaan, että toisen polygonin ensimmäinen verteksi on
    // toisen etupuolella.
    
    assert(pointInFrontOfPolygon(origin, target->verts[0]->world));
    assert(pointInFrontOfPolygon(target, origin->verts[0]->world));
    
    // Tarkistetaan, että target on origin-polygonin edellä
    
    assert(isInFrontOfPolygon(target, origin));
    assert(isInFrontOfPolygon(origin, target));
    
    // Poistetaan luodut tietorakenteet
    
    free(target);
    free(origin);
    deleteMatrix(V0->world);
    deleteMatrix(V1->world);
    deleteMatrix(V2->world);
    deleteMatrix(targetV0->world);
    deleteMatrix(targetV1->world);
    deleteMatrix(targetV2->world);
    free(V0);
    free(V1);
    free(V2);
    free(targetV0);
    free(targetV1);
    free(targetV2);
}
