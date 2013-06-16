#include "../Header files/matrix.h"
#include "../Header files/scene.h"
#include "../Header files/primitives.h"
#include <math.h>

void meshTest() {
    
    // Mallitesti, testin pitäisi piirtää normaali tila, jossa on
    // pitkä palkki kuvattuna yläviistosta. Palkki venyy y-akselin
    // suuntaan. Lisäksi piirrettynä pitäisi olla erillinen kolmio.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("Mesh test", "Mesh test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    object* triangle = sceneNewObject(scn);
    mesh* M1 = sceneNewMesh(scn);
    triangle->mesh = M1;
    
    vertex* V1 = meshNewVertex(M1, -3.0, 7.0, 1.0);
    vertex* V2 = meshNewVertex(M1, -3.0, 7.0, 3.0);
    vertex* V3 = meshNewVertex(M1, -3.0, 9.0, 3.0);
    
    polygon* P = meshNewPolygon(M1, V1, V2, V3);
    
    object* grid = sceneNewObject(scn);
    mesh* M2 = newGrid(scn, 4, 4);
    grid->mesh = M2;
    
    objectTranslate(grid, 7, 7, 0);
    objectRotate(grid, 0, M_PI/4, -M_PI/2);
    
    object* cone = sceneNewObject(scn);
    mesh* M3 = newCone(scn, 16, 4.0);
    cone->mesh = M3;
    
    objectTranslate(cone, 7, -7, 0);
    
    drawSceneWireframe(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "meshTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
}