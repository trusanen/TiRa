#include "mesh.h"
#include "draw.h"

void renderTest() {
    
    // Luodaan testikuutio
    
    mesh* testCube = newMesh();
    
    // Luodaan verteksit, NEU = NorthEastUpper, 
    // SWL = SouthWestLower jne...
    
    vertex* NEU = newVertex(-1, 1, 1);
    vertex* NWU = newVertex(1, 1, 1);
    vertex* SEU = newVertex(-1, 1, -1);
    vertex* SWU = newVertex(1, 1, -1);
    
    vertex* NEL = newVertex(-1, -1, 1);
    vertex* NWL = newVertex(1, -1, 1);
    vertex* SEL = newVertex(-1, -1, -1);
    vertex* SWL = newVertex(1, -1, -1);
    
    // Muodostetaan polygonit
    
    polygon* front1 = newPolygon(SEU, SWU, SWL);
    polygon* front2 = newPolygon(SWL, SEL, SEU);
    setPolygonColor(front1, 0xff000000);
    setPolygonColor(front2, 0xff000000);
    
    polygon* back1 = newPolygon(NEU, NWU, NWL);
    polygon* back2 = newPolygon(NWL, NEL, NEU);
    setPolygonColor(back1, 0x00ff0000);
    setPolygonColor(back2, 0x00ff0000);
    
    polygon* right1 = newPolygon(SEU, NEU, NEL);
    polygon* right2 = newPolygon(NEL, SEL, SEU);
    setPolygonColor(right1, 0x0000ff00);
    setPolygonColor(right2, 0x0000ff00);
    
    polygon* left1 = newPolygon(SWU, NWU, NWL);
    polygon* left2 = newPolygon(NWL, SWL, SWU);
    setPolygonColor(left1, 0xf0f0f000);
    setPolygonColor(left2, 0xf0f0f000);
    
    polygon* top1 = newPolygon(NEU, SEU, SWU);
    polygon* top2 = newPolygon(SWU, NWU, NEU);
    setPolygonColor(top1, 0x0f0f0f00);
    setPolygonColor(top2, 0x0f0f0f00);
    
    polygon* bottom1 = newPolygon(NEL, SEL, SWL);
    polygon* bottom2 = newPolygon(SWL, NWL, NEL);
    setPolygonColor(bottom1, 0xffffff00);
    setPolygonColor(bottom2, 0xffffff00);
    
    // Lisätään polygonit malliin
    
    addPolygon(testCube, front1);
    addPolygon(testCube, front2);
    
    addPolygon(testCube, back1);
    addPolygon(testCube, back2);
    
    addPolygon(testCube, right1);
    addPolygon(testCube, right2);
    
    addPolygon(testCube, left1);
    addPolygon(testCube, left2);
    
    addPolygon(testCube, top1);
    addPolygon(testCube, top2);
    
    addPolygon(testCube, bottom1);
    addPolygon(testCube, bottom2);
    
    // Siirretään mallia hieman
    
    meshTranslate(testCube, 2.0, 2.0, 8.0);
    
    printMatrix(testCube->coords);
    
    // Määritellään näkymän rajat
    
    float Pfar = 30.0;
    float Pnear = 5.0;
    float Pright = -5.0;
    float Pleft = 5.0;
    float Ptop = 5.0;
    float Pbottom = -5.0;
    
    // Lasketaan projektiomatriisi
    
    matrix* projMatrix = newMatrix(4, 4);
    
    projMatrix->values[0][0] = (2*Pnear)/(Pright-Pleft);
    projMatrix->values[1][1] = (2*Pnear)/(Ptop-Pbottom);
    projMatrix->values[0][2] = (Pright + Pleft)/(Pright - Pleft);
    projMatrix->values[1][2] = (Ptop + Pbottom)/(Ptop - Pbottom);
    projMatrix->values[2][2] = -1*(Pfar+Pnear)/(Pfar-Pnear);
    projMatrix->values[3][2] = -1;
    projMatrix->values[2][3] = (-2*Pfar*Pnear)/(Pfar-Pnear);
    
    printMatrix(projMatrix);
    
    // Piirretään
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    matrix* V1;
    matrix* V2;
    matrix* V3;
    
    matrix* V1trans;
    matrix* V2trans;
    matrix* V3trans;
    
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    
    Uint32 white = 0xffffffff;
    polygon* P = testCube->polygons;
    
    while(P != NULL) {
        
        V1trans = matrixMultiply(testCube->worldTransform, P->verts[0]->coords);
        V2trans = matrixMultiply(testCube->worldTransform, P->verts[1]->coords);
        V3trans = matrixMultiply(testCube->worldTransform, P->verts[2]->coords);
        
        V1 = matrixMultiply(projMatrix, V1trans);
        V2 = matrixMultiply(projMatrix, V2trans);
        V3 = matrixMultiply(projMatrix, V3trans);
        
        deleteMatrix(V1trans);
        deleteMatrix(V2trans);
        deleteMatrix(V3trans);
        
        matrixMultiplyScalar(V1, 1.0/V1->values[3][0]);
        matrixMultiplyScalar(V2, 1.0/V2->values[3][0]);
        matrixMultiplyScalar(V3, 1.0/V3->values[3][0]);
        
        printMatrix(V1);
        printMatrix(V2);
        printMatrix(V3);
        
        x1 = 320+(int)(V1->values[0][0]*320+0.5);
        y1 = 240+(int)(V1->values[1][0]*240+0.5);
        x2 = 320+(int)(V2->values[0][0]*320+0.5);
        y2 = 240+(int)(V2->values[1][0]*240+0.5);
        x3 = 320+(int)(V3->values[0][0]*320+0.5);
        y3 = 240+(int)(V3->values[1][0]*240+0.5);
        
        //printf("x1: %d\ny1: %d\nx2: %d\ny2: %d\nx3: %d\ny3: %d\n", x1, y1, x2, y2, x3, y3);
        
        putPixel(screen, x1, y1, white);
        putPixel(screen, x2, y2, white);
        putPixel(screen, x3, y3, white);
        
        
        drawLine(screen, x1, y1, x2, y2, white);
        drawLine(screen, x2, y2, x3, y3, white);
        drawLine(screen, x3, y3, x1, y1, white);
        
        
        P = P->next;
        
        deleteMatrix(V1);
        deleteMatrix(V2);
        deleteMatrix(V3);
    }
    
    SDL_Flip(screen);
    
    SDL_SaveBMP(screen, "render.bmp");
    
    SDL_Delay(5000);
    
    SDL_Quit();
    
    deleteMatrix(projMatrix);
    deleteMesh(testCube);
}
