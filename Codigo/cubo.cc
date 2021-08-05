#include "auxiliar.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices  
   v.clear();

   v={   {-lado/2,lado/2,lado/2},      //0
         {lado/2,lado/2,lado/2},       //1
         {-lado/2,-lado/2,lado/2},     //2
         {lado/2,-lado/2,lado/2},      //3
         {lado/2,lado/2,-lado/2},      //4
         {-lado/2,lado/2,-lado/2},     //5    
         {lado/2,-lado/2,-lado/2},     //6
         {-lado/2,-lado/2,-lado/2},    //7
   };


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.clear();

   f={
      {2,3,0},{0,3,1},  //Front
      {7,4,6},{4,7,5},  //Back
      {1,3,6},{6,4,1},  //Right
      {5,7,2},{2,0,5},  //Left
      {1,5,0},{4,5,1},  //Up
      {7,6,2},{2,6,3}   //Down
   };

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
   colorPunt.clear(); // tabla de color Modo puntos (MAGENTA)
   colorPunt.insert( colorPunt.begin(), v.size(), {255.0,0.0,255.0} );

   colorLin.clear(); // tabla de color Modo Lineas (NEGRO)
   colorLin.insert( colorLin.begin(), v.size(), {0.0,0.0,0.0} );

   colorSol.clear(); // tabla de color Modo Solido (MAGENTA)
   colorSol.insert( colorSol.begin(), v.size(),   {255.0,0.0,255.0} );

   colorFPar.clear(); // tabla de color Modo Ajedrez caras pares (ROJO)
   colorFPar.insert( colorFPar.begin(), v.size(), {255.0,0.0,0.0} );

   colorFImpar.clear();// tabla de color Modo Ajedrez caras impares (VERDE)
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
   Material mEsmeralda({ 0.0215, 0.1745, 0.0215, 0.55 },{0.633, 0.727811, 0.633, 0.55 },{0.07568, 0.61424, 0.07568, 0.55 },76.8) ;

   m = mEsmeralda;


   Material mAmarillo({0.329412, 0.223529, 0.027451,1.0},{ 0.992157, 0.941176, 0.807843, 1.0},{0.780392, 0.568627, 0.113725, 1.0},80.0);
   mSeleccion =mAmarillo;


}

