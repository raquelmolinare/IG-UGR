// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: asientos.h
// -- declaraciones de clase Asientos
//
// #############################################################################

#ifndef ASIENTOS_H_INCLUDED
#define ASIENTOS_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include <bitset>

#include "cubo.h"
#include "objply.h"

// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class Asientos
{

    public:
        Asientos();
        void draw(std::bitset<10> vision, bool seleccionado);
        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);

    protected:
        Cubo * cubo = nullptr;
        ObjPLY * asiento = nullptr;



};

#endif