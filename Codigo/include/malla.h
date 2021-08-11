// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"
#include "material.h"
#include "textura.h"
#include <bitset>
#include <vector>

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   //Crear VBO, devuelve el identificador
   GLuint CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram );

   
   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   // o bien a drawAjedrez
   void draw(std::bitset<10> vision, bool seleccionado) ;


   void setMaterial( Material mat ); //Modifica el material del objeto

   //void setColor( char puntos='m', char lineas='k', char solido='y', char ajed1='r', char ajed2='g'); //Modifica el color de un objeto tipo malla
   void setColor( Tupla3f cPunt, Tupla3f cLin, Tupla3f cSol, Tupla3f cFPar, Tupla3f cFImpar); //Modifica el color de un objeto tipo malla
   void setColorModoSeleccion( Tupla3f cModoSeleccion); //Modifica el color de un objeto tipo malla
   void setColorSeleccionado( Tupla3f cSeleccionado);
   void setColorModoLineas(Tupla3f cLin); //Modifica el color de un objeto tipo malla


   protected:

   // función que redibuja el objeto PARA EL MODO AJEDREZ
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void drawAjedrez(bool inmediato, std::bitset<10> vision,bool seleccionado) ;

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool modoAjedrez, std::bitset<10> vision, std::vector<int> tamanios,bool seleccionado);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool modoAjedrez, std::bitset<10> vision, std::vector<int> tamanios,bool seleccionado);

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)


   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> fPar ; //una terna de 3 enteros por cada cara o triángulo de las caras pares
   std::vector<Tupla3i> fImpar ; //una terna de 3 enteros por cada cara o triángulo de las caras impares

   // completar: tabla de colores, tabla de normales de vértices
   //Tablas de colores
   std::vector<Tupla3f> colorPunt;  // tabla de color Modo puntos
   std::vector<Tupla3f> colorLin;   // tabla de color Modo Lineas
   std::vector<Tupla3f> colorSol;   // tabla de color Modo Solido

   std::vector<Tupla3f> colorFPar;   // tabla de color Modo Ajedrez caras pares
   std::vector<Tupla3f> colorFImpar;   // tabla de color Modo Ajedrez caras impares

   std::vector<Tupla3f> colorFParSeleccionado;   // tabla de color Modo Ajedrez caras pares cuando el objeto esta seleccionado
   std::vector<Tupla3f> colorFImparSeleccionado;   // tabla de color Modo Ajedrez caras impares cuando el objeto esta seleccionado

   std::vector<Tupla3f> colorModoSeleccion;  // tabla de color Modo Seleccion de objetos
   std::vector<Tupla3f> colorSeleccionado;  // tabla de color cuando un objeto esta seleccionado
   std::vector<Tupla3f> colorSeleccionable;  // tabla de color cuando un objeto esta seleccionado


   //Práctica 3
   //Tabla de normales de vértices
   std::vector<Tupla3f> nv;  // tabla de normales de certices

   Material m; //= new Material({0.2,0.2,0.2,1.0}, {0.2,0.2,0.2,1.0},{0.2,0.2,0.2,1.0}, 128.0); //Material del objeto
   Material mSeleccion;

   //Practica 5
   //Tabla de coordenadas de textura
   std::vector<Tupla2f> ct;

   Textura * textura = nullptr;

    
   //Identificadores de los VBOs 
   //Se inicializan a 0 para indicar que no se han creado todavía
   GLuint id_vbo_ver=0;
   GLuint id_vbo_tri=0;
   GLuint id_vbo_nv=0;
   GLuint id_vbo_ct=0;
   GLuint id_vbo_f_par=0;
   GLuint id_vbo_f_impar=0;

   //COLORES
   GLuint id_vbo_col_par=0;
   GLuint id_vbo_col_impar=0;
   GLuint id_vbo_colorPunt=0;
   GLuint id_vbo_colorLin=0;
   GLuint id_vbo_colorSol=0;

   GLuint id_vbo_colorModoSeleccion=0;

   GLuint id_vbo_colorSeleccionado=0;
   GLuint id_vbo_colorSeleccionable=0;
   GLuint id_vbo_col_parSeleccionado=0;
   GLuint id_vbo_col_imparSeleccionado=0;

} ;


#endif
