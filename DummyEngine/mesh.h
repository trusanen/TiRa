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

typedef struct {
    matrix* coords;
} vertex;

typedef struct polygon_t {
    vertex* verts[3];
    Uint32 color;
    struct polygon_t* next;
} polygon;

typedef struct {
    matrix* coords;
    matrix* rotation;
    polygon* polygons;
} mesh;

vertex* newVertex(float x, float y, float z);
void deleteVertex(vertex* V);

polygon* newPolygon(vertex* A, vertex* B, vertex* C);
void deletePolygon(polygon* P);
void setPolygonColor(polygon* P, Uint32 color);

mesh* newMesh();
void deleteMesh(mesh* M);
void addPolygon(mesh*M, polygon* P);

void meshScale(mesh* M, float x, float y, float z);
void meshRotate(mesh* M, float xRotation, float yRotation, float zRotation);
void meshTranslate(mesh* M, float x, float y, float z);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MESH_H */

