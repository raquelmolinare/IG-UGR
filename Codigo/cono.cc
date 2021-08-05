#include "auxiliar.h"
#include "cono.h"

#define PI 3.141592 //Definimos PI

Cono::Cono( const int num_vert_perfil, const int num_instancias_perf, const float altura , const float radio, bool tapa_inf, char eje, bool conTextura){

  // Crear el  perfil original
  vPerfilOriginal.clear(); //Tabla de coordenadas del perfil original

  int num_vertices = num_vert_perfil;

   if(num_vert_perfil < 2)
        num_vertices = 2;
    
  //Distancia en y desde un vertice a otro
  float a = altura / (num_vertices-1);

  //Distancia en x desde un vertice a otro
  float b = radio / (num_vertices-1);

  float x,y;

  for(int i=0; i < num_vertices; i++){
      x = radio - (b*i);
      y = a*i;
      vPerfilOriginal.push_back({x, y ,0});
  }
  
  //EXTRAEMOS EL VERTICE SUPEIOR PARA GESTONARLO DESPUES
  norte = vPerfilOriginal.back();
  vPerfilOriginal.pop_back(); //Lo extraemos del perfil original

   //Crear la malla
   if(eje == 'x')
      crearMallaX(vPerfilOriginal,num_instancias_perf, tapa_inf);
   else if(eje == 'y')
      crearMallaY(vPerfilOriginal,num_instancias_perf, tapa_inf);
   else
      crearMallaZ(vPerfilOriginal,num_instancias_perf, tapa_inf);

   //Práctica 5 ---- TEXTURAS----------------------
      //Calcular coordenadas de textura si se requiere
      if(conTextura){
         //copiar el primer perfil al final 
         calcularCoordTextura();
      }
   completarObjeto();

   //COLORES
   
   //Tablas de colores
   // colorPunt.clear(); colorPunt.resize(v.size()); // tabla de color Modo puntos (ROJO)
   // colorPunt.insert( colorPunt.begin(), v.size(), {255.0,0.0,0.0} );

   // colorLin.clear();  colorLin.resize(v.size()); // tabla de color Modo Lineas (NEGRO)
   // colorLin.insert( colorLin.begin(), v.size(), {0.0,0.0,0.0} );

   // colorSol.clear(); colorSol.resize(v.size()); // tabla de color Modo Solido (VERDE)
   // colorSol.insert( colorSol.begin(), v.size(), {0.0,255.0,0.0});

   // colorFPar.clear(); colorFPar.resize(v.size()); // tabla de color Modo Ajedrez caras pares (AMARILLO)
   // colorFPar.insert( colorFPar.begin(), v.size(), {255.0,255.0,0.0});

   // colorFImpar.clear(); colorFImpar.resize(v.size());// tabla de color Modo Ajedrez caras impares (NEGRO)
   // colorFImpar.insert( colorFImpar.begin(), v.size(), {0.0,0.0,0.0} );

}

/**
 * En este caso crear malla considera vNoTapas y fNoTapas como el cono con el polo norte (OBLIGATORO PARA QUE SEA UN CONO)
 * Y vTapas y fTapas se considera con la tapa sur también
 */
