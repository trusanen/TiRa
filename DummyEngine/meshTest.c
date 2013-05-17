#include "mesh.h"

void meshTest() {
    
    vertex* V1 = newVertex(5.0, 5.0, 5.0);
    vertex* V2 = newVertex(1.0, 1.0, 0);
    vertex* V3 = newVertex(-1.0, -2.0, -3.0);
    
    polygon* P = newPolygon(V1, V2, V3);
    
    mesh* M = newMesh();
    
    addPolygon(M, P);
    
    deleteMesh(M);
    
}