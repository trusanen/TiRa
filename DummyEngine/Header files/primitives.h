/* 
 * File:   primitives.h
 * Author: topias
 *
 * Created on May 28, 2013, 11:30 AM
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

#include "scene.h"

mesh* newUnitCube(scene* scene);
mesh* newGrid(scene* scene, int x, int y);
mesh* newCone(scene* scene, int vertices, float height);

#ifdef	__cplusplus
extern "C" {
#endif

    


#ifdef	__cplusplus
}
#endif

#endif	/* PRIMITIVES_H */

