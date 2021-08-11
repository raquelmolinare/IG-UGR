// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objrevolucion.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"
#include "ply_reader.h"
#include "material.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, char eje='y', bool conTextura=false) ;
        ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, char eje='y', bool conTextura=false) ;

        // función que redibuja el objeto
        // está función llama a 'draw_ModoInmediato' (modo inmediato)
        // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
        // o bien a drawAjedrez
        void draw(std::bitset<10> vision, bool seleccionado) ;

        void setTextura(string archivo);

    protected:
        // función que redibuja el objeto PARA EL MODO AJEDREZ
        // está función llama a 'draw_ModoInmediato' (modo inmediato)
        // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
        void drawAjedrez(bool inmediato, std::bitset<10> vision, bool seleccionado) ;

        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,char eje, bool conTextura );
        void crearMalla(std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf,char eje, bool conTextura) ;

        void crearMallaFinalX( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf) ;
        void crearMallaFinalY( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf) ;
        void crearMallaFinalZ( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf) ;
        
        void gestionarPolos(std::vector<Tupla3f> & perfil_original, std::vector<Tupla3f> & polos);

        void completarObjeto();

        //Practica 5: Texturas
        void instaciaExtraPerfil(bool tapa_sup, bool tapa_inf);
        void calcularCoordTextura();
        

        bool poloSur = false;
        bool poloNorte = false;

        char eje;
        int numInstancias;
        int tamPerfilOriginal;
        bool tieneCoordTexturas = false;

        std::vector<Tupla3f> vPerfilOComp ;   // tabla de coordenadas de vértices del perfil original COMPLETO (al crear la malla contendrá los polos)
        
        std::vector<Tupla3f> vPerfilOriginal ;   // tabla de coordenadas de vértices del perfil original (al crear la malla no contendrá los polos)
        std::vector<Tupla3f> vPolos; //coordenadas de vertices de los polos

        std::vector<Tupla3f> vNoTapas; //coordenadas de vertices y las coordenadas de las tapas
        std::vector<Tupla3i> fNoTapas; //Tabla de triangulos teniendo en cuenta las tapas

        std::vector<Tupla3f> vTapas; //coordenadas de vertices y las coordenadas de las tapas
        std::vector<Tupla3i> fTapas; //Tabla de triangulos teniendo en cuenta las tapas

        std::vector<int> sizeTapas; //{fTapas.size(), fparTapas.size(), fimparTapas.size()}
        std::vector<int> sizeNoTapas; //{fNoTapas.size(), fparNoTapas.size(), fimparNoTapas.size()}

} ;




#endif
