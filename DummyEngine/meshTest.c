#include "mesh.h"
#include "matrix.h"

void meshTest() {
    
    mesh* M = newMesh();
    
    vertex* V1 = meshNewVertex(M, 5.0, 5.0, 5.0);
    vertex* V2 = meshNewVertex(M, 1.0, 1.0, 0);
    vertex* V3 = meshNewVertex(M, -1.0, -2.0, -3.0);
    
    polygon* P = meshNewPolygon(M, V1, V2, V3);
    
    meshTranslate(M, 1.0, 2.0, 3.0);
    
    printMatrix(M->worldTransform);
    
    deleteMesh(M);
    
}