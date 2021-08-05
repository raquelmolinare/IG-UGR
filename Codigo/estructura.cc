#include "auxiliar.h"
#include "estructura.h"

Estructura::Estructura(){
    //---Objetos---------
    cilindro = new Cilindro(5, 50,1.0,1.0,true, true,'y');
    cono = new Cono(5,50,1.0,1.0,true,'y');
    esfera = new Esfera(50,50, 1.0, true, true,true);
    yoshi = new ObjPLY("./plys/yoshi.ply");
    
    //---Colores de los Objetos---------
    cilindro->setColor({255.0,0.0,255.0},{255.0,255.0,0.0},{0.0,255.0,0.0},{255.0,0.0,0.0},{0.0,0.0,255.0});
    cono->setColor({255.0,0.0,255.0},{255.0,255.0,0.0},{255.0,0.0,0.0},{255.0,0.0,0.0},{0.0,0.0,255.0});
    esfera->setColor({255.0,0.0,255.0},{255.0,255.0,0.0},{255.0,0.0,0.0},{255.0,0.0,0.0},{0.0,0.0,255.0});

    //---Materiales de los Objetos---------
    Material mC({ 0.25, 0.25, 0.25, 1.0 }, {0.774597, 0.774597, 0.774597, 1.0}, {0.4, 0.4, 0.4, 1.0}, 100.0); 
    Material mCono( { 0.19125, 0.0735, 0.0225, 1.0 },{0.256777, 0.137622, 0.086014, 1.0 }, {0.7038, 0.27048, 0.0828, 1.0 } ,12.8); 
    Material mEsfera({ 0.1745, 0.01175, 0.01175, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.61424, 0.04136, 0.04136, 0.55 }, 76.8);

    //Especificar materiales
    cilindro->setMaterial(mC);
    cono->setMaterial(mC);
    esfera->setMaterial(mEsfera);

    esfera->setTextura("./texturas/text-world-map.jpg");

}


void Estructura::draw(std::bitset<10> vision, bool seleccionado){

    //Soporte de los pistones
    glPushMatrix();
        glTranslatef(0.0,9.0,0.0);
        glScalef(30.0,15.0,30.0);
        cono->draw(vision,seleccionado);
    glPopMatrix();

    //Cilindro inferior
    glPushMatrix();
        glTranslatef(0.0,12.0,0.0);
        glScalef(20.0,40.0,20.0);
        cilindro->draw(vision,seleccionado);
    glPopMatrix();

    //Cilindro superior
    glPushMatrix();
        glTranslatef(0.0,72.0,0.0);
        glScalef(20.0,4.0,20.0);
        cilindro->draw(vision,seleccionado);
    glPopMatrix();

    //esfera intermedia
    glPushMatrix();
        glTranslatef(0.0,62.0,0.0);
        glScalef(10.0,10.0,10.0);
        esfera->draw(vision,seleccionado);
    glPopMatrix();

    //yoshi
    glPushMatrix();
        glTranslatef(0.0,76.0,0.0);
        yoshi->draw(vision,seleccionado);
    glPopMatrix();
    
}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Estructura::setColorModoSeleccion( Tupla3f cModoSeleccion){
    cono->setColorModoSeleccion(cModoSeleccion);
    cilindro->setColorModoSeleccion(cModoSeleccion);
    esfera->setColorModoSeleccion(cModoSeleccion);
    yoshi->setColorModoSeleccion(cModoSeleccion);
}

void Estructura::setColorModoLineas(Tupla3f cLin){
    cono->setColorModoLineas(cLin);
    cilindro->setColorModoLineas(cLin);
    esfera->setColorModoLineas(cLin);
    yoshi->setColorModoLineas(cLin);
}