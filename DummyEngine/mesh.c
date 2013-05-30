#include "mesh.h"
#include "matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

vertex* meshNewVertex(mesh* M, float x, float y, float z) {
    
    // Luo uuden verteksin (pisteen avaruudessa) ja liittää sen malliin.
    // Tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    vertex* V = malloc(sizeof(vertex));
    
    V->coords = newMatrix(4, 1);
    
    V->coords->values[0][0] = x;
    V->coords->values[1][0] = y;
    V->coords->values[2][0] = z;
    V->coords->values[3][0] = 1;
    
    V->next = NULL;
    V->prev = NULL;
    
    addVertex(M, V);
    
    return V;
}

void deleteVertex(vertex* V) {
    
    // Poistaa verteksin, tarkistaa, että annettu osoitin ei ole tyhjä.
    
    assert(V != NULL);
    
    vertex* Vnext = V->next;
    vertex* Vprev = V->prev;
    
    if(Vnext != NULL) {
        Vnext->prev = Vprev;
    }
    if(Vprev != NULL) {
        Vprev->next = Vnext;
    }
    
    deleteMatrix(V->coords);
    
    free(V);
}

polygon* meshNewPolygon(mesh* M, vertex* A, vertex* B, vertex* C) {
    
    // Luo uuden polygonin (kolmio kolmiulotteisessa avaruudessa). Tarkistaa,
    // että malli tai annetut pisteet eivät ole tyhjiä.
    
    assert(M != NULL && A != NULL && B != NULL && C != NULL);
    
    polygon* P = malloc(sizeof(polygon));
    
    P->verts[0] = A;
    P->verts[1] = B;
    P->verts[2] = C;
    
    P->color = 0x00ffffff;
    
    P->next = NULL;
    P->prev = NULL;
    
    addPolygon(M, P);
    
    return P;
}

void deletePolygon(polygon* P) {
    
    // Poistaa polygonin, tarkistaa, että annettu osoitin ei ole tyhjä.
    
    assert(P != NULL);
    
    polygon* Pnext = P->next;
    polygon* Pprev = P->prev;
    
    if(Pnext != NULL) {
        Pnext->prev = Pprev;
    }
    if(Pprev != NULL) {
        Pprev->next = Pnext;
    }
    
    free(P);
}

void setPolygonColor(polygon* P, Uint32 color) {
    
    // Asettaa polygonin värin, color-argumentti jakautuu neljään
    // kahdeksan bitin osaan, jotka kuvaavat punaisen, vihreän,
    // sinisen ja alpha-kanavan astetta.
    
    // Tarkistaa, että annettu polygoni ei ole tyhjä.
    
    assert(P != NULL);
    
    P->color = color;
    
}

void deleteMesh(mesh* M) {
    
    // Poistaa mallin poistamalla kaikki sen polygonit ja verteksit. 
    // Tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    polygon* P = M->polygons;
    
    while(P != NULL) {
        deletePolygon(P);
        P = P->next;
    }
    
    vertex* V = M->vertices;
    
    while(V != NULL) {
        deleteVertex(V);
        V = V->next;
    }
    
    free(M);
}

void addPolygon(mesh* M, polygon* P) {
    
    // Lisää polygonin P malliin M lisäämällä sen linkitetyn listan ensimmäiseksi.
    // Tarkistaa, että malli ja polygoni eivät ole tyhjiä.
    
    assert(M != NULL && P != NULL);
    
    polygon* P0 = M->polygons;
    
    if(P0 != NULL) {
        P0->prev = P;
        P->next = P0;
    }
    
    M->polygons = P;
}

void addVertex(mesh* M, vertex* V) {
    
    // Lisää verteksin V malliin M lisäämällä sen linkitetyn listan ensimmäiseksi.
    // Tarkistaa, että malli ja verteksi eivät ole tyhjiä.
    
    assert(M != NULL && V != NULL);
    
    vertex* V0 = M->vertices;
    
    if(V0 != NULL) {
        V0->prev = V;
        V->next = V0;
    }
    
    M->vertices = V;
    
}

vertex* meshGetVertex(mesh* M, int n) {
    
    // Palauttaa n:nnen verteksin mallin M verteksilistasta. Jos
    // n on suurempi kuin verteksien lukumäärä, palauttaa tyhjän osoittimen.
    // Jos n = 0, palauttaa viimeiseksi lisätyn. Tarkistaa, että malli 
    // ei ole tyhjä ja n on positiivinen.
    
    assert(M != NULL && n >= 0);
    
    vertex* V = M->vertices;
    int i = 0;
    
    while(i < n) {
        if(V != NULL) {
            V = V->next;
            i++;
        }
    }
    return V;
}