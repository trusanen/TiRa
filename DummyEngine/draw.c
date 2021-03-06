#include "Header files/draw.h"
#include "Header files/scene.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "Header files/bspTree.h"

void putPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    
    // Piirtää pikselin näytölle, (0, 0) on ruudun vasen alakulma.
    
    Uint32* pixels = (Uint32*)surface->pixels;
    
    if(x >= 0 && y >= 0 && x < surface->w && y < surface->h) {
        pixels[((surface->h - y) * surface->w) + x] = color;
    }
    
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

void drawPolygonWireframe(SDL_Surface* surface, polygon* P) {
    
    // Funktio piirtää polygonin ääriviivat, tarkistaa, että
    // osoittimet eivät ole tyhjiä.
    
    assert(surface != NULL && P != NULL);
    
    Uint32 white = 0xffffffff;
    Uint32 magenta = 0x00ff00ff;
    
    calculateWindowCoordinates(surface, P);
    
    float x1 = P->verts[0]->window->values[0][0];
    float y1 = P->verts[0]->window->values[2][0];
    float x2 = P->verts[1]->window->values[0][0];
    float y2 = P->verts[1]->window->values[2][0];
    float x3 = P->verts[2]->window->values[0][0];
    float y3 = P->verts[2]->window->values[2][0];
    
    // Piirretään viivat
                
    drawLine(surface, x1, y1, x2, y2, white);
    drawLine(surface, x2, y2, x3, y3, white);
    drawLine(surface, x3, y3, x1, y1, white);

    // Piirretään verteksien kohdalle ympyrät

    drawCircle(surface, x1, y1, 5, magenta);
    drawCircle(surface, x2, y2, 5, magenta);
    drawCircle(surface, x3, y3, 5, magenta);
    
}

int isInsidePolygon(int x, int y, polygon* P) {
    
    // Funktio tarkistaa, winding numbers-menetelmää käyttäen,
    // onko annettu piste polygonin P sisällä. Funktio tarkistaa,
    // että polygonin osoitin ei ole tyhjä. Funktio myös vaatii 
    // sen, että P:n ikkunakoordinaatit on laskettu.
    
    assert(P != NULL);
    assert(P->verts[0]->window != NULL);
    
    // Siirretään polygonin koordinaatit niin, että origoksi tulee
    // piste (x, y)
    
    float xs[] = {P->verts[0]->window->values[0][0] - x, 
    P->verts[1]->window->values[0][0] - x,
    P->verts[2]->window->values[0][0] - x,
    P->verts[0]->window->values[0][0] - x
    };
    
    float ys[] = {P->verts[0]->window->values[2][0] - y, 
    P->verts[1]->window->values[2][0] - y,
    P->verts[2]->window->values[2][0] - y,
    P->verts[0]->window->values[2][0] - y
    };
    
    int windingNumber = 0;
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        
        // Tutkitaan, leikkaako viiva (v[i] -> v[i+1]) positiivisen x-akselin
        
        if(ys[i]*ys[i+1] < 0) {
            
            float isect = xs[i] + (ys[i]*(xs[i+1]-xs[i]))/(ys[i]-ys[i+1]);
            
            if(isect > 0) {
                
                // Jos leikkaa, kasvatetaan windingNumberia, jos viiva
                // kulkee ylhäältä alas ja pienennetään, jos alhaalta ylös.
                
                if(ys[i] > 0) {
                    windingNumber++;
                }
                else {
                    windingNumber--;
                }
            }
        }
    }
    
    // Jos piste on polygonin sisällä, saa windingNumber nollasta
    // poikkeavan arvon, jos taas ulkopuolella, windingNumber on nolla.
    
    return windingNumber;
}

void calculateWindowCoordinates(SDL_Surface* surface, polygon* P) {
    
    // Laskee polygonin vertekseille niiden ikkunakoordinaatit
    // eli sijainnin ruudulla. Tarkistaa, että osoittimet eivät
    // ole tyhjiä. Funktio olettaa, että polygonin normalisoidut
    // koordinaatit ovat laskettu.
    
    assert(surface != NULL && P != NULL);
    assert(P->verts[0]->NDC != NULL);
    
    int screenWidth = surface->w;
    int screenHeight = surface->h;
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        if(P->verts[i]->window == NULL) {
            P->verts[i]->window = newMatrix(4, 1);
        }
        
        P->verts[i]->window->values[0][0] = screenWidth * 0.5
                + P->verts[i]->NDC->values[0][0]*screenWidth*0.5;
        P->verts[i]->window->values[1][0] = P->verts[i]->NDC->values[1][0];
        P->verts[i]->window->values[2][0] = screenHeight * 0.5
                + P->verts[i]->NDC->values[2][0]*screenHeight*0.5;
        P->verts[i]->window->values[3][0] = 1;
    }
}

