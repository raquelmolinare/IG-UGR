// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Luz.h
// -- declaraciones de clase Luz y derivados
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clase para objetos Fuentes de Luz
//
// *****************************************************************************

typedef enum {DIRECCIONAL, POSICIONAL} tipoFuente;

class Luz
{
   public:
      void activar();

   protected:
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;
      tipoFuente tipo;



} ;

#endif