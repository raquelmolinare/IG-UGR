#include "auxiliar.h"
#include "atraccion.h"

// *****************************************************************************
//
// Clase Atraccion
//
// *****************************************************************************

Atraccion::Atraccion(){

    base = new Base();
    estructuragiratoria = new EstructuraGiratoria();
}

void Atraccion::draw(std::bitset<10> vision, bool seleccionado){

    
    base->draw(vision,seleccionado);
    estructuragiratoria->draw(vision,seleccionado);
}

void Atraccion::restablecerValores(){
    estructuragiratoria->restablecerValores();
}

void Atraccion::movimientoPistonBrazo(float valor){
    estructuragiratoria->movimientoPistonBrazo(valor);
}

void Atraccion::modificaAlturaPiston( float valor ){

    estructuragiratoria->modificaAlturaPiston( valor);

}
void Atraccion::aumentarAlturaPiston( float valor ){

    estructuragiratoria->aumentarAlturaPiston( valor);

}
void Atraccion::disminuirAlturaPiston( float valor ){

    estructuragiratoria->disminuirAlturaPiston( valor);

}

void Atraccion::modificaGiroZBrazos( float valor ){

    estructuragiratoria->modificaGiroZBrazos( valor );

}

void Atraccion::disminuirGiroZBrazos( float valor ){

    estructuragiratoria->disminuirGiroZBrazos( valor );

}

void Atraccion::aumentarGiroZBrazos( float valor ){

    estructuragiratoria->aumentarGiroZBrazos( valor );

}

void Atraccion::modificaGiroEstructura(float valor ){
    
    estructuragiratoria->modificaGiroEstructura(valor );

}

void Atraccion::aumentarGiroEstructura(float valor ){
    
    estructuragiratoria->aumentarGiroEstructura(valor );

}
void Atraccion::disminuirGiroEstructura(float valor ){
    
    estructuragiratoria->disminuirGiroEstructura(valor );

}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Atraccion::setColorModoSeleccion( Tupla3f cModoSeleccion){
    base->setColorModoSeleccion(cModoSeleccion);
    estructuragiratoria->setColorModoSeleccion(cModoSeleccion);
}

void Atraccion::setColorModoLineas(Tupla3f cLin){
    base->setColorModoLineas(cLin);
    estructuragiratoria->setColorModoLineas(cLin);
}