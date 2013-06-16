/* 
 * File:   md2Loader.h
 * Author: topias
 *
 * Created on June 7, 2013, 12:46 PM
 */

#ifndef MD2LOADER_H
#define	MD2LOADER_H

#include <stdio.h>
#include "scene.h"

typedef struct {
    int magic;
    int version;
    int skinWidth;
    int skinHeight;
    int frameSize;
    int numSkins;
    int numVertices;
    int numTexCoords;
    int numTriangles;
    int numGlCommands;
    int numFrames;
    int offsetSkins;
    int offsetTexCoords;
    int offsetTriangles;
    int offsetFrames;
    int offsetGlCommands;
    int offsetEnd;
} md2_header;

typedef struct {
    char vertex[3]; // Käytetään char, koska verteksit ovat yhden tavun kokoisia
    char lightNormalIndex;
} md2_vertex;

typedef struct {
    float scale[3];
    float translate[3];
    char name[16];
    md2_vertex vertices[1];
} md2_frame;

typedef struct {
    short vertexIndices[3];
    short textureIndices[3];
} md2_triangle;

typedef struct {
    FILE* file;
    md2_header* header;
} md2;

md2* loadModel(char* filepath);
void closeModel(md2* model);

mesh* md2ToMesh(char* filepath, scene* scene);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MD2LOADER_H */

