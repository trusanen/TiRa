#include "scene.h"
#include "matrix.h"
#include "mesh.h"
#include <assert.h>
#include <math.h>
#include "primitives.h"

object* sceneNewObject(scene* scene) {
    
    // Luo uuden objektin tilaan, tarkistaa, että
    // tila ei ole tyhjä osoitin.
    
    assert(scene != NULL);
    
    object* obj = malloc(sizeof(object));
    
    obj->worldTransform = identityMatrix(4);
    obj->scaleTransform = identityMatrix(4);
    obj->mesh = NULL;
    obj->next = NULL;
    obj->prev = NULL;
    
    addObject(scene, obj);
    
    return obj;
}

void deleteObject(object* obj) {
    
    // Poistaa objektin, tarkistaa, että annettu osoitin ei ole
    // tyhjä.
    
    assert(obj != NULL);
    
    object* objNext = obj->next;
    object* objPrev = obj->prev;
    
    if(objNext != NULL) {
        objNext->prev = objPrev;
    }
    if(objPrev != NULL) {
        objPrev->next = objNext;
    }
    
    deleteMatrix(obj->worldTransform);
    deleteMatrix(obj->scaleTransform);
    
    free(obj);
}

void objectTranslate(object* obj, float x, float y, float z) {
    
    // Siirtää mallia M x-, y- ja z-akselien suuntaisesti. Tarkistaa, että
    // malli ei ole tyhjä.
    
    assert(obj != NULL);
    
    // Siirtomatriisi on seuraavanlainen:
    //
    // [ 1 0 0 x ]
    // [ 0 1 0 y ]
    // [ 0 0 1 z ]
    // [ 0 0 0 1 ]
    //
    // Kun tällä kerrotaan koordinaattimatriisia, saadaan
    //
    // [ x0 + x ]
    // [ y0 + y ]
    // [ z0 + z ]
    // [   1    ]
    //
    // eli mallia on siirretty x:n, y:n ja z:n verran akseleita pitkin.
    
    // Asetetaan mallin siirtomatriisiin oikeat arvot
    
    obj->worldTransform->values[0][3] = x;
    obj->worldTransform->values[1][3] = y;
    obj->worldTransform->values[2][3] = z;
}

void objectRotate(object* obj, float xRotation, float yRotation, float zRotation) {
    
    // Kääntää mallia globaalin avaruuden (world space) standardikannan
    // x-, y- ja z-akselien ympäri.
    
    // Kääntö x-akselin ympäri voidaan määritellä matriisilla
    
    //      [ 1   0       0    0 ]
    // Rx = [ 0 cos(t) -sin(t) 0 ]
    //      [ 0 sin(t)  cos(t) 0 ]
    //      [ 0   0       0    1 ]
    
    // Samanlainen matriisi voidaan määritellä myös käännölle y- ja 
    // z-akselien ympäri. Kun nämä matriisit kerrotaan keskenään, saadaan
    // kokonaiskääntö R = Rz * Ry * Rx.
    
    // Funktio asettaa vain oikeat arvot matriisimuunnoksen vastaaviin
    // kohtiin. Funktio tarkistaa, että malli ei ole tyhjä.
    
    assert(obj != NULL);
    
    obj->worldTransform->values[0][0] = cos(yRotation)*cos(zRotation);
    obj->worldTransform->values[0][1] = sin(xRotation)*sin(yRotation)*cos(zRotation)
            - cos(xRotation)*sin(zRotation);
    obj->worldTransform->values[0][2] = cos(xRotation)*sin(yRotation)*cos(zRotation)
            + sin(xRotation)*sin(zRotation);
    obj->worldTransform->values[1][0] = cos(yRotation)*sin(zRotation);
    obj->worldTransform->values[1][1] = cos(xRotation)*cos(zRotation)
            + sin(xRotation)*sin(yRotation)*sin(zRotation);
    obj->worldTransform->values[1][2] = -sin(xRotation)*cos(zRotation)
            + cos(xRotation)*sin(yRotation)*sin(zRotation);
    obj->worldTransform->values[2][0] = -sin(yRotation);
    obj->worldTransform->values[2][1] = sin(xRotation)*cos(yRotation);
    obj->worldTransform->values[2][2] = cos(xRotation)*cos(yRotation);
}

camera* sceneNewCamera(scene* scene, object* obj) {
    
    // Luo uuden kameran ja asettaa sen paikaksi objektin obj paikan.
    // Tarkistaa, että argumentit eivät ole tyhjiä osoittimia.
    
    assert(scene != NULL && obj != NULL);
    
    camera* cam = malloc(sizeof(camera));
    
    cam->cameraObj = obj;
    cam->perspectiveMatrix = identityMatrix(4);
    
    if(scene->camera != NULL) {
        deleteCamera(scene->camera);
    }
    
    scene->camera = cam;
    
    return cam;
}

