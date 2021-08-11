#include "auxiliar.h"
#include "luz.h"
#include "luzposicional.h"

#include <cmath>

#define PI 3.141592 //Definimos PI


// -----------------------------------------------------------------------------
// Constructor fuente de luz posicional
LuzPosicional::LuzPosicional(Tupla3f pos, GLenum idLuzOpenGL, Tupla4f cAmbiente, Tupla4f cEspecular, Tupla4f cDifuso){

    posicion = {pos[0], pos[1], pos[2], 1.0 };

    id = idLuzOpenGL;
    colorAmbiente = cAmbiente;
    colorDifuso = cDifuso;
    colorEspecular = cEspecular;
    tipo = POSICIONAL;

    //Variables para la animacion del color
    colorAmbienteInical = cAmbiente;
    animacion = 0;
    pasos = 3;
    color = 0;

    colorAmbiente1 = {0.0,1.0,0.0,1.0};
    colorAmbiente2 = {0.0,0.0,1.0,1.0};
}


void LuzPosicional::animar( float incremento ){

    rotarX(incremento);
    //rotarY(incremento);
        
    
    cambiarColor();
    this->activar();
}

void LuzPosicional::rotarX(float incremento ){
    //ROTACION incremento GRADOS EN X
    float x,y,z;

    x = posicion[0];
    y = (posicion[1] * cos((incremento*PI)/180.0)) + (posicion[2] * -sin((incremento*PI)/180.0));
    z = (posicion[1] * sin((incremento*PI)/180.0)) + (posicion[2] * cos((incremento*PI)/180.0)) ;

    posicion = {x,y,z, 1.0};
}

void LuzPosicional::rotarY(float incremento ){
    //ROTACION incremento GRADOS EN Y
    float x,y,z;

    
    x = (posicion[0] * cos((incremento*PI)/180.0)) + (posicion[2] * sin((incremento*PI)/180.0));
    y = posicion[1];
    z = (posicion[0] * -sin((incremento*PI)/180.0)) + (posicion[2] * cos((incremento*PI)/180.0)) ;

    posicion = {x,y,z,1.0 };

}

void LuzPosicional::cambiarColor(){
    //CAMBIAR COLOR
    if(animacion == pasos){

       if(color == 0){
           colorAmbiente= {0.0,0.5,0.0,1.0};
           color= (color+1)%3;
       }
       else if(color == 1){
           colorAmbiente = {0.0,0.0,0.5,1.0};
           color= (color+1)%3;
       }
       else{
            colorAmbiente = {0.0,0.0,0.0,1.0};
            color= (color+1)%3;
       }
       animacion=0;
    }
    else{
       animacion++;
    }
}