boundingBox* calculateBoundingBox(polygon* P) {
    
    // Laskee pienimmän neliön, joka sisältää polygonin P
    // Tarkistaa, että osoitin ei ole tyhjä.
    
    assert(P != NULL);
    
    boundingBox* bb = malloc(sizeof(boundingBox));
    
    bb->xmin = P->verts[0]->window->values[0][0];
    bb->xmax = P->verts[0]->window->values[0][0];
    bb->ymin = P->verts[0]->window->values[2][0];
    bb->ymax = P->verts[0]->window->values[2][0];
    
    int i = 0;
    
    for(i ; i < 3 ; i++) {
        
        if(bb->xmax < P->verts[i]->window->values[0][0]) {
            bb->xmax = P->verts[i]->window->values[0][0];
        }
        if(bb->xmin > P->verts[i]->window->values[0][0]) {
            bb->xmin = P->verts[i]->window->values[0][0];
        }
        if(bb->ymax < P->verts[i]->window->values[2][0]) {
            bb->ymax = P->verts[i]->window->values[2][0];
        }
        if(bb->ymin > P->verts[i]->window->values[2][0]) {
            bb->ymin = P->verts[i]->window->values[2][0];
        }
    }
    
    return bb;
}

void drawPolygonSolid(SDL_Surface* surface, polygon* P) {
    
    // Piirtää polygonin umpinaisena. Funktio olettaa, että
    // polygonin normalisoidut koordinaatit ovat laskettu. 
    // Tarkistaa, että annetut osoittimet eivät ole tyhjiä.
    
    assert(surface != NULL && P != NULL);
    assert(P->verts[0]->NDC != NULL);
    
    calculateWindowCoordinates(surface, P);
    
    // Lasketaan pienin neliö, joka sisältää polygonin.
    
    boundingBox* bb = calculateBoundingBox(P);
    
    // Väritetään jokainen pikseli, joka sisältyy polygoniin.
    
    int i = ceil(bb->xmin);
    int j = ceil(bb->ymin);
    
    for(i ; i <= floor(bb->xmax) ; i++) {
        for(j ; j <= floor(bb->ymax) ; j++) {
            if(isInsidePolygon(i, j, P)) {
                putPixel(surface, i, j, P->color);
            }
        }
        j = ceil(bb->ymin);
    }
    
    free(bb);
}

int doBackfaceCulling(camera* cam, polygon* P) {
    
    // Tutkii, osoittaako polygoni kameraan päin. Funktio vaatii,
    // että polygonin verteksien maailmakoordinaatit on laskettu.
    // Tarkistaa, etteivät osoittimet ole tyhjiä.
    
    assert(cam != NULL && P != NULL);
    assert(P->verts[0]->world != NULL);
    
    // Luodaan vektori, joka osoittaa kamerasta tutkittavan
    // polygonin ensimmäiseen verteksiin.
    
    matrix* camToPolygon = newMatrix(4,1);
    
    camToPolygon->values[0][0] = P->verts[0]->world->values[0][0] - 
            cam->cameraObj->worldTransform->values[0][3];
    camToPolygon->values[1][0] = P->verts[0]->world->values[1][0] - 
            cam->cameraObj->worldTransform->values[1][3];
    camToPolygon->values[2][0] = P->verts[0]->world->values[2][0] - 
            cam->cameraObj->worldTransform->values[2][3];
    camToPolygon->values[3][0] = 1;
    
    // Lasketaan polygonin normaali tila-avaruudessa (world space)
    
    matrix* normal = calculatePolygonWorldNormal(P);
    
    // Lasketaan kamerasta polygonin ensimmäiseen verteksiin osoittavan
    // vektorin ja muunnetun normaalivektorin sisätulo.
    
    float dotProduct = vectorDotProduct(camToPolygon, normal);
    
    deleteMatrix(camToPolygon);
    deleteMatrix(normal);
    
    // Jos sisätulo on negatiivinen, on vektorien välinen kulma
    // yli 90 astetta jompaan kumpaan suuntaan, joten sitä ei piirretä.
    
    if(dotProduct < 0) {
        return 1;
    }
    return 0;
}

