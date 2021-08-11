#include "auxiliar.h"
#include "asientos.h"

Asientos::Asientos(){

    //---Objetos---------
    cubo = new Cubo(1);
    asiento = new ObjPLY("./plys/asiento.ply");

    //---Colores de los Objetos---------
    cubo->setColor({255.0,0.0,255.0},{0.0,0.0,0.0},{0.0,0.0,255.0},{255.0,0.0,0.0},{0.0,0.0,255.0});
    asiento->setColor({255.0,255.0,0.0},{255.0,0.0,255.0},{0.0,255.0,255.0},{255.0,0.0,0.0},{0.0,0.0,255.0});

    //---Materiales de los Objetos---------
    Material mRuby({ 0.1745, 0.01175, 0.01175, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.61424, 0.04136, 0.04136, 0.55 }, 76.8);
    Material mPerla( { 0.25, 0.20725, 0.20725, 0.922 },{0.296648, 0.296648, 0.296648, 0.922 }, {1.0, 0.829, 0.829, 0.922 } ,100.264);
    Material mEsmeralda({ 0.0215, 0.1745, 0.0215, 0.55 },{0.633, 0.727811, 0.633, 0.55 },{0.07568, 0.61424, 0.07568, 0.55 },50) ;
    Material mCyan({ 0.0,0.1,0.06 ,1.0},{0.50196078,0.50196078,0.50196078,1.0},{0.0,0.50980392,0.50980392,1.0},32.0) ;


    //Especificar materiales
    cubo->setMaterial(mCyan);
    asiento->setMaterial(mPerla);

}

void Asientos::draw(std::bitset<10> vision, bool seleccionado){

    //Parte lateral derecha
    glPushMatrix();
        glTranslatef(2.5,15.0,0.0);
        glScalef(5.0,30.0,30.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();

    //Parte lateral izquierda
    glPushMatrix();
        glTranslatef(62.5,15.0,0.0);
        glScalef(5.0,30.0,30.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();

    //Parte inferior
    glPushMatrix();
        glTranslatef(32.5,6.0,0.0);
        glScalef(55.0,12.0,30.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();

    //Parte posterior
    glPushMatrix();
        glTranslatef(32.5,14.0,-16.5);
        glScalef(55.0,28.0,3.0);
        cubo->draw(vision,seleccionado);
    glPopMatrix();

    //Asientos
    glPushMatrix();
        glTranslatef(31.0,12.0,-5.0);
        asiento->draw(vision,seleccionado);
    glPopMatrix();

}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Asientos::setColorModoSeleccion( Tupla3f cModoSeleccion){
    cubo->setColorModoSeleccion(cModoSeleccion);
    asiento->setColorModoSeleccion(cModoSeleccion);
}

void Asientos::setColorModoLineas(Tupla3f cLin){
    cubo->setColorModoLineas(cLin);
    asiento->setColorModoLineas(cLin);
}