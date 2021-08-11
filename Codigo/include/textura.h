// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h
// -- declaraciones de clase Textura
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "auxiliar.h"
#include "jpg_imagen.hpp"
#include <string>
using namespace std;

// *****************************************************************************
//
// clase para la textura de los objetos
//
// *****************************************************************************

class Textura{

    public :
        Textura( string archivo );
        void activar ();
        
    private :
        GLuint textura_id = 0;
        std::vector <unsigned char> data;
        int width, height;
        

};

#endif