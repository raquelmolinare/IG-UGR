#include "cuadro.h"
#include "malla.h"

Cuadro::Cuadro(string imagen, float lado){

    // inicializar la tabla de vértices  
   v.clear();

   v={{lado,-lado,0.0},
    {lado,lado,0.0},
    {-lado,lado,0.0},
    {-lado,-lado,0.0}
   };
    
    f.clear();

   f={{0,1,3}, {1,2,3}};

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

   
   calcular_normales();
   
   //Material por defecto
   Material mBlanco({ 0.25,0.25,0.25,1.0 }, { 1.0,1.0,1.0,1.0}, { 1.0,1.0,1.0,1.0}, 100.0); 
   m = mBlanco;

   //Tablas de colores
   setColor({255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0});

   ct.clear();
   
   ct = {
       {1.0,1.0},
       {1.0,0.0},
       {0.0,0.0},
       {0.0,1.0},
   };

   textura = new Textura(imagen);
   
    
}