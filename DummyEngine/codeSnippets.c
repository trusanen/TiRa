/*
#include <assert.h>
#include "mesh.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SDL/SDL.h"

// Tästä tiedostosta löytyy koodinpätkiä, joita saatan tarvita ehkä vielä joskus.

void meshTranslateOld(mesh* M, float x, float y, float z) {
    
    // Siirtää mallia M x-, y- ja z-akselien suuntaisesti. Tarkistaa, että
    // malli ei ole tyhjä.
    
    assert(M != NULL);
    
    // Siirtomatriisi on seuraavanlainen:
    //
    // [ 1 0 0 x ]
    // [ 0 1 0 y ]
    // [ 0 0 1 z ]
    // [ 0 0 0 1 ]
    //
    // Kun tällä kerrotaan koordinaattimatriisia, saadaan
    //
    // [ x0 + x ]
    // [ y0 + y ]
    // [ z0 + z ]
    // [   1    ]
    //
    // eli mallia on siirretty x:n, y:n ja z:n verran akseleita pitkin.
    
    // Luodaan siirtomatriisi
    
    matrix* translationMatrix = newMatrix(4, 4);
    matrixFill(translationMatrix, 0);
    
    translationMatrix->values[0][0] = 1;
    translationMatrix->values[1][1] = 1;
    translationMatrix->values[2][2] = 1;
    translationMatrix->values[3][3] = 1;
    
    translationMatrix->values[0][3] = x;
    translationMatrix->values[1][3] = y;
    translationMatrix->values[2][3] = z;
    
    // Suoritetaan matriisikertolasku
    
    matrix* result = matrixMultiply(translationMatrix, M->coords);
    
    // Poistetaan alkuperäinen koordinaattimatriisi ja asetetaan
    // uusi laskettu tilalle. Vapautetaan myös siirtomatriisin käyttämä
    // tila.
    
    free(M->coords);
    
    M->coords = result;
    
    free(translationMatrix);
}

polygon* getLastPolygon(mesh* M) {
    
    // Hakee mallin M ensimmäiseksi lisätyn polygonin, eli linkitetyn listan
    // viimeisen alkion. Tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    if(M->polygons != NULL) {
        polygon* P = M->polygons;
        while(P->next != NULL) {
            P = P->next;
        }
        return P;
    }
    return NULL;
}

mesh* newUnitCubeOld() {
    
    // Luo yksikkökuution
    
    mesh* unitCube = newMesh();
    
    // Luodaan verteksit, NEU = NorthEastUpper, 
    // SWL = SouthWestLower jne...
    
    // TÄLLÄ HETKELLÄ VIELÄ MÄÄRITELTY KUVAKULMA-AVARUUDESSA!
    // VAIHDA MYÖHEMMIN!
    
    vertex* NEU = meshNewVertex(unitCube, -1, 1, 1);
    vertex* NWU = meshNewVertex(unitCube, 1, 1, 1);
    vertex* SEU = meshNewVertex(unitCube, -1, 1, -1);
    vertex* SWU = meshNewVertex(unitCube, 1, 1, -1);
    
    vertex* NEL = meshNewVertex(unitCube, -1, -1, 1);
    vertex* NWL = meshNewVertex(unitCube, 1, -1, 1);
    vertex* SEL = meshNewVertex(unitCube, -1, -1, -1);
    vertex* SWL = meshNewVertex(unitCube, 1, -1, -1);
    
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

void renderTestOld() {
    
    // Luodaan testikuutio
    
    mesh* testMesh = newUnitCubeOld();
    
    // Siirretään mallia hieman
    
    meshScale(testMesh, 1, 2, 1);
    meshTranslate(testMesh, -2.0, 0, 9);
    meshRotate(testMesh, 0, M_PI/4, 0);
    
    printMatrix(testMesh->coords);
    
    // Määritellään näkymän rajat
    
    float Pfar = 30.0;
    float Pnear = 5.0;
    float Pright = -5.0;
    float Pleft = 5.0;
    float Ptop = 5.0;
    float Pbottom = -5.0;
    
    // Lasketaan projektiomatriisi
    
    matrix* projMatrix = newMatrix(4, 4);
    matrixFill(projMatrix, 0);
    
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
    polygon* P = testMesh->polygons;
    
    while(P != NULL) {
        
        V1trans = matrixMultiply(testMesh->worldTransform, P->verts[0]->coords);
        V2trans = matrixMultiply(testMesh->worldTransform, P->verts[1]->coords);
        V3trans = matrixMultiply(testMesh->worldTransform, P->verts[2]->coords);
        
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
    deleteMesh(testMesh);
}

matrix* calculatePolygonNormal(polygon* P) {
    
    // Laskee polygonin normaalin ja sijoittaa sen polygonin keskelle.
    // Verteksien tulee olla määritelty myötäpäivään pinnan normaalin
    // suhteen. Tarkistaa, että osoitin ei ole tyhjä.
    
    assert(P != NULL);
    
    matrix* u = newMatrix(3,1);
    matrix* v = newMatrix(3,1);
    
    // Määritellään vektorit u ja v, jotka määrittävät tason
    
    u->values[0][0] = P->verts[1]->coords->values[0][0] 
            - P->verts[0]->coords->values[0][0];
    u->values[1][0] = P->verts[1]->coords->values[1][0] 
            - P->verts[0]->coords->values[1][0];
    u->values[2][0] = P->verts[1]->coords->values[2][0] 
            - P->verts[0]->coords->values[2][0];
    
    v->values[0][0] = P->verts[2]->coords->values[0][0] 
            - P->verts[1]->coords->values[0][0];
    v->values[1][0] = P->verts[2]->coords->values[1][0] 
            - P->verts[1]->coords->values[1][0];
    v->values[2][0] = P->verts[2]->coords->values[2][0] 
            - P->verts[1]->coords->values[2][0];
    
    // Lasketaan normaali
    
    matrix* normal = newMatrix(4, 1);
    
    normal->values[0][0] = u->values[1][0]*v->values[2][0] 
            - u->values[2][0]*v->values[1][0];
    normal->values[1][0] = u->values[2][0]*v->values[0][0] 
            - u->values[0][0]*v->values[2][0];
    normal->values[2][0] = u->values[0][0]*v->values[1][0] 
            - u->values[1][0]*v->values[0][0];
    normal->values[3][0] = 1;
    
    deleteMatrix(u);
    deleteMatrix(v);
    
    return normal;
}
*/
