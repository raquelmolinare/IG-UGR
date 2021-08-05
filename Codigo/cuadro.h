// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuadro.h
// -- declaraciones de clase Cuadro
//
// #############################################################################

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "malla.h"

// *****************************************************************************
//
// clase para skybox
//
// *****************************************************************************

class Cuadro : public Malla3D{
    public:
        Cuadro(string imagen,float lado=150);
};

#endif