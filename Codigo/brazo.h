// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: brazo.h
// -- declaraciones de clase Brazo
//
// #############################################################################

#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include <bitset>

#include "cubo.h"
#include "asientos.h"

// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class Brazo
{

    public:
        Brazo();
        void draw(std::bitset<10> vision, bool seleccionado);
        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);

    protected:
        Cubo * cubo = nullptr;
        Asientos * asientos = nullptr;


};

#endif