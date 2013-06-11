/* 
 * File:   bspTree.h
 * Author: topias
 *
 * Created on June 11, 2013, 1:49 PM
 */

#ifndef BSPTREE_H
#define	BSPTREE_H

typedef struct bspNode_t {
    polygon* P;
    bspNode_t* front;
    bspNode_t* behind;
} bspNode;

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BSPTREE_H */

