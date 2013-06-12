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
    
    V->world = NULL;
    V->NDC = NULL;
    V->window = NULL;
    
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
    
    if(V->world != NULL) {
        deleteMatrix(V->world);
    }
    
    if(V->NDC != NULL) {
        deleteMatrix(V->NDC);
    }
    
    if(V->window != NULL) {
        deleteMatrix(V->window);
    }
    
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
    
    P->normal = calculatePolygonNormal(P);
    
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
    
    deleteMatrix(P->normal);
    
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

matrix* calculatePolygonNormal(polygon* P) {
    
    // Laskee polygonin normaalin ja sijoittaa sen polygonin keskelle.
    // Verteksien tulee olla määritelty myötäpäivään pinnan normaalin
    // suhteen. Tarkistaa, että osoitin ei ole tyhjä.
    
    assert(P != NULL);
    
    matrix* u = newMatrix(3,1);
    matrix* v = newMatrix(3,1);
    
    // Määritellään vektorit u ja v, jotka määrittävät tason
    
    u->values[0][0] = P->verts[1]->coords->values[0][0] 
            - P->verts[0]->coords->values[0][0];
    u->values[1][0] = P->verts[1]->coords->values[1][0] 
            - P->verts[0]->coords->values[1][0];
    u->values[2][0] = P->verts[1]->coords->values[2][0] 
            - P->verts[0]->coords->values[2][0];
    
    v->values[0][0] = P->verts[2]->coords->values[0][0] 
            - P->verts[1]->coords->values[0][0];
    v->values[1][0] = P->verts[2]->coords->values[1][0] 
            - P->verts[1]->coords->values[1][0];
    v->values[2][0] = P->verts[2]->coords->values[2][0] 
            - P->verts[1]->coords->values[2][0];
    
    // Lasketaan normaali
    
    matrix* normal = newMatrix(4, 1);
    
    normal->values[0][0] = -u->values[1][0]*v->values[2][0] 
            + u->values[2][0]*v->values[1][0];
    normal->values[1][0] = -u->values[2][0]*v->values[0][0] 
            + u->values[0][0]*v->values[2][0];
    normal->values[2][0] = -u->values[0][0]*v->values[1][0] 
            + u->values[1][0]*v->values[0][0];
    normal->values[3][0] = 1;
    
    deleteMatrix(u);
    deleteMatrix(v);
    
    return normal;
}

void calculateWorldCoordinates(polygon* P, matrix* worldTransform) {
    
    // Laskee polygonin verteksien oikeat koordinaatit globaalissa
    // avaruudessa. Tarkistaa, että annetut osoittimet eivät ole
    // tyhjiä.
    
    assert(P != NULL && worldTransform != NULL);
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        
        // Poistetaan edellinen world-koordinaattivektori
        
        if(P->verts[i]->world != NULL) {
            deleteMatrix(P->verts[i]->world);
            P->verts[i]->world = NULL;
        }
        
        // Muunnetaan koordinaatit tila-avaruuteen (world space)
        
        P->verts[i]->world = matrixMultiply(worldTransform, P->verts[i]->coords); 
    }
}

void calculateNormalizedDeviceCoordinates(polygon* P, matrix* fullTransform) {
    
    // Laskee polygonin verteksien koordinaatit näytöllä 
    // (NDC = Normalized Device Coordinates). Tarkistaa,
    // että annetut osoittimet eivät ole tyhjiä.
    
    assert(P != NULL && fullTransform != NULL);
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        
        // Poistetaan edellinen NDC-koordinaattivektori
        
        if(P->verts[i]->NDC != NULL) {
            deleteMatrix(P->verts[i]->NDC);
            P->verts[i]->NDC = NULL;
        }
        
        // Muunnetaan koordinaatit leikkausavaruuteen (clip space)
        
        P->verts[i]->NDC = matrixMultiply(fullTransform, P->verts[i]->coords);
        
        // Koordinaattien palauttaminen w = 1 avaruuteen,
        // ns. "Perspective divide"
        
        matrixMultiplyScalar(P->verts[i]->NDC, 1.0/P->verts[i]->NDC->values[3][0]);   
    }
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