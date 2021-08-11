#include "auxiliar.h"
#include "base.h"

Base::Base(){

    //---Objetos---------
    cilindro = new Cilindro(5, 50,1.0,1.0,true, true,'y');

    //---Colores de los Objetos---------
    cilindro->setColor({255.0,0.0,255.0},{0.0,0.0,0.0},{255.0,0.0,255.0},{255.0,0.0,0.0},{0.0,0.0,255.0});

    //---Materiales de los Objetos---------
    Material m({ 0.105882, 0.058824, 0.113725, 1.0}, {0.333333, 0.333333, 0.521569, 1.0}, {0.427451, 0.470588, 0.541176, 1.0}, 9.84615);

    //Especificar materiales
    cilindro->setMaterial(m);

}

void Base::draw(std::bitset<10> vision, bool seleccionado){

    //Parte inferior
    glPushMatrix();
        glScalef(110.0,4.0,110.0);
        cilindro->draw(vision,seleccionado);
    glPopMatrix();

    //Parte superior
    glPushMatrix();
        glTranslatef(0.0,4.0,0.0);
        glScalef(100.0,5.0,100.0);
        cilindro->draw(vision,seleccionado);
    glPopMatrix();
    
}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Base::setColorModoSeleccion( Tupla3f cModoSeleccion){
    cilindro->setColorModoSeleccion(cModoSeleccion);
}

void Base::setColorModoLineas(Tupla3f cLin){
    cilindro->setColorModoLineas(cLin);
}