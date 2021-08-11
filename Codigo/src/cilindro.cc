#include "auxiliar.h"
#include "cilindro.h"

Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapa_sup, bool tapa_inf,char eje, bool conTextura){

    // Crear el  perfil original
    vPerfilOriginal.clear(); //Tabla de coordenadas del perfil original

    int num_vertices = num_vert_perfil;

    if(num_vert_perfil < 2)
        num_vertices = 2;


    //Distancia en y desde un vertice a otro
    float a = altura / (num_vertices-1);

    float y=0;

    for(int i=0; i < num_vertices; i++){
        y= i*a;
        vPerfilOriginal.push_back({radio, y ,0});
    }

    crearMalla(vPerfilOriginal,num_instancias_perf,tapa_sup,tapa_inf,eje, conTextura);

    //COLORES
   
   //Tablas de colores
//    colorPunt.clear(); colorPunt.resize(v.size()); // tabla de color Modo puntos (ROJO)
//    colorPunt.insert( colorPunt.begin(), v.size(), {255.0,0.0,0.0} );

//    colorLin.clear();  colorLin.resize(v.size()); // tabla de color Modo Lineas (NEGRO)
//    colorLin.insert( colorLin.begin(), v.size(), {0.0,0.0,0.0} );

//    colorSol.clear(); colorSol.resize(v.size()); // tabla de color Modo Solido (VERDE)
//    colorSol.insert( colorSol.begin(), v.size(), {0.0,255.0,0.0});

//    colorFPar.clear(); colorFPar.resize(v.size()); // tabla de color Modo Ajedrez caras pares (AMARILLO)
//    colorFPar.insert( colorFPar.begin(), v.size(), {255.0,255.0,0.0});

//    colorFImpar.clear(); colorFImpar.resize(v.size());// tabla de color Modo Ajedrez caras impares (NEGRO)
//    colorFImpar.insert( colorFImpar.begin(), v.size(), {0.0,0.0,0.0} );
   
}