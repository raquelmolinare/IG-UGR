// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: atraccion.h
// -- declaraciones de clase Atraccion (modelo jerarquico) y derivados
//
// #############################################################################

#ifndef ATRACCION_H_INCLUDED
#define ATRACCION_H_INCLUDED

#include "auxiliar.h"
#include <bitset>


#include "base.h"
#include "estructuragiratoria.h"

// *****************************************************************************
//
// clase Atraccion, para objetos que componen el Modelo Jerarquico
//
// *****************************************************************************

class Atraccion
{

    public:
        Atraccion();
        void draw(std::bitset<10> vision, bool seleccionado);

        void restablecerValores();
        void movimientoPistonBrazo(float valor);
        void modificaAlturaPiston( float valor );
        void aumentarAlturaPiston( float valor );
        void disminuirAlturaPiston( float valor );

        void modificaGiroZBrazos( float valor );
        void disminuirGiroZBrazos( float valor );
        void aumentarGiroZBrazos( float valor );

        void modificaGiroEstructura(float valor );
        void disminuirGiroEstructura(float valor );
        void aumentarGiroEstructura(float valor );

        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin); //Modifica el color de un objeto tipo malla


    protected:
        Base * base = nullptr;
        EstructuraGiratoria * estructuragiratoria = nullptr;


};

#endif
