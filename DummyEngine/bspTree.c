#include "Header files/bspTree.h"
#include "Header files/scene.h"
#include <stdlib.h>
#include <assert.h>
#include "Header files/mathematics.h"

bspNode* createBSPNode(polygon* P, matrix* fullTransform) {
    
    // Funktio luo BSP-puun alkion ja asettaa sen
    // avaimeksi polygonin osoittimen. Tarkistaa, että
    // osoitin ei ole tyhjä.
    
    assert(P != NULL && fullTransform != NULL);
    
    bspNode* node = malloc(sizeof(bspNode));
    
    node->polygon = P;
    node->fullTransform = fullTransform;
    
    node->behind = NULL;
    node->front = NULL;
    
    return node;
}

bspNode* createBSPTree(scene* scene) {
    
    // Funktio luo tilasta BSP-puun, jonka juureksi valitaan
    // ensimmäisen mallin ensimmäinen polygoni. Samalla
    // lasketaan polygonien ikkunakoordinaatit. Funktio
    // tarkistaa, että tilan osoitin ei ole tyhjä.
    
    assert(scene != NULL);
    
    // Lasketaan kameramatriisi
    
    matrix* camMatrix = calculateCameraMatrix(scene);
    
    matrix* world;
    matrix* fullTransform;
    
    // Käydään läpi tilan kaikki objektit ja laitetaan kaikki polygonit
    // aluksi yhteen listaan.
    
    object* obj = scene->objects;
    mesh* M;
    polygon* P;
    
    bspNode* root = NULL;
    bspNode* node;
    bspNode* prevNode = NULL;
    
    while(obj != NULL) {
        M = obj->mesh;
        
        if(M != NULL) {
            
            // Lasketaan objektikohtainen muunnosmatriisi
            
            world = matrixMultiply(obj->worldTransform, obj->scaleTransform);
            fullTransform = matrixMultiply(camMatrix, world);
            
            P = M->polygons;
            while(P != NULL) {
                
                calculateWorldCoordinates(P, world);
                
                // Luodaan alkio BSP-puuhun, jos polygoni osoittaa
                // kameraan päin.

                node = createBSPNode(P, fullTransform);

                if(root == NULL) {
                    root = node;
                }

                if(prevNode != NULL) {
                    prevNode->front = node;
                }
                prevNode = node;
                
                P = P->next;
            }
        }
        obj = obj->next;
    }
    
    // Asetetaan alkiot oikeaan järjestykseen rekursiivisella
    // kutsulla
    
    resolveBSPTree(root);
    return root;
}

void deleteBSPTree(bspNode* root) {
    
    // Poistaa BSP-puun rekursiivisesti.
    
    if(root == NULL) {
        return;
    }
    
    deleteBSPTree(root->behind);
    deleteBSPTree(root->front);
    free(root);
}

void resolveBSPTree(bspNode* root) {
    
    // Ratkaisee BSP-puun tutkimalla annetun juuren kaikki edessä
    // olevat polygonit ja siirtämällä ne juuren taakse tarvittaessa.
    // Tarkistaa, että argumenttina annettu osoitin ei ole tyhjä.
    
    if(root == NULL) {
        return;
    }
    
    bspNode* prev = root;
    bspNode* next = root->front;
    
    while(next != NULL) {
        if(!isInFrontOfPolygon(next->polygon, root->polygon)) {
            
            prev->front = next->front;
            
            addNodeBehind(root, next);
            
            next = prev->front;
        }
        else {
            prev = next;
            next = next->front;
        }
    }
    
    resolveBSPTree(root->behind);
    resolveBSPTree(root->front);
}

void addNodeBehind(bspNode* front, bspNode* behind) {
    
    // Lisää behind-alkion front-alkion taakse, tarkistaa, että
    // osoittimet eivät ole tyhjiä.
    
    assert(behind != NULL && front != NULL);
    
    if(front->behind == NULL) {
        front->behind = behind;
        behind->front = NULL;
    }
    else {
        behind->front = front->behind;
        front->behind = behind;
    }
}

void travelBSPTree(bspNode* root, scene* scene, SDL_Surface* surface) {
    
    // Käy rekursiivisesti BSP-puun läpi sisäjärjestyksessä ja piirtää
    // kaikki polygonit. Funktio tarkistaa, että annettu osoitin ei ole tyhjä.
    
    if(root == NULL) {
        return;
    }
    
    // Jos kamera on polygonin edessä, piirretään ensin polygonit, jotka
    // ovat tutkittavan polygonin takana. Jos taas kamera on tutkittavan
    // polygonin takana, piirretään edessä olevat polygonit ensin.
    
    if(cameraInFrontOfPolygon(scene->camera, root->polygon)) {
        
        travelBSPTree(root->behind, scene, surface);

        // Lasketaan polygonin normalisoidut koordinaatit

        calculateNormalizedDeviceCoordinates(root->polygon, root->fullTransform);

        // Piirretään polygoni

        drawPolygonSolid(surface, root->polygon);

        travelBSPTree(root->front, scene, surface);
    }
    else {
        travelBSPTree(root->front, scene, surface);

        // Lasketaan polygonin normalisoidut koordinaatit

        calculateNormalizedDeviceCoordinates(root->polygon, root->fullTransform);

        // Piirretään polygoni

        drawPolygonSolid(surface, root->polygon);

        travelBSPTree(root->behind, scene, surface);
    }
}