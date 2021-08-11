#include "auxiliar.h"
#include "esfera.h"

#define PI 3.141592 //Definimos PI


Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf, const float radio, bool tapa_sup, bool tapa_inf, bool conTextura){

    // Crear el  perfil original
    vPerfilOriginal.clear(); //Tabla de coordenadas del perfil original
    
    float y,x;

    std::vector<Tupla3f> vector; vector.clear();


    for(int i=1; i < num_vert_perfil; i++){ 
        x = radio * cos((PI*i)/(num_vert_perfil*2));
        y = radio * sin((PI*i)/(num_vert_perfil*2));
        vector.push_back({x,y,0});
    }

    vPerfilOriginal.push_back({0,-radio,0}); //incluimos el polo sur

    for(int i=1; i < num_vert_perfil; i++){ //incluimos la parte negativa (y)
        x = vector[vector.size()-i][0];
        y = vector[vector.size()-i][1];
        vPerfilOriginal.push_back({x,-y,0}); //incluimos el polo sur
    }

    vPerfilOriginal.push_back({radio,0,0});

    for(int i=0; i < num_vert_perfil-1; i++){ //incluimos la parte positiva (y)
        x = vector[i][0];
        y = vector[i][1];
        vPerfilOriginal.push_back({x,y,0}); //incluimos el polo sur
    }

    vPerfilOriginal.push_back({0,radio,0}); //incluimos el polo norte



    crearMalla(vPerfilOriginal,num_instancias_perf,tapa_sup,tapa_inf,'y', conTextura);

    //COLORES
   
   //Tablas de colores
//    colorPunt.clear(); colorPunt.resize(v.size()); // tabla de color Modo puntos (VERDE)
//    colorPunt.insert( colorPunt.begin(), v.size(), {0.0,255.0,0.0} );

//    colorLin.clear();  colorLin.resize(v.size()); // tabla de color Modo Lineas (NEGRO)
//    colorLin.insert( colorLin.begin(), v.size(),  {0.0,0.0,0.0});

//    colorSol.clear(); colorSol.resize(v.size()); // tabla de color Modo Solido (ROJO)
//    colorSol.insert( colorSol.begin(), v.size(),  {255.0,0.0,0.0});

//    colorFPar.clear(); colorFPar.resize(v.size()); // tabla de color Modo Ajedrez caras pares (AMARILLO)
//    colorFPar.insert( colorFPar.begin(), v.size(), {255.0,255.0,0.0} );

//    colorFImpar.clear(); colorFImpar.resize(v.size());// tabla de color Modo Ajedrez caras impares (NEGRO)
//    colorFImpar.insert( colorFImpar.begin(), v.size(), {0.0,0.0,0.0} );

   

}
