#include "draw.h"

void putPixel(SDL_Surface* surface, int x, int y, Uint32 p) {
    
    Uint32* pixels = (Uint32*)surface->pixels;
    
    pixels[(y * surface->w) + x] = p;
    
}

void drawPolygon(SDL_Surface* surface, polygon* P) {
    
    
    
}
