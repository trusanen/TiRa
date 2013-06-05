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
#include "scene.h"

Uint32 getPixel(SDL_Surface* surface, int x, int y);

void putPixel(SDL_Surface* surface, int x, int y, Uint32 color);
void drawLine(SDL_Surface* surface, float startX, float startY, float endX, float endY, Uint32 color);
void drawCircle(SDL_Surface* surface, float x, float y, float r, Uint32 color);

void drawPolygon(SDL_Surface* surface, polygon* P);
void drawPolygonWireframe(SDL_Surface* surface, polygon* P);
void drawPolygonSolid(SDL_Surface* surface, polygon* P);
void drawMeshWireframe(SDL_Surface* surface, mesh* M);

void drawSceneWireframe(SDL_Surface* surface, scene* scene);
void drawSceneWireframeBackfaceCulling(SDL_Surface* surface, scene* scene);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DRAW_H */

