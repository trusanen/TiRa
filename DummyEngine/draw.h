/* 
 * File:   draw.h
 * Author: topias
 *
 * Created on May 19, 2013, 9:09 PM
 */

#ifndef DRAW_H
#define	DRAW_H

#include "SDL/SDL.h"
#include "mesh.h"

Uint32 getPixel(SDL_Surface* surface, int x, int y);
void putPixel(SDL_Surface* surface, int x, int y, Uint32 color);
void drawLine(SDL_Surface* surface, int startX, int startY, int endX, int endY, Uint32 color);
void drawPolygon(SDL_Surface* surface, polygon* P);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DRAW_H */

