#include "SDL/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

sdlTest() {
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    int i = 0;
    int j = 0;
    
    Uint32 pixel = 4294967295;
    
    for(i ; i < 6 ; i++) {
        for(j ; j < 11 ; j++) {
            putPixel(screen, 100 + i, 100 + j, pixel);
        }
        j = 0;
    }
    
    // Piirretään kompassiruusu
    
    drawLine(screen, 200, 200, 200, 190, pixel);
    drawLine(screen, 200, 200, 210, 190, pixel);
    drawLine(screen, 200, 200, 210, 200, pixel);
    drawLine(screen, 200, 200, 210, 210, pixel);
    drawLine(screen, 200, 200, 200, 210, pixel);
    drawLine(screen, 200, 200, 190, 210, pixel);
    drawLine(screen, 200, 200, 190, 200, pixel);
    drawLine(screen, 200, 200, 190, 190, pixel);
    
    // Piirretään ympyrä
    
    drawCircle(screen, 300.0, 300.0, 5.0, 0x0000ff00);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_Quit();
    
}
