// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tetraedro.h

//
// #############################################################################

#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen, lado unidad por defecto y color por defecto M

//Para los colores N=Black, R=Red, G=Green, B=Blue, M=Magenta, C=Cyan, Y=Yellow W=White


class Tetraedro: public Malla3D
{
   public:
      Tetraedro(float l=1.0);

} ;




#endif
