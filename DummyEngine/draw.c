#include "draw.h"
#include "scene.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

void putPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    
    // Piirtää pikselin näytölle, (0, 0) on ruudun vasen alakulma.
    
    Uint32* pixels = (Uint32*)surface->pixels;
    
    pixels[((surface->h - y) * surface->w) + x] = color;
    
}

void drawLine(SDL_Surface* surface, float startX, float startY, float endX, float endY, Uint32 color) {
        
    // Piirtää viivan näytölle, käyttää Bresenhamin algoritmia
    // optimoituna käyttämään pelkkiä kokonaislukuja.
    // Ks. Wikipedia: Bresenham Line Algorithm
    
    // Liukulukujen pyöristys lähimpään kokonaislukuun.
    
    int x0 = (int)(startX + 0.5);
    int x1 = (int)(endX + 0.5);
    int y0 = (int)(startY + 0.5);
    int y1 = (int)(endY + 0.5);
    
    int tmp;
    
    int steep = abs(y1 - y0) > abs(x1 - x0);
    
    // Jos y:n muutos on suurempaa kuin x:n muutos, vaihdetaan koordinaatti-
    // akseleita keskenään. Tämä estää sellaiset tilanteet, joissa
    // viiva on esimerkiksi pystysuora.
    
    if(steep) {
        tmp = x0;
        x0 = y0;
        y0 = tmp;
        tmp = x1;
        x1 = y1;
        y1 = tmp;
    }
    
    // Tarkistetaan, että piste, josta viivaa aletaan piirtämään löytyy
    // loppupisteen vasemmalta puolelta. Jos näin ei ole, vaihdetaan
    // pisteiden paikkoja.
    
    if(x0 > x1) {
        tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }
    
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = deltax / 2;
    int ystep;
    
    // Jos suora on laskeva, y:n muutos on negatiivinen ja nousevan
    // suoran taas positiivinen
    
    if(y0 < y1) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }
    
    int x = x0;
    int y = y0;
    
    // Nyt iteroidaan vaan jokaisen x-koordinaatin yli ja piirretään
    // piste oikealle korkeudelle.
    
    for(x ; x <= x1 ; x++) {
        if(steep) {
            putPixel(surface, y, x, color);
        }
        else {
            putPixel(surface, x, y, color);
        }
        error = error - deltay;
        if(error < 0) {
            y = y + ystep;
            error = error + deltax;
        }
    }
}

void drawCircle(SDL_Surface* surface, float x, float y, float r, Uint32 color) {
    
    // Piirtää ympyrän, jonka keskipiste on (x, y) ja säde r. Tarkistaa, että
    // SDL_Surface-osoitin ei ole tyhjä.
    
    // Tässä vaiheessa ympyrä on vielä tiheä kasa pisteitä, tulee paranemaan
    // jatkossa.
    
    assert(surface != NULL);
    
    int a = (int)(x+0.5);
    int b = (int)(y+0.5);
    
    int i = 0;
    
    for(i ; i < 360 ; i = i + 10) {
        putPixel(surface, a + (r*cos(i*M_PI/180)), b + (r*sin(i*M_PI/180)), color);
    }
}

void drawPolygonWireframe(SDL_Surface* surface,
        float x1, float y1,
        float x2, float y2,
        float x3, float y3) {
    
    // Funktio piirtää kolmion ääriviivat, tarkistaa, että
    // pinnan osoitin ei ole tyhjä.
    
    assert(surface != NULL);
    
    Uint32 white = 0xffffffff;
    Uint32 magenta = 0x00ff00ff;
    
    // Piirretään viivat
                
    drawLine(surface, x1, y1, x2, y2, white);
    drawLine(surface, x2, y2, x3, y3, white);
    drawLine(surface, x3, y3, x1, y1, white);

    // Piirretään verteksien kohdalle ympyrät

    drawCircle(surface, x1, y1, 5, magenta);
    drawCircle(surface, x2, y2, 5, magenta);
    drawCircle(surface, x3, y3, 5, magenta);
    
}

void drawSceneWireframe(SDL_Surface* surface, scene* scene) {
    
    // Piirtää tilan wireframe-muodossa. Tarkistaa, että argumentit
    // eivät ole tyhjiä.
    
    assert(surface != NULL && scene != NULL);
    
    if(scene->camera == NULL) {
        printf("No camera assigned! Stopping render.");
        return;
    }
    
    matrix* viewMatrix = getViewMatrix(scene->camera);
    matrix* projMatrix = scene->camera->perspectiveMatrix;
    
    matrix* world;
    matrix* camMatrix;
    matrix* fullTransform;
    
    int screenWidth = surface->w;
    int screenHeight = surface->h;
    
    object* obj = scene->objects;
    
    while(obj != NULL) {
        if(obj->mesh != NULL) {
            
            matrix* V1;
            matrix* V2;
            matrix* V3;
            
            int x1;
            int y1;
            int x2;
            int y2;
            int x3;
            int y3;
            
            // Lasketaan objektikohtainen muunnosmatriisi
            
            camMatrix = matrixMultiply(projMatrix, viewMatrix);
            world = matrixMultiply(camMatrix, obj->worldTransform);
            fullTransform = matrixMultiply(world, obj->scaleTransform);
            
            polygon* P = obj->mesh->polygons;
            
            while(P != NULL) {
                
                // Muunnetaan koordinaatit leikkausavaruuteen (clip space)
                
                V1 = matrixMultiply(fullTransform, P->verts[0]->coords);
                V2 = matrixMultiply(fullTransform, P->verts[1]->coords);
                V3 = matrixMultiply(fullTransform, P->verts[2]->coords);
                
                // Koordinaattien palauttaminen w = 1 avaruuteen,
                // ns. "Perspective divide"

                matrixMultiplyScalar(V1, 1.0/V1->values[3][0]);
                matrixMultiplyScalar(V2, 1.0/V2->values[3][0]);
                matrixMultiplyScalar(V3, 1.0/V3->values[3][0]);
                
                // Polygonien kulmapisteet ruudulla. Huom! y-koordinaatti
                // osoittaa kamerasta poispäin ja z-koordinaatti ylöspäin!
                
                x1 = screenWidth*0.5+(int)(V1->values[0][0]*screenWidth*0.5+0.5);
                y1 = screenHeight*0.5+(int)(V1->values[2][0]*screenHeight*0.5+0.5);
                x2 = screenWidth*0.5+(int)(V2->values[0][0]*screenWidth*0.5+0.5);
                y2 = screenHeight*0.5+(int)(V2->values[2][0]*screenHeight*0.5+0.5);
                x3 = screenWidth*0.5+(int)(V3->values[0][0]*screenWidth*0.5+0.5);
                y3 = screenHeight*0.5+(int)(V3->values[2][0]*screenHeight*0.5+0.5);
                
                drawPolygonWireframe(surface, 
                        x1, y1,
                        x2, y2,
                        x3, y3);

                P = P->next;
                
                // Poistetaan turhat matriisit
                
                deleteMatrix(V1);
                deleteMatrix(V2);
                deleteMatrix(V3);
            }
            
            deleteMatrix(camMatrix);
            deleteMatrix(world);
            deleteMatrix(fullTransform);
        }
        obj = obj->next;
    }   
}
