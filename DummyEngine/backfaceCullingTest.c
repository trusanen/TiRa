#include "SDL/SDL.h"
#include <stdlib.h>
#include "scene.h"
#include <math.h>
#include "primitives.h"

void backfaceCullingTest() {
    
    // Tällä testataan niiden polygonien leikkaamista pois kuvasta,
    // jotka eivät osoita kameraan päin. Kuvan pitäisi olla sama,
    // kuin edellisessä testissä, mutta kaikki polygonit kuutiosta
    // ja kartiosta, jotka jäävät muiden polygonien peittoon,
    // tulisi olla poistettu.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("Backface culling test", "Backface culling test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    mesh* unitCubeMesh = scn->objects->next->mesh;
    
    // Luodaan yksi pinkki polygoni
    
    object* triangle = sceneNewObject(scn);
    mesh* M1 = sceneNewMesh(scn);
    triangle->mesh = M1;
    
    vertex* V1 = meshNewVertex(M1, -3.0, 7.0, 1.0);
    vertex* V2 = meshNewVertex(M1, -3.0, 7.0, 3.0);
    vertex* V3 = meshNewVertex(M1, -3.0, 9.0, 3.0);
    
    polygon* P = meshNewPolygon(M1, V1, V2, V3);
    
    setPolygonColor(P, 0x00ff00ff);
    
    // Luodaan ruudukko
    
    object* grid = sceneNewObject(scn);
    mesh* M2 = newGrid(scn, 4, 4);
    grid->mesh = M2;
    
    objectTranslate(grid, 7, 7, 0);
    objectRotate(grid, 0, M_PI/4, -M_PI/2);
    
    // Luodaan kartio
    
    object* cone = sceneNewObject(scn);
    mesh* M3 = newCone(scn, 16, 4.0);
    cone->mesh = M3;
    
    objectTranslate(cone, 7, -7, 0);
    
    // Luodaan toinen kuutio
    
    object* cube = sceneNewObject(scn);
    cube->mesh = newUnitCube(scn);
    //cube->mesh = unitCubeMesh;
    
    objectRotate(cube, 0, 0, M_PI/2);
    objectTranslate(cube, 0, -5, 0);
    
    drawSceneWireframeBackfaceCulling(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "cullingTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
    
}