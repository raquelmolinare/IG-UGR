#include "auxiliar.h"
#include "camara.h"

#define PI 3.141592 //Definimos PI


Camara::Camara (Tupla3f eyeCam,Tupla3f atCam,Tupla3f upCam, int tipoCam,float leftCam, float rightCam, float bottomCam, float topCam,float nearCam ,float farCam) {
    
    if( tipoCam > 2 || tipoCam < 1){
        tipo = 1;
    }
    else
        tipo = tipoCam;

    //parámetros gluLookAt
    eye = eyeCam;
    at = atCam;
    up = upCam;

    //Parametros de la camara
    left = leftCam;
    right = rightCam;
    bottom = bottomCam;
    top = topCam;
    near = nearCam;
    far = farCam;

    //Parametros para el control del movimiento
    cteGiro = 0.2;
    anguloX = 0.0; anguloY = 0.0;
    yaw = 0.0; pitch = 0.0;

    modo = FIRSTPERSON;
    seleccionaObjeto = false;
    indiceObjeto = 0; //0 si ninguno
        
}

Camara::Camara (Tupla3f eyeCam,Tupla3f atCam, int tipoCam) {
    if( tipoCam > 2 || tipoCam < 1){
        tipo = 1;
    }
    else
        tipo = tipoCam;

    //parámetros gluLookAt
    eye = eyeCam;
    at = atCam;
    up = {0.0,1.0,0.0}; //Sentido hacia arriba

    //El volumen de visualización depende del tipo de camara
    switch (tipo) {
        case 1: //ORTOGONAL (1) 
            left = -200.0;
            right = 200.0;
            bottom = -200.0;
            top = 200.0;
            near = -200.0;
            far = 2000.0;
            break;
    
        case 2: //Perspectiva (2)
            bottom = left = -70.0;
            top = right = 70.0;
            near =50.0;
            far = 2000.0; 
            break;
    }

    cteGiro = 0.2;
    anguloX = 0.0; anguloY = 0.0;
    yaw = 0.0; pitch = 0.0;

    seleccionaObjeto = false;
    indiceObjeto = false; //0 si ninguno
        
}

//Rotar x en torno a un punto
void Camara::rotarXExaminar ( float angle ){

    
    //glRotatef( angle, 1, 0, 0 );
    
    //Rotar eye respecto a at sobre el eje x
    Tupla3f direccion = eye - at; //Obtenemos el vector director

    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));

    //Rotacion en X
    //direccion[0] = direccion[0];
    direccion[1] = (direccion[1] * cos((angle*PI)/180.0)) - (direccion[2] * sin((angle*PI)/180.0));
    direccion[2] = (direccion[1] * sin((angle*PI)/180.0)) + (direccion[2] * cos((angle*PI)/180.0));

    direccion = direccion.normalized() * modulo;

    //Aignamos
    eye = direccion + at;


}

//Rotar y en torno a un punto
void Camara::rotarYExaminar ( float angle ){

    
    //glRotatef( angle, 0 ,1, 0 );

    //Rotar eye respecto a at sobre el eje y
    Tupla3f direccion = eye - at; //Obtenemos el vector director

    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));

    //Rotacion en Y
    direccion[0] = (direccion[0] * cos((angle*PI)/180.0)) + (direccion[2] * sin((angle*PI)/180.0));
    //direccion[1] = direccion[1];
    direccion[2] = (direccion[0] * -sin((angle*PI)/180.0)) + (direccion[2] * cos((angle*PI)/180.0));

    direccion = direccion.normalized() * modulo;

    //Aignamos
    eye = direccion + at;
}

//Rotar z en torno a un punto
void Camara::rotarZExaminar ( float angle ){
    
    //glRotatef( angle, 0 ,0, 1 );

    //Rotar eye respecto a at sobre el eje z
    Tupla3f direccion = eye - at; //Obtenemos el vector director

    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));

    //Rotacion en Z
    direccion[0] = (direccion[0] * cos((angle*PI)/180.0)) - (direccion[1] * sin((angle*PI)/180.0));
    direccion[1] = (direccion[0] * sin((angle*PI)/180.0)) + (direccion[1] * cos((angle*PI)/180.0));
    //direccion[2] = direccion[2];

    direccion = direccion.normalized() * modulo;

    //Aignamos
    eye = direccion + at;
}

void Camara::rotarXFirstPerson ( float angle ){

    //Rotar at respecto a eye sobre el eje x
    Tupla3f direccion = at - eye;

    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));

    //Rotacion en X
    //direccion[0] = direccion[0];
    direccion[1] = (direccion[1] * cos((angle*PI)/180.0)) - (direccion[2] * sin((angle*PI)/180.0));
    direccion[2] = (direccion[1] * sin((angle*PI)/180.0)) + (direccion[2]* cos((angle*PI)/180.0));

    direccion = direccion.normalized() * modulo;

    at = direccion + eye;
}

void Camara::rotarYFirstPerson ( float angle ){

    //Rotar at respecto a eye sobre el eje Y
    Tupla3f direccion = at - eye;

    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));
    
    //Rotacion en Y
    direccion[0] = (direccion[0] * cos((angle*PI)/180.0)) + (direccion[2] * sin((angle*PI)/180.0));
    //direccion[1] = direccion[1];
    direccion[2] = (direccion[0]* -sin((angle*PI)/180.0)) + (direccion[2] * cos((angle*PI)/180.0));
    
    direccion = direccion.normalized() * modulo;

    at = direccion + eye;   
}