void deleteCamera(camera* cam) {
    
    // Poistaa kameran, tarkistaa, että osoitin ei ole tyhjä.
    
    assert(cam != NULL);
    
    deleteMatrix(cam->perspectiveMatrix);
    
    free(cam);
}

scene* newScene() {
    
    // Luo uuden tilan. Asettaa tilaan pisteeseen (0,0,0) yksikkökuution
    // ja kameran pisteeseen(3, -3, 3), jota se kääntää pi/4 radiaania
    // z-akselin ympäri ja pi/4 astetta x-akselin ympäri.
    
    scene* scene = malloc(sizeof(scene));
    
    scene->meshes = NULL;
    scene->objects = NULL;
    scene->camera = NULL;
    
    object* unitCube = sceneNewObject(scene);
    unitCube->mesh = newUnitCube();
    
    object* cam = sceneNewObject(scene);
    
    objectTranslate(cam, 3, -3, 3);
    objectRotate(cam, M_PI/4, 0, M_PI/4);
    
    sceneNewCamera(scene, cam);
    
    return scene;
}

void addObject(scene* scene, object* obj) {
    
    // Lisää objektin tilaan, tarkistaa, että osoittimet eivät ole
    // tyhjiä.
    
    assert(scene != NULL && obj != NULL);
    
    object* objects = scene->objects;
    
    if(objects != NULL) {
        objects->prev = obj;
        obj->next = objects;
    }
    
    scene->objects = obj;
}



matrix* getViewMatrix(camera* cam) {
    
    // Laskee annetun objektin kuvakulmamatriisin (view matrix).
    // Kuvamatriisi on oikeastaan vain kameraksi valitun pisteen
    // (silmäpiste, "eye coordinates") maailmamuunnoksen (world transform)
    // käänteismatriisi. Se määritellään seuraavasti:
    
    // viewTransform = [ Sinv 0 ] * [ Rt -Rt*T ]
    //                 [   0  1 ]   [ 0     1  ],
    
    // missä Sinv on kameran skaalausmatriin käänteismatriisi,
    // Rt on kameran rotaatiomatriisin transpoosi (3x3-matriisi) 
    // ja T kameran translaatiovektori (3x1-matriisi).
    
    // Tarkistaa, että annettu kamera ei ole tyhjä.
    
    assert(cam != NULL);
    
    // Allokoidaan tilaa sopiville matriiseille
    
    matrix* viewMatrix = newMatrix(4, 4);
    
    // R kameran rotaatio- ja T translaatiomatriisi.
    
    matrix* R = newMatrix(3, 3);
    matrix* T = newMatrix(3, 1);
    
    int i = 0;
    int j = 0;
    
    // Asetetaan oikeat arvot R matriisiin ja kuvakulmamatriisin
    // rotaatio-osuuteen.
    
    for(i ; i < R->rows ; i++) {
        for(j ; j < R->columns ; j++) {
            R->values[i][j] = cam->cameraObj->mesh->worldTransform->values[i][j];
            viewMatrix->values[j][i] = cam->cameraObj->mesh->worldTransform->values[i][j];
        }
        j = 0;
    }
    
    i = 0;
    
    // Asetetaan oikeat arvot translaatiovektoriin.
    
    for(i ; i < T->rows ; i++) {
        T->values[i][0] = cam->cameraObj->worldTransform->values[i][3];
    }
    
    // Lasketaan kuvakulmamatriisin translaatio-osuus.
    
    matrix* Rt = matrixTranspose(R);
    matrix* RtT = matrixMultiply(Rt, T);
    matrixMultiplyScalar(RtT, -1);
    
    i = 0;
    
    // Asetetaan kuvakulmamatriisin translaatio-osuuteen oikeat arvot.
    
    for(i ; i < T->rows ; i++) {
        viewMatrix->values[i][3] = RtT->values[i][0];
    }
    
    // Lasketaan skaalausmatriisin käänteismatriisi.
    
    matrix* Sinverse = identityMatrix(4);
    
    i = 0;
    
    for(i ; i < Sinverse->rows - 1 ; i++) {
        Sinverse->values[i][i] = 1/cam->cameraObj->scaleTransform->values[i][i];
    }
    
    // Kerrotaan skaalausmatriisilla rotaatio- ja translaatio-osuutta.
    
    matrix* viewMatrixFinal = matrixMultiply(Sinverse, viewMatrix);
    
    // Poistetaan turhaksi jääneet matriisit.
    
    deleteMatrix(viewMatrix);
    deleteMatrix(R);
    deleteMatrix(T);
    deleteMatrix(Rt);
    deleteMatrix(RtT);
    deleteMatrix(Sinverse);
    
    return viewMatrixFinal;
}

