// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: estructura.h
// -- declaraciones de clase Estructura
//
// #############################################################################

#ifndef ESTRUCTURA_H_INCLUDED
#define ESTRUCTURA_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include <bitset>

#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "objply.h"

// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class Estructura
{

    public:
        Estructura();
        void draw(std::bitset<10> vision, bool seleccionado);
        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);


    protected:
        Cilindro * cilindro = nullptr;
        Cono * cono = nullptr;
        Esfera * esfera = nullptr;
        ObjPLY * yoshi = nullptr;


};

#endif