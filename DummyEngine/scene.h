/* 
 * File:   render.h
 * Author: topias
 *
 * Created on May 28, 2013, 12:31 PM
 */

#ifndef RENDER_H
#define	RENDER_H

#include "matrix.h"
#include "mesh.h"

typedef struct object_t {
    matrix* worldTransform;
    matrix* scaleTransform;
    mesh* mesh;
    struct object_t* next;
    struct object_t* prev;
} object;

typedef struct {
    matrix* perspectiveMatrix;
    object* cameraObj;
} camera;

typedef struct {
    object* objects;
    mesh* meshes;
    camera* camera;
} scene;

object* newObject();
void deleteObject();

void objectScale(object* O, float xScale, float yScale, float zScale);
void objectRotate(object* O, float xRotation, float yRotation, float zRotation);
void objectTranslate(object* O, float x, float y, float z);

camera* sceneNewCamera(scene* scene, object* obj);
void deleteCamera(camera* cam);
matrix* getViewMatrix(camera* cam);

scene* newScene();
void deleteScene();

void addObject(scene* scene, object* obj);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RENDER_H */

