// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: base.h
// -- declaraciones de clase Base
//
// #############################################################################

#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include <bitset>

#include "cilindro.h"

// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class Base
{

    public:
        Base();
        void draw(std::bitset<10> vision, bool seleccionado);
        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);

    protected:
        Cilindro * cilindro = nullptr;

};

#endif