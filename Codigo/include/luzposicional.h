// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Luz (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// LuzPosicional


class LuzPosicional : public Luz
{
   public:
      LuzPosicional(Tupla3f pos, GLenum idLuzOpenGL, Tupla4f cAmbiente, Tupla4f cEspecular, Tupla4f cDifuso);
      void animar( float velocidad ) ;

   private:
      Tupla4f colorAmbienteInical;
      int animacion;
      int pasos;
      Tupla4f colorAmbiente1;
      Tupla4f colorAmbiente2;
      int color;
      void cambiarColor() ;
      void rotarX(float incremento);
      void rotarY(float incremento);


} ;




#endif