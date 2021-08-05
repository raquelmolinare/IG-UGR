// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Luz (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// LuzDireccional


class LuzDireccional : public Luz
{
   public:
      //Construcctor de la fuente de luz
      LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f cAmbiente, Tupla4f cEspecular, Tupla4f cDifuso);

      // Cambiar ángulo:
      void variarAnguloAlpha( float incremento ) ;
      void variarAnguloBeta( float incremento ) ;

      float getAlpha();
      float getBeta();
      Tupla4f getPosicion();

      

   protected :

      float alpha ;  //Ángulo de rotación en torno al eje y (Longitud)
      float beta ;   //Ángulo de rotación en torno al eje x (Latitud)


} ;




#endif