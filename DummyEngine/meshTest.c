#include "matrix.h"
#include "scene.h"

void meshTest() {
    
    // Mallitesti, testin pitäisi piirtää normaali tila, jossa on
    // pitkä palkki kuvattuna yläviistosta. Palkki venyy y-akselin
    // suuntaan. Lisäksi piirrettynä pitäisi olla erillinen kolmio.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    object* obj = sceneNewObject(scn);
    mesh* M = sceneNewMesh(scn);
    obj->mesh = M;
    
    vertex* V1 = meshNewVertex(M, -3.0, 3.0, 1.0);
    vertex* V2 = meshNewVertex(M, -3.0, 3.0, 3.0);
    vertex* V3 = meshNewVertex(M, -3.0, 5.0, 3.0);
    
    polygon* P = meshNewPolygon(M, V1, V2, V3);
    
    drawSceneWireframe(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(5000);
    
    SDL_SaveBMP(screen, "meshTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
}