#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

   //ply::read_vertices( nombre_archivo, this->v);

   //Practica 2

   

   // inicializar la tabla de vértices Caras Pares e Impares
   fPar.clear();
   fImpar.clear();

   for(int i=0; i < f.size(); i++){
      if(i%2 == 0){ //Si es una cara par
         fPar.push_back(f[i]);

      }
      else{ //Si es una cara impar
         fImpar.push_back(f[i]);    
      }
   }

   //Tablas de colores
   colorPunt.clear(); colorPunt.resize(v.size()); // tabla de color Modo puntos (MAGENTA)
   colorPunt.insert( colorPunt.begin(), v.size(), {255.0,0.0,255.0} );

   colorLin.clear();  colorLin.resize(v.size()); // tabla de color Modo Lineas (NEGRO)
   colorLin.insert( colorLin.begin(), v.size(),  {0.0,0.0,0.0});

   colorSol.clear(); colorSol.resize(v.size()); // tabla de color Modo Solido (AZUL)
   colorSol.insert( colorSol.begin(), v.size(),  {0.0,0.0,0.255} );

   colorFPar.clear(); colorFPar.resize(v.size()); // tabla de color Modo Ajedrez caras pares (ROJP)
   colorFPar.insert( colorFPar.begin(), v.size(), {255.0,0.0,0.0} );

   colorFImpar.clear(); colorFImpar.resize(v.size());// tabla de color Modo Ajedrez caras impares (VERDE)
   colorFImpar.insert( colorFImpar.begin(), v.size(), {0.0,255.0,0.0} );

   colorSeleccionado.clear();// tabla de color Modo Seleccion (AMARIILO)
   colorSeleccionado.insert( colorSeleccionado.begin(), v.size(), {255.0,255.0,0.0} );

   colorSeleccionable.clear();// tabla de color Modo Seleccion (AMARIILO)
   colorSeleccionable.insert( colorSeleccionable.begin(), v.size(), {255.0,255.0,0.0} );

   colorFParSeleccionado.clear(); // tabla de color Modo Ajedrez caras pares cuando esta seleccionado (AMARILLO)
   colorFParSeleccionado.insert( colorFParSeleccionado.begin(), v.size(), {255.0,255.0,0.0} );

   colorFImparSeleccionado.clear();// tabla de color Modo Ajedrez caras impares cuando esta seleccionado  (NEGRO)
   colorFImparSeleccionado.insert( colorFImparSeleccionado.begin(), v.size(), {0.0,0.0,0.0} );


   //Tabla de normales
   calcular_normales();

   //Material por defecto
   //Material mEsmeralda({ 0.0215, 0.1745, 0.0215, 0.55 },{0.633, 0.727811, 0.633, 0.55 },{0.07568, 0.61424, 0.07568, 0.55 },76.8) ;

   //m = mEsmeralda;

   //Material mRuby({ 0.1745, 0.01175, 0.01175, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.61424, 0.04136, 0.04136, 0.55 }, 76.8);

   Material mObsidian({ 0.15, 0.00, 0.15, 1.0 }, { 0.18275, 0.17, 0.22525, 0.82}, { 0.332741, 0.328634, 0.346435, 0.82}, 100.0);
   m = mObsidian;

   Material mAmarillo({0.329412, 0.223529, 0.027451,1.0},{ 0.992157, 0.941176, 0.807843, 1.0},{0.780392, 0.568627, 0.113725, 1.0},80.0);
   mSeleccion =mAmarillo;
}

