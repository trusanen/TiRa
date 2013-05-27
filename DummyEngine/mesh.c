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

mesh* newMesh() {
    
    // Luo uuden 3D-mallin, joka on aluksi tyhjä. Malli koostuu polygoneista,
    // jotka tallennetaan yksisuuntaisena linkitettynä listana.
    
    mesh* M = malloc(sizeof(mesh));
    
    M->coords = newMatrix(4,1);
    matrixFill(M->coords, 0);
    M->coords->values[3][0] = 1.0;
    
    M->worldTransform = identityMatrix(4);
    
    M->vertices = NULL;
    M->polygons = NULL;
    
    return M;
}

void deleteMesh(mesh* M) {
    
    // Poistaa mallin poistamalla kaikki sen polygonit ja verteksit. 
    // Tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    deleteMatrix(M->coords);
    deleteMatrix(M->worldTransform);
    
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

void meshTranslate(mesh* M, float x, float y, float z) {
    
    // Siirtää mallia M x-, y- ja z-akselien suuntaisesti. Tarkistaa, että
    // malli ei ole tyhjä.
    
    assert(M != NULL);
    
    // Siirtomatriisi on seuraavanlainen:
    //
    // [ 1 0 0 x ]
    // [ 0 1 0 y ]
    // [ 0 0 1 z ]
    // [ 0 0 0 1 ]
    //
    // Kun tällä kerrotaan koordinaattimatriisia, saadaan
    //
    // [ x0 + x ]
    // [ y0 + y ]
    // [ z0 + z ]
    // [   1    ]
    //
    // eli mallia on siirretty x:n, y:n ja z:n verran akseleita pitkin.
    
    // Asetetaan mallin siirtomatriisiin oikeat arvot
    
    M->worldTransform->values[0][3] = x;
    M->worldTransform->values[1][3] = y;
    M->worldTransform->values[2][3] = z;
}

void meshRotate(mesh* M, float xRotation, float yRotation, float zRotation) {
    
    // Kääntää mallia globaalin avaruuden (world space) standardikannan
    // x-, y- ja z-akselien ympäri.
    
    // Kääntö x-akselin ympäri voidaan määritellä matriisilla
    
    //      [ 1   0       0    0 ]
    // Rx = [ 0 cos(t) -sin(t) 0 ]
    //      [ 0 sin(t)  cos(t) 0 ]
    //      [ 0   0       0    1 ]
    
    // Samanlainen matriisi voidaan määritellä myös käännölle y- ja 
    // z-akselien ympäri. Kun nämä matriisit kerrotaan keskenään, saadaan
    // kokonaiskääntö R = Rz * Ry * Rx.
    
    // Funktio asettaa vain oikeat arvot matriisimuunnoksen vastaaviin
    // kohtiin. Funktio tarkistaa, että malli ei ole tyhjä.
    
    assert(M != NULL);
    
    M->worldTransform->values[0][0] = cos(yRotation)*cos(zRotation);
    M->worldTransform->values[0][1] = sin(xRotation)*sin(yRotation)*cos(zRotation)
            - cos(xRotation)*sin(zRotation);
    M->worldTransform->values[0][2] = cos(xRotation)*sin(yRotation)*cos(zRotation)
            + sin(xRotation)*sin(zRotation);
    M->worldTransform->values[1][0] = cos(yRotation)*sin(zRotation);
    M->worldTransform->values[1][1] = cos(xRotation)*cos(zRotation)
            + sin(xRotation)*sin(yRotation)*sin(zRotation);
    M->worldTransform->values[1][2] = -sin(xRotation)*cos(zRotation)
            + cos(xRotation)*sin(yRotation)*sin(zRotation);
    M->worldTransform->values[2][0] = -sin(yRotation);
    M->worldTransform->values[2][1] = sin(xRotation)*cos(yRotation);
    M->worldTransform->values[2][2] = cos(xRotation)*cos(yRotation);
}

void meshScale(mesh* M, float xScale, float yScale, float zScale) {
    
    // Skaalaa mallia globaalin avaruuden x-, y- ja z-akseleiden suuntaisesti.
    
    // Skaalausmatriisi voidaan määritellä seuraavasti:
    
    //     [ Sx 0  0  0 ]
    // S = [ 0  Sy 0  0 ]
    //     [ 0  0  Sz 0 ]
    //     [ 0  0  0  1 ]
    
    // Funktio asettaa kertoimet oikeisiin kohtiin mallin muunnosmatriisissa.
    // Funktio tarkistta, että annettu malli ei ole tyhjä.
    
    assert(M != NULL);
    
    M->worldTransform->values[0][0] = M->worldTransform->values[0][0]*xScale;
    M->worldTransform->values[1][0] = M->worldTransform->values[1][0]*xScale;
    M->worldTransform->values[2][0] = M->worldTransform->values[2][0]*xScale;
    
    M->worldTransform->values[0][1] = M->worldTransform->values[0][1]*yScale;
    M->worldTransform->values[1][1] = M->worldTransform->values[1][1]*yScale;
    M->worldTransform->values[2][1] = M->worldTransform->values[2][1]*yScale;
    
    M->worldTransform->values[0][2] = M->worldTransform->values[0][2]*zScale;
    M->worldTransform->values[1][2] = M->worldTransform->values[1][2]*zScale;
    M->worldTransform->values[2][2] = M->worldTransform->values[2][2]*zScale;
}

mesh* newUnitCube() {
    
    // Luodaan testikuutio
    
    mesh* unitCube = newMesh();
    
    // Luodaan verteksit, NEU = NorthEastUpper, 
    // SWL = SouthWestLower jne...
    
    vertex* NEU = meshNewVertex(unitCube, -1, 1, 1);
    vertex* NWU = meshNewVertex(unitCube, 1, 1, 1);
    vertex* SEU = meshNewVertex(unitCube, -1, 1, -1);
    vertex* SWU = meshNewVertex(unitCube, 1, 1, -1);
    
    vertex* NEL = meshNewVertex(unitCube, -1, -1, 1);
    vertex* NWL = meshNewVertex(unitCube, 1, -1, 1);
    vertex* SEL = meshNewVertex(unitCube, -1, -1, -1);
    vertex* SWL = meshNewVertex(unitCube, 1, -1, -1);
    
    // Muodostetaan polygonit
    
    polygon* front1 = meshNewPolygon(unitCube, SEU, SWU, SWL);
    polygon* front2 = meshNewPolygon(unitCube, SWL, SEL, SEU);
    setPolygonColor(front1, 0xff000000);
    setPolygonColor(front2, 0xff000000);
    
    polygon* back1 = meshNewPolygon(unitCube, NEU, NWU, NWL);
    polygon* back2 = meshNewPolygon(unitCube, NWL, NEL, NEU);
    setPolygonColor(back1, 0x00ff0000);
    setPolygonColor(back2, 0x00ff0000);
    
    polygon* right1 = meshNewPolygon(unitCube, SEU, NEU, NEL);
    polygon* right2 = meshNewPolygon(unitCube, NEL, SEL, SEU);
    setPolygonColor(right1, 0x0000ff00);
    setPolygonColor(right2, 0x0000ff00);
    
    polygon* left1 = meshNewPolygon(unitCube, SWU, NWU, NWL);
    polygon* left2 = meshNewPolygon(unitCube, NWL, SWL, SWU);
    setPolygonColor(left1, 0xf0f0f000);
    setPolygonColor(left2, 0xf0f0f000);
    
    polygon* top1 = meshNewPolygon(unitCube, NEU, SEU, SWU);
    polygon* top2 = meshNewPolygon(unitCube, SWU, NWU, NEU);
    setPolygonColor(top1, 0x0f0f0f00);
    setPolygonColor(top2, 0x0f0f0f00);
    
    polygon* bottom1 = meshNewPolygon(unitCube, NEL, SEL, SWL);
    polygon* bottom2 = meshNewPolygon(unitCube, SWL, NWL, NEL);
    setPolygonColor(bottom1, 0xffffff00);
    setPolygonColor(bottom2, 0xffffff00);
    
    return unitCube;
}