#include "SDL/SDL.h"
#include <stdlib.h>
#include "scene.h"
#include <math.h>

void backfaceCullingTest() {
    
    // Tällä testataan tilan luomisen toimivuutta, funktion pitäisi
    // luoda normaali tila, jossa y-akselin suuntaista palkkia kuvataan
    // yläviistosta. Kuva piirretään wireframe-muodossa ja tallennetaan.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("Backface culling test", "Backface culling test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    object* unitCube = scn->objects->next;
    
    /*
    objectScale(unitCube, 1/5, 1, 1);
    objectRotate(unitCube, 0, 0, -M_PI/2);
    objectTranslate(unitCube, -3, 3, -3);
    */
    
    drawSceneWireframeBackfaceCulling(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(5000);
    
    SDL_SaveBMP(screen, "cullingTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
    
}