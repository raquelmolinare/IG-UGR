#include "auxiliar.h"
#include "luz.h"
#include "luzdireccional.h"
#include <cmath>

#define PI 3.141592 //Definimos PI


// -----------------------------------------------------------------------------
// Constructor fuente de luz direccional a partir de todos los parámetros
LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f cAmbiente, Tupla4f cEspecular, Tupla4f cDifuso){

    id = idLuzOpenGL;
    colorAmbiente = cAmbiente;
    colorDifuso = cDifuso;
    colorEspecular = cEspecular;
    tipo = DIRECCIONAL;

    alpha = direccion[0]; 
    beta = direccion[1];

    float x,y,z;

    x = sin((alpha*PI)/180.0);
    y = cos((alpha*PI)/180.0) * (- sin((beta*PI)/180.0));
    z = cos((alpha*PI)/180.0) * cos((beta*PI)/180.0);

    posicion = {x,y,z, 0.0 };
    //std::cout << "Vector dirección: " << posicion << std::endl;


}


// -----------------------------------------------------------------------------
// Función para cambiar el angulo alpha
void LuzDireccional::variarAnguloAlpha( float incremento ){
    //ROTACION incremento GRADOS EN Y
    float x,y,z;

    x = (posicion[0] * cos((incremento*PI)/180.0)) + (posicion[2] * sin((incremento*PI)/180.0));
    y = posicion[1];
    z = (posicion[0] * -sin((incremento*PI)/180.0)) + (posicion[2] * cos((incremento*PI)/180.0)) ;

    alpha = alpha + incremento;

    posicion = {x,y,z,0.0 };
}


// -----------------------------------------------------------------------------
// Función para cambiar el angulo beta
void LuzDireccional::variarAnguloBeta( float incremento ){

    //ROTACION incremento GRADOS EN X
    float x,y,z;

    x = posicion[0];
    y = (posicion[1] * cos((incremento*PI)/180.0)) + (posicion[2] * -sin((incremento*PI)/180.0));
    z = (posicion[1] * sin((incremento*PI)/180.0)) + (posicion[2] * cos((incremento*PI)/180.0)) ;

    beta = beta + incremento;

    posicion = {x,y,z, 0.0};


}

float LuzDireccional::getAlpha(){
    return alpha;
}

float LuzDireccional::getBeta(){
    return beta;
}

Tupla4f LuzDireccional::getPosicion(){
    return posicion;
}