#include "auxiliar.h"
#include "piston.h"
#include <math.h> 

Piston::Piston(){

    //---Objetos---------
    cubo = new Cubo(1);
    cilindro = new Cilindro(5, 50,1.0,1.0,true, true,'y');

    //---Colores de los Objetos---------
    cubo->setColor({255.0,0.0,255.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
    cilindro->setColor({255.0,255.0,0.0},{0.0,0.0,0.0},{255.0,0.0,05.0},{255.0,0.0,0.0},{0.0,255.0,0.0});

    //---Materiales de los Objetos---------
    Material mMetal({ 0.19225, 0.19225, 0.19225, 1.0}, {0.508273, 0.508273, 0.508273, 1.0 }, { 0.50754, 0.50754, 0.50754, 1.0}, 80.0);
    Material mNegro( { 0.02, 0.02, 0.02, 1.0  },{0.4, 0.4, 0.4, 1.0 }, { 0.01, 0.01, 0.01, 1.0} ,10.0);
    Material mRojo({ 0.1745, 0.01175, 0.01175, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.61424, 0.04136, 0.04136, 0.55 }, 100);

    //Especificar materiales
    cubo->setMaterial(mNegro);
    cilindro->setMaterial(mRojo);

    //---Parametro----
    cteAltura = 19;
    alpha=-9;
    subir = true;

}

float Piston::getAlpha(){
    return alpha;
}

void Piston::setAlpha(float valor){
    alpha=valor;
}

void Piston::draw(std::bitset<10> vision, bool seleccionado){

    glPushMatrix();
        glTranslatef(0.0,7.5,0.0);
        glScalef(5.0,15.0,5.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,alpha,0.0); //Alpha [-9,10]
        glScalef(1.0,30.0,1.0);
        cilindro->draw(vision,seleccionado);
    glPopMatrix();

}

void Piston::restablecerValores(){
    alpha=-9;
}

void Piston::modificaAlturaPiston( float valor ){

    if(valor > 0){

    if(subir){ //Si no se ha alcanzado el máximo de 10 se sigue subiendo
        cteAltura = 19;
        float incremento = alpha + fabs (cteAltura*valor);

        if(incremento >= 10.0){
            alpha=10.0;
            subir=false;
        }
        else{
            alpha = incremento;
        }

    }
    else{ //Si hay que bajar
        cteAltura = 20;
        float decremento = alpha - fabs (cteAltura*valor);

        if(decremento <= -9.0){
            alpha=-9.0;
            subir=true;
        }
        else{
            alpha = decremento;
        }
    }

    }


}

void Piston::disminuirAlturaPiston( float valor ){

    if(valor > 0){

    float decremento = alpha - fabs (cteAltura*valor);

    if(decremento <= -9.0){
        std::cout << "\t  No es posible disminuir mas la altura del piston "<< std::endl;
        alpha=-9.0;
    }
    else{
        alpha = decremento;
    }
    }

}

void Piston::aumentarAlturaPiston( float valor ){

    if(valor > 0){

    float incremento = alpha + fabs (cteAltura*valor);

    if(incremento >= 10.0){
        std::cout << "\t  No es posible aumentar mas la altura del piston "<< std::endl;
        alpha=10.0;
    }
    else{
        alpha = incremento;
    }

    }

}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Piston::setColorModoSeleccion( Tupla3f cModoSeleccion){
    cubo->setColorModoSeleccion(cModoSeleccion);
    cilindro->setColorModoSeleccion(cModoSeleccion);
}

void Piston::setColorModoLineas(Tupla3f cLin){
    cubo->setColorModoLineas(cLin);
    cilindro->setColorModoLineas(cLin);
}