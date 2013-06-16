#include <assert.h>
#include "../Header files/md2Loader.h"

void md2ImportTest() {
    
    // Tämä tiedosto testaa MD2-tiedostojen lataamiseen
    // liittyviä funktioita.
    
    // Tarkistetaan, että mallin lataaminen muistiin toimii.
    
    md2* model = loadModel("testi.md2");
    
    assert(model != NULL);
    
    // Tarkistetaan, että header-osan tiedot ovat
    // kunnossa. Magic- ja version-attribuutit ovat
    // tarkistus arvoja, joilla on aina samat arvot
    // korruptoitumattomassa MD2-tiedostossa.
    
    assert(model->header->magic == 844121161);
    assert(model->header->version == 8);
    
    // Tarkistetaan, että tiedoston sulkeminen onnistuu.
    
    closeModel(model);
    
    // Tarkistetaan, että tiedoston muuttaminen ja piirtäminen onnistuu
    
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_EVERYTHING);
    
    SDL_WM_SetCaption("MD2 import test", "MD2 import test");
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    
    scene* scn = newScene();
    
    // Poistetaan yksikkökuutio
    
    deleteObject(scn->objects->next);
    
    // Lisätään .md2-tiedostosta luettu malli
    
    object* importedObject = sceneNewObject(scn);    
    mesh* mesh = md2ToMesh("testi.md2", scn);    
    importedObject->mesh = mesh;
    
    // Skaalataan objektia hieman pienemmäksi
    
    objectScale(importedObject, 0.3, 0.3, 0.3);
    
    // Piirretään
    
    drawSceneWireframe(screen, scn);
    
    SDL_Flip(screen);
    
    SDL_Delay(2000);
    
    SDL_SaveBMP(screen, "md2Test.bmp");
    
    SDL_Quit();
    
    deleteScene(scn);
}
