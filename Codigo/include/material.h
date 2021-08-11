// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
// -- declaraciones de clase Material
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clase para el material de los objetos
//
// *****************************************************************************

class Material{

    public :
        Material();
        Material (Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso, float mbrillo );
        void aplicar ();
   
    private :
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
};

#endif