void drawSceneWireframe(SDL_Surface* surface, scene* scene) {
    
    // Piirtää tilan wireframe-muodossa. Tarkistaa, että argumentit
    // eivät ole tyhjiä.
    
    assert(surface != NULL && scene != NULL);
    
    if(scene->camera == NULL) {
        printf("No camera assigned! Stopping render.");
        return;
    }
    
    // Lasketaan kameramatriisi
    
    matrix* camMatrix = calculateCameraMatrix(scene);
    
    matrix* world;
    matrix* fullTransform;
    
    object* obj = scene->objects;
    
    while(obj != NULL) {
        if(obj->mesh != NULL) {
            
            // Lasketaan objektikohtainen muunnosmatriisi
            
            world = matrixMultiply(obj->worldTransform, obj->scaleTransform);
            fullTransform = matrixMultiply(camMatrix, world);
            
            polygon* P = obj->mesh->polygons;
            
            while(P != NULL) {
                
                // Lasketaan polygonin verteksien koordinaatit ruudulla (NDC)
                
                calculateNormalizedDeviceCoordinates(P, fullTransform);
                
                // Piirretään polygoni
                
                drawPolygonWireframe(surface, P);

                P = P->next;
            }
            
            deleteMatrix(world);
            deleteMatrix(fullTransform);
        }
        
        obj = obj->next;
    }
    
    deleteMatrix(camMatrix);
}

void drawSceneWireframeBackfaceCulling(SDL_Surface* surface, scene* scene) {
    
    // Piirtää tilan wireframe-muodossa, poistaa kaikki pinnat, jotka
    // eivät osoita kameraan päin. Tarkistaa, että argumentit
    // eivät ole tyhjiä osoittimia.
    
    assert(surface != NULL && scene != NULL);
    
    if(scene->camera == NULL) {
        printf("No camera assigned! Stopping render.");
        return;
    }
    
    // Lasketaan kameramatriisi
    
    matrix* camMatrix = calculateCameraMatrix(scene);
    
    matrix* world;
    matrix* fullTransform;
    
    object* obj = scene->objects;
    
    while(obj != NULL) {
        if(obj->mesh != NULL) {
            
            // Lasketaan objektikohtainen muunnosmatriisi
            
            world = matrixMultiply(obj->worldTransform, obj->scaleTransform);
            fullTransform = matrixMultiply(camMatrix, world);
            
            polygon* P = obj->mesh->polygons;
            
            while(P != NULL) {
                
                calculateWorldCoordinates(P, world);
                
                // Piirretään polygoni, jos se osoittaa kameraan
                // päin.
                
                if(doBackfaceCulling(scene->camera, P)) {
                    
                    // Lasketaan polygonin verteksien koordinaatit ruudulla (NDC)

                    calculateNormalizedDeviceCoordinates(P, fullTransform);

                    // Piirretään polygoni

                    drawPolygonWireframe(surface, P);
                }
                
                P = P->next;
            }
            
            deleteMatrix(world);
            deleteMatrix(fullTransform);
        }
        obj = obj->next;
    }
    
    deleteMatrix(camMatrix);
}

void drawSceneSolid(SDL_Surface* surface, scene* scene) {
    
    // Piirtää tilan solid-muodossa, poistaa kaikki pinnat, jotka
    // eivät osoita kameraan päin. Tarkistaa, että argumentit
    // eivät ole tyhjiä osoittimia.
    
    assert(surface != NULL && scene != NULL);
    
    if(scene->camera == NULL) {
        printf("No camera assigned! Stopping render.");
        return;
    }
    
    // Lasketaan kameramatriisi
    
    matrix* camMatrix = calculateCameraMatrix(scene);
    
    matrix* world;
    matrix* fullTransform;
    
    object* obj = scene->objects;
    
    while(obj != NULL) {
        if(obj->mesh != NULL) {
            
            // Lasketaan objektikohtainen muunnosmatriisi
            
            world = matrixMultiply(obj->worldTransform, obj->scaleTransform);
            fullTransform = matrixMultiply(camMatrix, world);
            
            polygon* P = obj->mesh->polygons;
            
            while(P != NULL) {
                
                calculateWorldCoordinates(P, world);
                
                // Piirretään polygoni, jos se osoittaa kameraan
                // päin.
                
                if(doBackfaceCulling(scene->camera, P)) {
                    
                    // Lasketaan polygonin verteksien koordinaatit ruudulla (NDC)

                    calculateNormalizedDeviceCoordinates(P, fullTransform);

                    // Piirretään polygoni

                    drawPolygonSolid(surface, P);
                }
                
                P = P->next;
            }
            
            deleteMatrix(world);
            deleteMatrix(fullTransform);
        }
        obj = obj->next;
    }
    
    deleteMatrix(camMatrix);
}

void drawBSPTree(SDL_Surface* surface, scene* scene) {
    
    // Piirtää tilan käyttäen BSP-puuta polygonien järjestämiseen.
    // Tarkistaa, että osoittimet eivät ole tyhjiä.
    
    assert(surface != NULL && scene != NULL);
    
    if(scene->camera == NULL) {
        printf("No camera assigned! Stopping render.");
        return;
    }
    
    // Luodaan BSP-puu ja käydään se läpi sisäjärjestyksessä.
    
    bspNode* root = createBSPTree(scene);
    
    travelBSPTree(root, scene, surface);

    deleteBSPTree(root);
}
