/* 
 * File:   render.h
 * Author: topias
 *
 * Created on May 28, 2013, 12:31 PM
 */

#ifndef SCENE_H
#define	SCENE_H

#include "matrix.h"
#include "mesh.h"

// Forward declaration of mesh
struct mesh;

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

object* sceneNewObject(scene* scene);
void deleteObject();

void objectScale(object* O, float xScale, float yScale, float zScale);
void objectRotate(object* O, float xRotation, float yRotation, float zRotation);
void objectTranslate(object* O, float x, float y, float z);

camera* sceneNewCamera(scene* scene, object* obj);
void deleteCamera(camera* cam);
matrix* getViewMatrix(camera* cam);

scene* newScene();
void deleteScene(scene* scene);

mesh* sceneNewMesh(scene* scene);
matrix* calculateCameraMatrix(scene* scene);

void addObject(scene* scene, object* obj);
void addMesh(scene* scene, mesh* M);

int cameraInFrontOfPolygon(camera* camera, polygon* P);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SCENE_H */

