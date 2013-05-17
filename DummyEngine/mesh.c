#include "mesh.h"
#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

vertex* newVertex(float x, float y, float z) {
    
    vertex* V = malloc(sizeof(vertex));
    
    V->coords = newMatrix(3, 1);
    
    V->coords->values[0][0] = x;
    V->coords->values[1][0] = y;
    V->coords->values[2][0] = z;
    
    return V;
}

void deleteVertex(vertex* V) {
    
    assert(V != NULL);
    
    deleteMatrix(V->coords);
    
    free(V);
}

polygon* newPolygon(vertex* A, vertex* B, vertex* C) {
    
    polygon* P = malloc(sizeof(polygon));
    
    P->verts[0] = A;
    P->verts[1] = B;
    P->verts[2] = C;
    
    P->next = NULL;
    
    return P;
}

void deletePolygon(polygon* P) {
    
    deleteVertex(P->verts[0]);
    deleteVertex(P->verts[1]);
    deleteVertex(P->verts[2]);
    
    free(P);
}

mesh* newMesh() {
    
    mesh* M = malloc(sizeof(mesh));
    
    M->polygons = NULL;
    
    return M;
}

void deleteMesh(mesh* M) {
    polygon* P = M->polygons;
    
    while(P != NULL) {
        deletePolygon(P);
        P = P->next;
    }
    
    free(M);
}

polygon* getLastPolygon(mesh* M) {
    if(M->polygons != NULL) {
        polygon* P = M->polygons;
        while(P->next != NULL) {
            P = P->next;
        }
        return P;
    }
    return NULL;
}

void addPolygon(mesh* M, polygon* P) {
    
    if(M->polygons == NULL) {
        M->polygons = P;
    }
    else {
        polygon* P0 = getLastPolygon(M);

        P0->next = P;
    }
}
