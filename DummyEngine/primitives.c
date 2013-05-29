#include "mesh.h"
#include <assert.h>

mesh* newUnitCube() {
    
    // Luo yksikkökuution
    
    mesh* unitCube = newMesh();
    
    // Luodaan verteksit, NEU = NorthEastUpper, 
    // SWL = SouthWestLower jne...
    
    vertex* NEU = meshNewVertex(unitCube, 1, 1, 1);
    vertex* NWU = meshNewVertex(unitCube, -1, 1, 1);
    vertex* SEU = meshNewVertex(unitCube, 1, -1, 1);
    vertex* SWU = meshNewVertex(unitCube, -1, -1, 1);
    
    vertex* NEL = meshNewVertex(unitCube, 1, 1, -1);
    vertex* NWL = meshNewVertex(unitCube, -1, 1, -1);
    vertex* SEL = meshNewVertex(unitCube, 1, -1, -1);
    vertex* SWL = meshNewVertex(unitCube, -1, -1, -1);
    
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

mesh* newGrid(int x, int y) {
    
    // Luo x*y -ruudukon, tarkistaa, että x ja y ovat suurempia kuin 1
    
    // KESKEN, VIIMEISTELE!
    
    assert(x > 0 && y > 0);
    
    mesh* grid = newMesh();
    
    vertex* NW = meshNewVertex(grid, 0, 0, 0);
    vertex* SW = meshNewVertex(grid, 0, 1, 0);
    vertex* NE = meshNewVertex(grid, 1, 1, 0);
    vertex* SE = NULL;
    
    int i = 0;
    int j = 0;
    
    for(i ; i < x ; i++) {
        for(j ; j < y ; j++) {
            meshNewVertex(grid, i, j, 0);
        }
        j = 0;
    }
    
    return grid;
}
