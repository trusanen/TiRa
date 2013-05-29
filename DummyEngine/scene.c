#include "matrix.h"
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

void objectScale(object* obj, float xScale, float yScale, float zScale) {
    
    // Skaalaa objektia globaalin avaruuden x-, y- ja z-akseleiden suuntaisesti.
    
    // Skaalausmatriisi voidaan määritellä seuraavasti:
    
    //     [ Sx 0  0  0 ]
    // S = [ 0  Sy 0  0 ]
    //     [ 0  0  Sz 0 ]
    //     [ 0  0  0  1 ]
    
    // Funktio asettaa kertoimet oikeisiin kohtiin mallin skaalausmatriisissa.
    // Funktio tarkistaa, että annettu malli ei ole tyhjä.
    
    assert(obj != NULL);
    
    obj->scaleTransform->values[0][0] = xScale;
    obj->scaleTransform->values[1][1] = yScale;
    obj->scaleTransform->values[2][2] = zScale;
}

camera* sceneNewCamera(scene* scene, object* obj) {
    
    // Luo uuden kameran ja asettaa sen paikaksi objektin obj paikan.
    // Tarkistaa, että argumentit eivät ole tyhjiä osoittimia.
    
    assert(scene != NULL && obj != NULL);
    
    camera* cam = malloc(sizeof(camera));
    
    cam->cameraObj = obj;
    
    // Määritellään näkymän rajat
    
    float far = 50.0;
    float near = 1.0;
    float fov = M_PI/2;
    float S = 1/(tan(fov*0.5));
    
    // Lasketaan projektiomatriisi
    
    cam->perspectiveMatrix = newMatrix(4, 4);
    matrixFill(cam->perspectiveMatrix, 0);
    
    cam->perspectiveMatrix->values[0][0] = S;
    cam->perspectiveMatrix->values[2][2] = S;
    cam->perspectiveMatrix->values[1][1] = far/(far-near);
    cam->perspectiveMatrix->values[1][3] = -(far*near)/(far-near);
    cam->perspectiveMatrix->values[3][1] = 1;
    
/*
    // Määritellään näkymän rajat
    
    float Pfar = 5.0;
    float Pnear = 1.0;
    float Pright = -5.0;
    float Pleft = 5.0;
    float Ptop = 5.0;
    float Pbottom = -5.0;
    
    // Lasketaan projektiomatriisi
    
    cam->perspectiveMatrix = newMatrix(4, 4);
    matrixFill(cam->perspectiveMatrix, 0);
    
    cam->perspectiveMatrix->values[0][0] = (2*Pnear)/(Pright-Pleft);
    cam->perspectiveMatrix->values[1][1] = (2*Pnear)/(Ptop-Pbottom);
    cam->perspectiveMatrix->values[0][2] = (Pright + Pleft)/(Pright - Pleft);
    cam->perspectiveMatrix->values[1][2] = (Ptop + Pbottom)/(Ptop - Pbottom);
    cam->perspectiveMatrix->values[2][2] = -1*(Pfar+Pnear)/(Pfar-Pnear);
    cam->perspectiveMatrix->values[3][2] = -1;
    cam->perspectiveMatrix->values[2][3] = (-2*Pfar*Pnear)/(Pfar-Pnear);
*/
    
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
    unitCube->mesh = newUnitCube(scene);
    
    objectScale(unitCube, 5, 1, 1);
    objectRotate(unitCube, 0, 0, M_PI/2);
    objectTranslate(unitCube, 3, -3, 3);
    
    object* cam = sceneNewObject(scene);
    
    objectTranslate(cam, 10, -10, 10);
    objectRotate(cam, -M_PI/4, 0, M_PI/4);
    
    sceneNewCamera(scene, cam);
    
    return scene;
}

void deleteScene(scene* scene) {
    
    // Poistaa tilan poistamalla kaikki sen mallit ja objektit
    // sekä kameran. Tarkistaa, että annettu osoitin ei ole tyhjä.
    
    assert(scene != NULL);
    
    mesh* M = scene->meshes;
    
    while(M != NULL) {
        deleteMesh(M);
        M = M->next;
    }
    
    object* obj = scene->objects;
    
    while(obj != NULL) {
        deleteObject(obj);
        obj = obj->next;
    }
    
    deleteCamera(scene->camera);
}

mesh* sceneNewMesh(scene* scene) {
    
    // Luo uuden 3D-mallin, joka on aluksi tyhjä. Malli koostuu polygoneista,
    // jotka tallennetaan yksisuuntaisena linkitettynä listana.
    
    mesh* M = malloc(sizeof(mesh));
    
    M->vertices = NULL;
    M->polygons = NULL;
    
    M->next = NULL;
    M->prev = NULL;
    
    addMesh(scene, M);
    
    return M;
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

void addMesh(scene* scene, mesh* M) {
    
    // Lisää mallin tilaan, tarkistaa, että osoittimet eivät ole
    // tyhjiä.
    
    assert(scene != NULL && M != NULL);
    
    mesh* meshes = scene->meshes;
    
    if(meshes != NULL) {
        meshes->prev = M;
        M->next = meshes;
    }
    
    scene->meshes = M;
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
    
    matrix* viewMatrix = identityMatrix(4);
    
    // R kameran rotaatio- ja T translaatiomatriisi.
    
    matrix* R = newMatrix(3, 3);
    matrix* T = newMatrix(3, 1);
    
    int i = 0;
    int j = 0;
    
    // Asetetaan oikeat arvot R matriisiin ja kuvakulmamatriisin
    // rotaatio-osuuteen.
    
    for(i ; i < R->rows ; i++) {
        for(j ; j < R->columns ; j++) {
            R->values[i][j] = cam->cameraObj->worldTransform->values[i][j];
            viewMatrix->values[j][i] = cam->cameraObj->worldTransform->values[i][j];
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

