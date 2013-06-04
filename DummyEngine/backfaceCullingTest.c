#include "SDL/SDL.h"
#include <stdlib.h>
#include "scene.h"

void backfaceCullingTest() {
    
    // Tällä testataan tilan luomisen toimivuutta, funktion pitäisi
    // luoda normaali tila, jossa y-akselin suuntaista palkkia kuvataan
    // yläviistosta. Kuva piirretään wireframe-muodossa ja tallennetaan.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("Backface culling test", "Backface culling test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    drawSceneWireframe(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "cullingTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
    
}