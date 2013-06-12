/* 
 * File:   mesh.h
 * Author: topias
 *
 * Created on May 17, 2013, 8:02 PM
 */

#ifndef MESH_H
#define	MESH_H

#include "matrix.h"
#include "SDL/SDL.h"

struct scene;

typedef struct vertex_t {
    matrix* coords; // Local coordinates
    matrix* world; // World coordinates
    matrix* NDC; // Normalized Device Coordinates
    matrix* window; // Window coordinates
    struct vertex_t* next;
    struct vertex_t* prev;
} vertex;

typedef struct polygon_t {
    vertex* verts[3];
    Uint32 color;
    matrix* normal;
    struct polygon_t* next;
    struct polygon_t* prev;
} polygon;

typedef struct mesh_t {
    vertex* vertices;
    polygon* polygons;
    struct mesh_t* next;
    struct mesh_t* prev;
} mesh;

vertex* meshNewVertex(mesh* M, float x, float y, float z);
void deleteVertex(vertex* V);

polygon* meshNewPolygon(mesh* M, vertex* A, vertex* B, vertex* C);
void deletePolygon(polygon* P);
void setPolygonColor(polygon* P, Uint32 color);
matrix* calculatePolygonNormal(polygon* P);
void calculateWorldCoordinates(polygon* P, matrix* worldTransform);
void calculateNormalizedDeviceCoordinates(polygon* P, matrix* fullTransform);

void deleteMesh(mesh* M);
void addVertex(mesh* M, vertex* V);
void addPolygon(mesh* M, polygon* P);

vertex* meshGetVertex(mesh* M, int n);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MESH_H */

