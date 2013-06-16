/* 
 * File:   bspTree.h
 * Author: topias
 *
 * Created on June 11, 2013, 1:49 PM
 */

#ifndef BSPTREE_H
#define	BSPTREE_H

#include "scene.h"

typedef struct bspNode_t {
    polygon* polygon;
    matrix* fullTransform;
    struct bspNode_t* front;
    struct bspNode_t* behind;
} bspNode;

bspNode* createBSPNode(polygon* P, matrix* fullTransform);
void addNodeFront(bspNode* behind, bspNode* front);
void addNodeBehind(bspNode* behind, bspNode* front);
bspNode* createBSPTree(scene* scene);
void resolveBSPTree(bspNode* root);
void travelBSPTree(bspNode* root, scene* scene, SDL_Surface* surface);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BSPTREE_H */