void Camara::rotarZFirstPerson ( float angle ){

    //Rotar at respecto a eye sobre el eje Z
    Tupla3f direccion = at - eye;
    
    float modulo = sqrt(pow(direccion[0],2) + pow(direccion[1],2) + pow(direccion[2],2));

    //Rotacion en Z
    direccion[0] = (direccion[0] * cos((angle*PI)/180.0)) - (direccion[2] * sin((angle*PI)/180.0));
    direccion[1] = (direccion[0] * sin((angle*PI)/180.0)) + (direccion[2] * cos((angle*PI)/180.0));
    //direccion[2] = direccion[2];

    direccion = direccion.normalized() * modulo;

    at = direccion + eye;
    
}

void Camara::mover ( float x, float y, float z ){
    eye[0] = x;
    eye[1] = y;
    eye[2] = z;
}

//Pone la camara en posicion examinar un objeto que esta en el x,y,z
void Camara::posicionarExaminar( float x, float y, float z ){
    at[0] = x;
    at[1] = y;
    at[2] = z;

    //eye[0] = x;
    eye[1] = y + 100.0;

    //eye[2] = z + 100.0;
    /*switch (tipo) {
        case 1: //ORTOGONAL (1) 
            if( eye[2] < 0 ) 
                eye[2] = z - 50.0;
            else
                eye[2] = z + 50.0;
            break;
    
        case 2: //Perspectiva (2)
            if( eye[2] < 0 ) 
                eye[2] = z - 100.0;
            else
                eye[2] = z + 100.0; 
            break;
    }*/
    
}

/**
 * @brief recalcula el valor de sus parámetros de giro en X y en Y (angleX y angleY).
 * 
 * @param x : Diferencia de xactual - xanterior
 * @param y : Diferencia de yactual - yanterior
 */
void Camara::girarExaminar( float x, float y){

    //Calculamos el angulo de giro
    //modo = EXAMINAR;
    anguloX = (float)(-cteGiro*y);
    anguloY = (float)(-cteGiro*x);

    //Realizamos el giro
    rotarYExaminar(anguloY);
    rotarXExaminar(anguloX);

}

void Camara::girarFirstPerson( float x, float y){

    //Calculamos el angulo de giro
    //modo = FIRSTPERSON;
    pitch = (-cteGiro*y);
    yaw = (-cteGiro*x);
    
    //Realizamos el giro
    rotarYFirstPerson(yaw);
    rotarXFirstPerson(pitch);
    
}

void Camara::zoom ( float factor ){

    
    left = (left * factor);
    right = (right *factor);
    top = (top * factor);
    bottom = (bottom * factor);
    
    //Para que se aplique el zoom
    setProyeccion();

}

void Camara::rotarX( float angle ){

    if(modo == EXAMINAR){
        
        anguloX = angle;
        rotarXExaminar(anguloX);
    }
    else{
        pitch = -angle;
        rotarXFirstPerson(pitch);
    }
}
void Camara::rotarY( float angle ){

    if(modo == EXAMINAR){
        
        anguloY = angle;
        rotarYExaminar(anguloY);
       
    }
    else{
        yaw = -angle;
        rotarYFirstPerson(yaw);
    }

}



/**
 * @brief   Esta función posiciona al observador de forma que el ojo está en la posición eye, mirando hacia el
            punto at y con el sentido “hacia arriba” definido por el vector up
 * 
 */
void Camara::setObserver () { 

    gluLookAt(  eye[0], eye[1], eye[2], at[0],  at[1],  at[2], up[0],  up[1],  up[2]);

    /*
    if(modo == EXAMINAR){

        glTranslatef(at[0],at[1],at[2]);
        rotarXExaminar(anguloX);
        rotarYExaminar(anguloY);
    }*/


}

void Camara::setProyeccion(){

    //indicar a OpenGL que todas las operacionessobre matrices que se apliquen desde 
    //ese instante hasta que se cambie el glMatrixMode, se aplicarán sobre la matriz de proyección
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //La proyeccion depende del tipo de camara
    switch (tipo) {
        case 1: //ORTOGONAL (1) --> glOrtho
            glOrtho( left, right, bottom, top, near, far);
    
        case 2: //Perspectiva (2) --> glFrustrum
            glFrustum( left, right, bottom, top, near, far);
    }
    

}

//---------------------------------------------------------
//------SETTERS
//---------------------------------------------------------
void Camara::setAt(Tupla3f atNew){
    at = atNew;
}

void Camara::setLeft(float nleft){
    left = nleft;
}

void Camara::setRight(float nright){
    right = nright;
}

void Camara::setNear(float nnear){
    near = nnear;
}

void Camara::setFar(float nfar){
    far = nfar;
}

void Camara::setBottom(float nbottom){
    bottom = nbottom;
}

void Camara::setTop(float ntop){
    top = ntop;
}

void Camara::setSeleccionaObjeto( bool selecciona){
    if(selecciona){
        seleccionaObjeto = true;
        modo = EXAMINAR;
    }
    else{
        seleccionaObjeto = false;
        modo = FIRSTPERSON;
    }
    
}

void Camara::setIndiceObjeto(int indice){
    indiceObjeto = indice;
}

//---------------------------------------------------------
//-----GETTERS
//---------------------------------------------------------
float Camara::getLeft(){
    return left;
}

float Camara::getRight(){
    return right;
}

float Camara::getNear(){
    return near;
}

float Camara::getFar(){
    return far;
}

float Camara::getBottom(){
    return bottom;
}

float Camara::getTop(){
    return top;
}

/**
 * @brief Devuelve el modo de movimiento actual de la camara 
 * 
 * @return int 0: si esta en modo EXAMINAR o 1 si está en modo FIRSTPERSON
 */
int Camara::getModo(){
    return modo;
}

int Camara::getIndiceObjeto(){
    return indiceObjeto;
}

bool Camara::getSeleccionaObjeto(){
    return seleccionaObjeto;
}

