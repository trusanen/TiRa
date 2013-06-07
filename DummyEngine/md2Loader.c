#include "md2Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

md2* loadModel(char* filepath) {
    
    // Funktio lataa MD2-formaatin mallin muistiin. Palauttaa
    // tyhjän osoittimen, jos mallin lataaminen epännistuu.
    
    md2* md2_file = malloc(sizeof(md2));
    
    FILE* f = fopen(filepath, "r");
    
    if(f == NULL) {
        printf("File loading failed!\n");
        return NULL;
    }
    
    md2_file->file = f;
    
    md2_header* header = malloc(sizeof(md2_header));
    
    fread(header, sizeof(md2_header), 1, f);
    
    md2_file->header = header;
    
    return md2_file;
}

void closeModel(md2* model) {
    
    // Funktio vapauttaa MD2-mallin muistista ja sulkee tiedoston,
    // josta dataa luetaan. Tarkistaa, että osoitin ei ole tyhjä.
    
    assert(model != NULL);
    
    fclose(model->file);
    free(model->header);
    free(model);
}

mesh* md2ToMesh(char* filepath, scene* scene) {
    
    // Funktio lataa MD2-tiedoston muistiin ja muodostaa siitä ohjelman
    // ymmärtämän mallin renderöitäväksi. Tarkistaa, että tila-osoitin
    // ei ole tyhjä.
    
    assert(scene != NULL);
    
    md2* model = loadModel(filepath);
    
    FILE* f = model->file;
    md2_header* header = model->header;
    
    fread(header, sizeof(md2_header), 1, f);
    
    mesh* mesh = sceneNewMesh(scene);
    
    // Muodostetaan malli ensimmäisen animaatiokehyksen mukaiseksi
    
    fseek(f, header->offsetFrames, SEEK_SET);
    
    closeModel(model);
}
