// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: skybox.h

//
// #############################################################################

#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"

#include <bitset>

// *****************************************************************************
//
// clase SkyBox
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen Y lado 
// las normales hacia dentro


class SkyBox : public Malla3D
{
   public:
        SkyBox(string imagen,float r=500.0);
        //void draw(std::bitset<10> vision, bool seleccionado);

   private:
        //Esfera * esfera = nullptr;
        float radio;
        int numInstancias;
        int numVertPerfil;
        std::vector<Tupla3f> vPerfil;
        //Textura * textura = nullptr;
        void crearSemiesfera();
        void coordTexturas();

} ;




#endif