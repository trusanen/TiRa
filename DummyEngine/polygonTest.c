#include "matrix.h"
#include "scene.h"
#include "draw.h"
#include <assert.h>

void polygonTest() {
    
    // Tällä testataan polygoneihin liittyviä funktioita.
    
    assert(1.9 < 2);
    assert(1.9999 < 2);
    
    scene* scn = newScene();
    
    object* obj= scn->objects->next;
    mesh* unitCube = obj->mesh;
    
    // Valitaan toinen päällimmäisistä polygoneista
    
    polygon* top2 = unitCube->polygons->next->next;
    
    // Lasketaan normalisoidut koordinaatit
    
    matrix* camMatrix;
    matrix* world;
    matrix* fullTransform;
    
    matrix* viewMatrix = getViewMatrix(scn->camera);
    matrix* projMatrix = scn->camera->perspectiveMatrix;
    
    camMatrix = matrixMultiply(projMatrix, viewMatrix);
    
    world = matrixMultiply(camMatrix, obj->worldTransform);
    fullTransform = matrixMultiply(world, obj->scaleTransform);
    
    transformPolygon(top2, fullTransform);
    
    // Lasketaan ikkunakoordinaatit
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    calculateWindowCoordinates(screen, top2);
    
    boundingBox* bb = calculateBoundingBox(top2);
    
    assert(bb->xmin - top2->verts[0]->window->values[0][0] == 0);
    assert(bb->ymin - top2->verts[0]->window->values[2][0] == 0);
    assert(bb->xmax - top2->verts[2]->window->values[0][0] == 0);
    assert(bb->ymax - top2->verts[1]->window->values[2][0] == 0);
    
    SDL_Quit();
    
    free(bb);
    
    deleteMatrix(viewMatrix);
    deleteMatrix(projMatrix);
    deleteMatrix(camMatrix);
    deleteMatrix(world);
    deleteMatrix(fullTransform);
}
