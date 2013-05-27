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

typedef struct vertex_t {
    matrix* coords;
    struct vertex_t* next;
    struct vertex_t* prev;
} vertex;

typedef struct polygon_t {
    vertex* verts[3];
    Uint32 color;
    struct polygon_t* next;
    struct polygon_t* prev;
} polygon;

typedef struct {
    matrix* coords;
    matrix* worldTransform;
    vertex* vertices;
    polygon* polygons;
} mesh;

vertex* meshNewVertex(mesh* M, float x, float y, float z);
void deleteVertex(vertex* V);

polygon* meshNewPolygon(mesh* M, vertex* A, vertex* B, vertex* C);
void deletePolygon(polygon* P);
void setPolygonColor(polygon* P, Uint32 color);

mesh* newMesh();
void deleteMesh(mesh* M);
void addVertex(mesh* M, vertex* V);
void addPolygon(mesh* M, polygon* P);

void meshScale(mesh* M, float xScale, float yScale, float zScale);
void meshRotate(mesh* M, float xRotation, float yRotation, float zRotation);
void meshTranslate(mesh* M, float x, float y, float z);

mesh* newUnitCube();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MESH_H */

