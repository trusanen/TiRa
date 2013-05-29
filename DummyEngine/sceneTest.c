#include "SDL/SDL.h"
#include "scene.h"

void sceneTest() {
    
    // Tällä testataan tilan luomisen toimivuutta, funktion pitäisi
    // luoda normaali tila, jossa y-akselin suuntaista palkkia kuvataan
    // yläviistosta. Kuva piirretään wireframe-muodossa ja tallennetaan.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    drawSceneWireframe(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(5000);
    
    SDL_SaveBMP(screen, "sceneTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
    
}
