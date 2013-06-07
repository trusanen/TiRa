#include <assert.h>
#include "md2Loader.h"

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
}
