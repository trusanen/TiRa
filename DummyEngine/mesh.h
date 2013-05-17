/* 
 * File:   mesh.h
 * Author: topias
 *
 * Created on May 17, 2013, 8:02 PM
 */

#ifndef MESH_H
#define	MESH_H

#include "matrix.h"

typedef struct {
    matrix* coords;
} vertex;

typedef struct polygon_t {
    vertex* verts[3];
    struct polygon_t* next;
} polygon;

typedef struct {
    polygon* polygons;
} mesh;

vertex* newVertex(float x, float y, float z);
void deleteVertex(vertex* V);

polygon* newPolygon();
void deletePolygon(polygon* P);

mesh* newMesh();
void deleteMesh(mesh* M);
void addPolygon(mesh*M, polygon* P);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MESH_H */

