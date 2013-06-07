#include "scene.h"
#include <assert.h>
#include <math.h>

mesh* newUnitCube(scene* scene) {
    
    // Luo yksikkökuution
    
    mesh* unitCube = sceneNewMesh(scene);
    
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
    
    // Muodostetaan polygonit, verteksit määritellään myötäpäivään
    // pinnan normaalin suhteen.
    
    polygon* front1 = meshNewPolygon(unitCube, SWU, SEU, SEL);
    polygon* front2 = meshNewPolygon(unitCube, SEL, SWL, SWU);
    setPolygonColor(front1, 0x00ff0000);
    setPolygonColor(front2, 0x00ff0000);
    
    polygon* back1 = meshNewPolygon(unitCube, NEU, NWU, NWL);
    polygon* back2 = meshNewPolygon(unitCube, NWL, NEL, NEU);
    setPolygonColor(back1, 0x000f0f0f);
    setPolygonColor(back2, 0x000f0f0f);
    
    polygon* right1 = meshNewPolygon(unitCube, SEU, NEU, NEL);
    polygon* right2 = meshNewPolygon(unitCube, NEL, SEL, SEU);
    setPolygonColor(right1, 0x000000ff);
    setPolygonColor(right2, 0x000000ff);
    
    polygon* left1 = meshNewPolygon(unitCube, NWU, SWU, SWL);
    polygon* left2 = meshNewPolygon(unitCube, SWL, NWL, NWU);
    setPolygonColor(left1, 0x00f0f0f0);
    setPolygonColor(left2, 0x00f0f0f0);
    
    polygon* top1 = meshNewPolygon(unitCube, NEU, SEU, SWU);
    polygon* top2 = meshNewPolygon(unitCube, SWU, NWU, NEU);
    setPolygonColor(top1, 0x0000ff00);
    setPolygonColor(top2, 0x0000ff00);
    
    polygon* bottom1 = meshNewPolygon(unitCube, SWL, SEL, NEL);
    polygon* bottom2 = meshNewPolygon(unitCube, NEL, NWL, SWL);
    setPolygonColor(bottom1, 0x00ffffff);
    setPolygonColor(bottom2, 0x00ffffff);
    
    return unitCube;
}

mesh* newGrid(scene* scene, int x, int y) {
    
    // Luo x*y -ruudukon, tarkistaa, että x ja y ovat suurempia kuin 1
    
    assert(x > 0 && y > 0);
    
    mesh* grid = sceneNewMesh(scene);
    
    int i = 0;
    int j = 0;
    
    for(j ; j <= y ; j++) {
        for(i ; i <= x ; i++) {
            meshNewVertex(grid, i, j, 0);
        }
        i = 0;
    }
    
    vertex* NW;
    vertex* NE;
    vertex* SE;
    vertex* SW;
    
    polygon* p1;
    polygon* p2;
    
    int white = 0x00ffffff;
    int gray = 0x00666666;
    
    i = 0;
    j = 0;
    
    for(j ; j < y ; j++) {
        for(i ; i < x ; i++) {
            NE = meshGetVertex(grid, (x+1)*j+i);
            NW = meshGetVertex(grid, (x+1)*j+i+1);
            SE = meshGetVertex(grid, (x+1)*(j+1)+i);
            SW = meshGetVertex(grid, (x+1)*(j+1)+i+1);
            p1 = meshNewPolygon(grid, NW, NE, SE);
            p2 = meshNewPolygon(grid, SE, SW, NW);
            if((i+j) % 2 == 0) {
                setPolygonColor(p1, white);
                setPolygonColor(p2, white);
            }
            else {
                setPolygonColor(p1, gray);
                setPolygonColor(p2, gray);
            }
        }
        i = 0;
    }
    
    return grid;
}

mesh* newCone(scene* scene, int vertices, float height) {
    
    // Luo kartion, jonka kannassa on vertices-määrä verteksejä ja
    // sen korkeus on height. Tarkistaa, että scene ei ole tyhjä osoitin
    // ja verteksejä on enemmän kuin 3.
    
    assert(scene != NULL && vertices > 2);
    
    mesh* cone = sceneNewMesh(scene);
    
    vertex* top = meshNewVertex(cone, 0, 0, height);
    vertex* bottom = meshNewVertex(cone, 0, 0, 0);
    vertex* start = meshNewVertex(cone, 1, 0, 0);
    
    vertex* first = start;
    vertex* new;
    
    int white = 0x00ffffff;
    int red = 0x00ff0000;
    
    polygon* pTop;
    polygon* pBottom;
    
    float angle = 2*M_PI/vertices;
    
    int i = 1;
    
    for(i ; i < vertices ; i++) {
        new = meshNewVertex(cone, cos(i*angle), sin(i*angle), 0);
        pTop = meshNewPolygon(cone, new, first, top);
        pBottom = meshNewPolygon(cone, first, new, bottom);
        if(i % 2 == 0) {
            setPolygonColor(pTop, white);
            setPolygonColor(pBottom, red);
        }
        else {
            setPolygonColor(pTop, red);
            setPolygonColor(pBottom, white);
        }
        first = new;
    }
    
    meshNewPolygon(cone, start, first, top);
    meshNewPolygon(cone, first, start, bottom);
    
    return cone;
}
