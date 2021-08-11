

// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cono con centro de la base en el origen, radio y altura unidad por defecto 

class Cono : public ObjRevolucion
{
    public :
        Cono(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float altura = 1.0, const float radio = 1.0, bool tapa_inf=true, char eje='y', bool conTextura=false);

        

    private :
        Tupla3f norte;
        void crearMallaX( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_inf) ;
        void crearMallaY( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_inf) ;
        void crearMallaZ( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_inf) ;


        
} ;


#endif