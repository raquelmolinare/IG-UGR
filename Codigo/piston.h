// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: piston.h
// -- declaraciones de clase Piston
//
// #############################################################################

#ifndef PISTON_H_INCLUDED
#define PISTON_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include <bitset>

#include "cubo.h"
#include "cilindro.h"

// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class Piston
{

    public:
        Piston();
        void draw(std::bitset<10> vision, bool seleccionado);
        void restablecerValores();
        void modificaAlturaPiston( float valor );
        void disminuirAlturaPiston( float valor );
        void aumentarAlturaPiston( float valor );

        float getAlpha();
        void setAlpha(float valor);

        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);


    protected:
        Cubo * cubo = nullptr;
        Cilindro * cilindro = nullptr;
        float cteAltura;
        float alpha; //Parámetro variación de la traslacion del piston
        bool subir;

};

#endif