

// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Esfera con centro de la base en el origen, radio unidad  por defecto 

class Esfera : public ObjRevolucion
{
    public :
    Esfera ( const int num_vert_perfil = 10, const int num_instancias_perf = 20, const float radio=1.0, bool tapa_sup=true, bool tapa_inf=true, bool conTextura=false);
} ;


#endif