#include "auxiliar.h"
#include "brazo.h"

Brazo::Brazo(){

    //---Objetos---------
    cubo = new Cubo(1);
    asientos = new Asientos();

    //---Colores de los Objetos---------
    cubo->setColor({255.0,0.0,255.0},{255.0,255.0,0.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{0.0,0.0,255.0});

    //---Materiales de los Objetos---------
    Material m({ 0.0,0.0,0.0,1.0 }, { 1.0,1.0,1.0,1.0}, { 0.0,0.0,0.0,1.0}, 100.0); 

    //Especificar materiales
    cubo->setMaterial(m);

}



void Brazo::draw(std::bitset<10> vision, bool seleccionado){

    glPushMatrix();
        glTranslatef(60.0,5.0,0.0);
        glScalef(120.0,10.0,10.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(120.0,0.0,0.0);
        glScalef(0.5,0.5,0.5);
        glRotatef(15.0,0,0,1);
        asientos->draw(vision,seleccionado);
    glPopMatrix();
}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Brazo::setColorModoSeleccion( Tupla3f cModoSeleccion){
    cubo->setColorModoSeleccion(cModoSeleccion);
    asientos->setColorModoSeleccion(cModoSeleccion);
}

void Brazo::setColorModoLineas(Tupla3f cLin){
    cubo->setColorModoLineas(cLin);
    asientos->setColorModoLineas(cLin);
}