void Cono::crearMallaX(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool tapa_inf ) {
   
   //Cambiamos la x e y del polo norte
   float p = norte[1];
   norte={p,0,0};

  //1 Crear la tabla de vértices------------------------------------------------------------------------
   //Partimos de la tabla de vértices vacía.
   float x,y,z;
   vNoTapas.clear();
   for(int i=0; i <= num_instancias_perf-1; i++){       //Para cada i desde 0 hasta N − 1 (ambos incluidos)
      for(int j=0; j <= perfil_original.size()-1; j++){  //Para cada j desde 0 hasta M − 1 (ambos incluidos)
         //Sea v vértice obtenido rotando j un ángulo igual a 2πi/N radianes.
         y = cos(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada y de O' = cos(2*pi*i/N) * hipotenusa (h=Ox)
         x = perfil_original[j][1];                                  //La coordenada x de O' = Oy
         z = sin(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada z de O' = sin(2*pi*i/N) * hipotenusa (h=Ox)


         //Añadir v a la tabla de vértices (al final)
         vNoTapas.push_back({x,y,z});
      }
   }


   //2 Crear la tabla de triángulos---------------------------------------------------------------------
   int a,b,c;

   //Partimos de la tabla de triángulos vacía
   fNoTapas.clear();
   
   if(perfil_original.size() >= 2){
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
         for(int j=0; j <= perfil_original.size()-2; j++){  //Para cada j desde 0 hasta M − 2 (ambos incluidos)

            a = (perfil_original.size() * i) + j;     //Sea a = M i + j
            b = (perfil_original.size() * ((i+1)%num_instancias_perf)) + j;   //Sea b = M((i + 1) m´od N) + j

            fNoTapas.push_back({a, b, b+1});//Añadir triángulo formado por los índices a, b y b + 1.
            fNoTapas.push_back({a, b+1, a+1});//Añadir triángulo formado por los índices a, b + 1 y a + 1.
         }
      }
   }


  //HACER PERMANENTE LA TAPA SUPERIOR
  vNoTapas.push_back(norte); //Insertamos polo norte

  //TABLA DE TRIANGULOS TAPA SUPERIOR---------------------------------------------------------------------

  //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
  // el último vértice de cada instancia 
  //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
  for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
    //vNoTapas.size()-1 es el índice del polo norte
    a = vNoTapas.size() - 1;
    b = (perfil_original.size() * (i+1))-1;
    c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
    if( c == -1){
      c=(perfil_original.size() * num_instancias_perf ) - 1;
    }
    fNoTapas.push_back({a,b,c});//Añadir triángulo formado 
  }
   
  v.clear(); v= vNoTapas;
  f.clear(); f= fNoTapas;

  //3 Si es necesario crear las tapa inferior------------------------------------------------------------------

  //Si se requiere la tapa inferior
  if( tapa_inf){
    //3.1 Añadir el vértice del polo sur 
    //el polo sur (tendrá índice N)

    vTapas.clear();
    vTapas = vNoTapas;

    //El polo sur es una proyeccion de los vertices
    float xSur;

    xSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
    vTapas.push_back({xSur,0,0});//Insertamos la proyección del polo Sur
    
    //3.2 Añadir las caras correspondientes

    fTapas.clear();
    fTapas = fNoTapas;
    //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
    //polo sur con los N primeros vértices de cada instancia 
    //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
    for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
          //vTapas.size()-1 es el índice del polor sur PORQUE SOLO SE HA REQUERIDO ESTA TAPA
          a = vTapas.size() - 1 ;
          b = perfil_original.size() * i;
          c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
          fTapas.push_back({a,c,b});//Añadir triángulo formado 
    }

    v.clear(); v= vTapas;
    f.clear(); f= fTapas;

  }

   completarObjeto();
}

/**
 * En este caso crear malla considera vNoTapas y fNoTapas como el cono con el polo norte (OBLIGATORO PARA QUE SEA UN CONO)
 * Y vTapas y fTapas se considera con la tapa sur también
 */
void Cono::crearMallaY(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool tapa_inf ) {
   
  //1 Crear la tabla de vértices------------------------------------------------------------------------
   //Partimos de la tabla de vértices vacía.
   float x,y,z;
   vNoTapas.clear();
   for(int i=0; i <= num_instancias_perf-1; i++){       //Para cada i desde 0 hasta N − 1 (ambos incluidos)
      for(int j=0; j <= perfil_original.size()-1; j++){  //Para cada j desde 0 hasta M − 1 (ambos incluidos)
         //Sea v vértice obtenido rotando j un ángulo igual a 2πi/N radianes.
         x = cos(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada x de O' = cos(2*pi*i/N) * hipotenusa (h=Ox)
         y = perfil_original[j][1];                                  //La coordenada y de O' = Oy
         z = sin(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada z de O' = sin(2*pi*i/N) * hipotenusa (h=Ox)


         //Añadir v a la tabla de vértices (al final)
         vNoTapas.push_back({x,y,z});
      }
   }


   //2 Crear la tabla de triángulos---------------------------------------------------------------------
   int a,b,c;

   //Partimos de la tabla de triángulos vacía
   fNoTapas.clear();
   
   if(perfil_original.size() >= 2){
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
         for(int j=0; j <= perfil_original.size()-2; j++){  //Para cada j desde 0 hasta M − 2 (ambos incluidos)

            a = (perfil_original.size() * i) + j;     //Sea a = M i + j
            b = (perfil_original.size() * ((i+1)%num_instancias_perf)) + j;   //Sea b = M((i + 1) m´od N) + j

            fNoTapas.push_back({a, b+1, b});//Añadir triángulo formado por los índices a, b y b + 1.
            fNoTapas.push_back({a, a+1, b+1});//Añadir triángulo formado por los índices a, b + 1 y a + 1.
         }
      }
   }


  //HACER PERMANENTE LA TAPA SUPERIOR
  vNoTapas.push_back(norte); //Insertamos polo norte

  //TABLA DE TRIANGULOS TAPA SUPERIOR---------------------------------------------------------------------

  //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
  // el último vértice de cada instancia 
  //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
  for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
    //vNoTapas.size()-1 es el índice del polo norte
    a = vNoTapas.size() - 1;
    b = (perfil_original.size() * (i+1))-1;
    c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
    if( c == -1){
      c=(perfil_original.size() * num_instancias_perf ) - 1;
    }
    fNoTapas.push_back({a,c,b});//Añadir triángulo formado 
  }
   
  v.clear(); v= vNoTapas;
  f.clear(); f= fNoTapas;

  //3 Si es necesario crear las tapa inferior------------------------------------------------------------------

  //Si se requiere la tapa inferior
  if( tapa_inf){
    //3.1 Añadir el vértice del polo sur 
    //el polo sur (tendrá índice N)

    vTapas.clear();
    vTapas = vNoTapas;

    //El polo sur es una proyeccion de los vertices
    float ySur;

    ySur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
    vTapas.push_back({0,ySur,0});//Insertamos la proyección del polo Sur
    
    //3.2 Añadir las caras correspondientes

    fTapas.clear();
    fTapas = fNoTapas;
    //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
    //polo sur con los N primeros vértices de cada instancia 
    //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
    for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
          //vTapas.size()-1 es el índice del polor sur PORQUE SOLO SE HA REQUERIDO ESTA TAPA
          a = vTapas.size() - 1 ;
          b = perfil_original.size() * i;
          c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
          fTapas.push_back({a,b,c});//Añadir triángulo formado 
    }

    v.clear(); v= vTapas;
    f.clear(); f= fTapas;

  }

   completarObjeto();
}

