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
    
    printf("Starting md2 import\n");
    printf("magic: %d\nversion: %d\n",header->magic, header->version);
    printf("Number of vertices: %d\n", header->numVertices);
    printf("Number of triangles: %d\n", header->numTriangles);
    
    mesh* mesh = sceneNewMesh(scene);
    
    // Muodostetaan malli ensimmäisen animaatiokehyksen mukaiseksi
    
    md2_frame* frame = malloc(sizeof(md2_frame) + sizeof(md2_vertex)*(header->numVertices-1));
    
    fseek(f, header->offsetFrames, SEEK_SET);
    
    fread(frame, sizeof(md2_frame) + sizeof(md2_vertex)*(header->numVertices-1), 1, f);
    
    printf("Frame scale: x=%f, y=%f, z=%f\n", frame->scale[0], frame->scale[1], frame->scale[2]);
    printf("Frame translate: x=%f, y=%f, z=%f\n", frame->translate[0], frame->translate[1], frame->translate[2]);
    
    // Lisätään verteksit malliin
    
    short added[header->numVertices];
    
    int i = 0;
    
    for(i ; i < header->numVertices ; i++) {
        added[i] = 0;
    }
    
    md2_triangle* tri = malloc(sizeof(md2_triangle));    
    fseek(f, header->offsetTriangles, SEEK_SET);
    
    vertex* addedVertices[3];
    
    i = 0;
    int j = 0;
    
    for(i ; i < header->numTriangles-1 ; i++) {
        fread(tri, sizeof(md2_triangle), 1, f);
        for(j ; j < 3 ; j++) {
            
            
            if(added[tri->vertexIndices[j]] == 0) {
                added[tri->vertexIndices[j]] = 1;
                addedVertices[j] = meshNewVertex(mesh,
                        frame->vertices[tri->vertexIndices[j]].vertex[0]*frame->scale[0]+frame->translate[0],
                        frame->vertices[tri->vertexIndices[j]].vertex[1]*frame->scale[1]+frame->translate[1],
                        frame->vertices[tri->vertexIndices[j]].vertex[2]*frame->scale[2]+frame->translate[2]);
            }
            else {
                matrix* coords = newMatrix(4, 1);
                coords->values[0][0] = frame->vertices[tri->vertexIndices[j]].vertex[0]*frame->scale[0]+frame->translate[0];
                coords->values[1][0] = frame->vertices[tri->vertexIndices[j]].vertex[1]*frame->scale[1]+frame->translate[1];
                coords->values[2][0] = frame->vertices[tri->vertexIndices[j]].vertex[2]*frame->scale[2]+frame->translate[2];
                coords->values[3][0] = 1;
                
                vertex* compare = mesh->vertices;
                
                while(matrixNorm(compare->coords, coords) != 0) {
                    compare = compare->next;
                }
                addedVertices[j] = compare;
            }
        }
        
        meshNewPolygon(mesh, addedVertices[0], addedVertices[1], addedVertices[2]);
        printf("Added polygon number %d\nVertex 1 coords: x=%f, y=%f, z=%f\nVertex 2 coords: x=%f, y=%f, z=%f\nVertex 3 coords: x=%f, y=%f, z=%f\n",
                i,
                addedVertices[0]->coords->values[0][0],
                addedVertices[0]->coords->values[1][0],
                addedVertices[0]->coords->values[2][0],
                addedVertices[1]->coords->values[0][0],
                addedVertices[1]->coords->values[1][0],
                addedVertices[1]->coords->values[2][0],
                addedVertices[2]->coords->values[0][0],
                addedVertices[2]->coords->values[1][0],
                addedVertices[2]->coords->values[2][0]);
        j = 0;
    }
    
    closeModel(model);
    free(frame);
    free(tri);
    
    printf("md2 import done.\n");
    return mesh;
}
