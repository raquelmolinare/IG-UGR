// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: estructuragiratoria.h
// -- declaraciones de clase EstructuraGiratoria
//
// #############################################################################

#ifndef ESTRUCTURAGIRATORIA_H_INCLUDED
#define ESTRUCTURAGIRATORIA_H_INCLUDED

#include "auxiliar.h"
#include <bitset>
#include "brazo.h"
#include "piston.h"
#include "estructura.h"

#include "material.h"


// *****************************************************************************
//
// clase para objetos del modelo jerarquico que componen una atraccion
//
// *****************************************************************************

class EstructuraGiratoria
{

    public:
        EstructuraGiratoria();
        void draw(std::bitset<10> vision, bool seleccionado);
        void dibujarBrazos(std::bitset<10> vision, bool seleccionado);
        void dibujarPistones(std::bitset<10> vision, bool seleccionado);

        void restablecerValores();

        float calcularAlpha();
        void movimientoPistonBrazo(float valor);

        void modificaAlturaPiston( float valor );
        void disminuirAlturaPiston( float valor );
        void aumentarAlturaPiston( float valor );

        void modificaGiroZBrazos( float valor );
        void disminuirGiroZBrazos( float valor );
        void aumentarGiroZBrazos( float valor );

        void modificaGiroEstructura(float valor );
        void aumentarGiroEstructura(float valor );
        void disminuirGiroEstructura(float valor );

        void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
        void setColorModoLineas(Tupla3f cLin);

    protected:
        Piston * piston = nullptr;
        Brazo * brazo = nullptr;
        Estructura * estructura = nullptr;
    
        //Animacion estructura
        float cteGiroEstructura;
        float gamma; //Parámetro variación de la totacion en el eje y del conjunto de la estructura los brazos y los pistones
        
        //Animacion de los brazos
        float cteGiroBrazos;
        float beta; //Parámetro variación de la rotacion sobre el eje z de los brazos
        bool subir;



};

#endif