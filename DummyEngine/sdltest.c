#include "SDL/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

sdlTest() {
    
    // Testaa SDL-kirjaston toimivuutta. Testin pitäisi piirtää valkoinen
    // neliö vasempaan alanurkkaan, siitä hieman oikealle vihreä
    // kompassiruusu ja siitä vielä hieman oikealle punainen ympyrä.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    int i = 0;
    int j = 0;
    
    Uint32 white = 0xffffffff;
    Uint32 red = 0x00ff0000;
    Uint32 green = 0x0000ff00;
    
    // Piirretään valkoinen neliö
    
    for(i ; i < 6 ; i++) {
        for(j ; j < 11 ; j++) {
            putPixel(screen, 100 + i, 100 + j, white);
        }
        j = 0;
    }
    
    // Piirretään vihreä kompassiruusu
    
    drawLine(screen, 200, 200, 200, 190, green);
    drawLine(screen, 200, 200, 210, 190, green);
    drawLine(screen, 200, 200, 210, 200, green);
    drawLine(screen, 200, 200, 210, 210, green);
    drawLine(screen, 200, 200, 200, 210, green);
    drawLine(screen, 200, 200, 190, 210, green);
    drawLine(screen, 200, 200, 190, 200, green);
    drawLine(screen, 200, 200, 190, 190, green);
    
    // Piirretään punainen ympyrä
    
    drawCircle(screen, 300.0, 300.0, 5.0, red);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "sdlTest.bmp");
    
    SDL_Quit();
    
}
