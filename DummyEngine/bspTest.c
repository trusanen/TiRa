#include "scene.h"
#include "bspTree.h"
#include <assert.h>
#include <math.h>
#include "primitives.h"

void bspTest() {
    
    // Tämä luokka testaa BSP-puuhun liittyviä algoritmeja.
    
    polygon* P = malloc(sizeof(polygon));
    matrix* tmp = newMatrix(4,4);
    
    // Luodaan muutama testialkio
    
    bspNode* root = createBSPNode(P, tmp);
    bspNode* new = createBSPNode(P, tmp);
    
    // Liitetään new-alkio root-alkion taakse
    
    addNodeBehind(root, new);
    
    // Tarkistetaan, että puu on oikeanlainen
    
    assert(root->behind == new);
    assert(root->front == NULL);
    assert(root->behind->front == NULL);
    assert(root->behind->behind == NULL);
    
    // Poistetaan puu
    
    deleteBSPTree(root);
    
    // Vapautetaan polygonille ja matriisille varattu muisti
    
    free(P);
    deleteMatrix(tmp);
    
    // Piirretään perustila bsp-puuta käyttäen. Asetetaan peruskuution
    // taakse taso, jonka eteen kuution pitäisi piirtyä.
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("BSP-tree test", "BSP-tree test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    object* cube = sceneNewObject(scn);
    
    cube->mesh = newUnitCube(scn);
    
    objectRotate(cube, 0, M_PI, 0);
    objectTranslate(cube, 0, -5, 0);
    
/*
    object* grid = sceneNewObject(scn);

    grid->mesh = newGrid(scn, 20, 20);
    
    objectTranslate(grid, -10, -10, 2);
    //objectRotate(grid, M_PI/4, 0, M_PI/4);
*/
    
    drawBSPTree(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "BSPTreeTest.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);   
}