/**
 * En este caso crear malla considera vNoTapas y fNoTapas como el cono con el polo norte (OBLIGATORO PARA QUE SEA UN CONO)
 * Y vTapas y fTapas se considera con la tapa sur también
 */
void Cono::crearMallaZ(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool tapa_inf ) {

   //Cambiamos la z e y del polo norte
   float p = norte[1];
   norte={0,0,p};
   
  //1 Crear la tabla de vértices------------------------------------------------------------------------
   //Partimos de la tabla de vértices vacía.
   float x,y,z;
   vNoTapas.clear();
   for(int i=0; i <= num_instancias_perf-1; i++){       //Para cada i desde 0 hasta N − 1 (ambos incluidos)
      for(int j=0; j <= perfil_original.size()-1; j++){  //Para cada j desde 0 hasta M − 1 (ambos incluidos)
         //Sea v vértice obtenido rotando j un ángulo igual a 2πi/N radianes.
         y = cos(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada y de O' = cos(2*pi*i/N) * hipotenusa (h=Ox)
         z = perfil_original[j][1];                                  //La coordenada z de O' = Oy
         x = sin(2*PI*i/num_instancias_perf)*perfil_original[j][0];  //La coordenada x de O' = sin(2*pi*i/N) * hipotenusa (h=Ox)


         //Añadir v a la tabla de vértices (al final)
         vNoTapas.push_back({x,y,z});
      }
   }


   //2 Crear la tabla de triángulos---------------------------------------------------------------------
   int a,b,c;

   //Partimos de la tabla de triángulos vacía
   fNoTapas.clear();
   
   if(perfil_original.size() >= 2){
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
         for(int j=0; j <= perfil_original.size()-2; j++){  //Para cada j desde 0 hasta M − 2 (ambos incluidos)

            a = (perfil_original.size() * i) + j;     //Sea a = M i + j
            b = (perfil_original.size() * ((i+1)%num_instancias_perf)) + j;   //Sea b = M((i + 1) m´od N) + j

            fNoTapas.push_back({a, b+1, b});//Añadir triángulo formado por los índices a, b y b + 1.
            fNoTapas.push_back({a, a+1, b+1});//Añadir triángulo formado por los índices a, b + 1 y a + 1.
         }
      }
   }


  //HACER PERMANENTE LA TAPA SUPERIOR
  vNoTapas.push_back(norte); //Insertamos polo norte

  //TABLA DE TRIANGULOS TAPA SUPERIOR---------------------------------------------------------------------

  //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
  // el último vértice de cada instancia 
  //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
  for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
    //vNoTapas.size()-1 es el índice del polo norte
    a = vNoTapas.size() - 1;
    b = (perfil_original.size() * (i+1))-1;
    c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
    if( c == -1){
      c=(perfil_original.size() * num_instancias_perf ) - 1;
    }
    fNoTapas.push_back({a,c,b});//Añadir triángulo formado 
  }
   
  v.clear(); v= vNoTapas;
  f.clear(); f= fNoTapas;

  //3 Si es necesario crear las tapa inferior------------------------------------------------------------------

  //Si se requiere la tapa inferior
  if( tapa_inf){
    //3.1 Añadir el vértice del polo sur 
    //el polo sur (tendrá índice N)

    vTapas.clear();
    vTapas = vNoTapas;

    //El polo sur es una proyeccion de los vertices
    float zSur;

    zSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
    vTapas.push_back({0,0,zSur});//Insertamos la proyección del polo Sur
    
    //3.2 Añadir las caras correspondientes

    fTapas.clear();
    fTapas = fNoTapas;
    //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
    //polo sur con los N primeros vértices de cada instancia 
    //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
    for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
          //vTapas.size()-1 es el índice del polor sur PORQUE SOLO SE HA REQUERIDO ESTA TAPA
          a = vTapas.size() - 1 ;
          b = perfil_original.size() * i;
          c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
          fTapas.push_back({a,b,c});//Añadir triángulo formado 
    }

    v.clear(); v= vTapas;
    f.clear(); f= fTapas;

  }

   completarObjeto();
}