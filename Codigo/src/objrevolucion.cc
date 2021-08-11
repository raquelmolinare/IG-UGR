#include "auxiliar.h"
#include "objrevolucion.h"
#include <cmath>
#include <limits>
#include <algorithm>    // std::find

#define PI 3.141592 //Definimos PI


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


bool mycomparison (const Tupla3f first,const Tupla3f second){
    return ( first[1] <= second[1] );
}

bool menormayor(const std::vector<Tupla3f> & perfil){
   bool result=true;

   for(int i=0; i < perfil.size()-2 && result; i++){
      if( perfil[i][1] > perfil[i+1][1]){
         result=false;
      }
   }

   return result;

}

void ordenarPerfil(std::vector<Tupla3f> & perfil){

   std::vector<Tupla3f> vector;
   vector.clear();

   std::vector<Tupla3f> ::const_reverse_iterator it;

   for(it = perfil.crbegin(); it != perfil.crend(); ++it){
      vector.push_back(*it);
   }

   perfil.clear();
   perfil = vector;
   
}

/**
 * PRECONDICION: El vector perfil_original ya está ordenado segun el valor de y (de menor a mayor)
 */
void ObjRevolucion::gestionarPolos(std::vector<Tupla3f> & perfil_original, std::vector<Tupla3f> & polos){
   
   std::vector<Tupla3f> vectorPolos;
   vectorPolos.clear();

   //vector = perfil_original; 
   //Buscamos el polo norte y el porlo Sur
   if(perfil_original.size() > 0){
      //si el primer vertice esta en y => hay polo sur
      //if( perfil_original[0][0] == 0.0 && perfil_original[0][2] == 0.0){   //Si x=0 y z=0 entonces el vértice está en el eje y
      if( std::fabs(perfil_original[0][0]-0.0) < std::numeric_limits<double>::epsilon() && std::fabs(perfil_original[0][2]-0.0) < std::numeric_limits<double>::epsilon() ){ //Si x=0 y z=0 entonces el vértice está en el eje y
         vectorPolos.push_back(perfil_original[0]); //Insertamos el vertice en el vector de polos
         poloSur = true;
         perfil_original.erase(perfil_original.begin()); //Lo extraemos del perfil original
      }

      //Si el último vértice está en y => hay polo norte
      //if( perfil_original[perfil_original.size()-1][0] == 0.0 && perfil_original[perfil_original.size()-1][2] == 0.0){   //Si x=0 y z=0 entonces el vértice está en el eje y
      if( std::fabs(perfil_original[perfil_original.size()-1][0] - 0.0)< std::numeric_limits<double>::epsilon() && std::fabs(perfil_original[perfil_original.size()-1][2] - 0.0) < std::numeric_limits<double>::epsilon() ){
         vectorPolos.push_back(perfil_original[perfil_original.size()-1]); //Insertamos el vertice en el vector de polos
         poloNorte = true;
         perfil_original.pop_back(); //Lo extraemos del perfil original
      }
   }

   //Añadirmos los polos al vector de polos
   polos.clear(); polos = vectorPolos;
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje,bool conTextura ) {
   // completar ......(práctica 2)

   
   //1 Crear la tabla de vértices
   //1.1 Leemos los vértices del perfil original que esan en el archivo
   ply::read_vertices(archivo, this->vPerfilOriginal);

   crearMalla(vPerfilOriginal,num_instancias,tapa_sup, tapa_inf,eje,conTextura);

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf, char eje, bool conTextura) {

   crearMalla(perfil,num_instancias,tapa_sup, tapa_inf, eje,conTextura);
}


void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, char eje, bool conTextura){
   
   if(perfil_original.size() > 0 ){
      //Si el vector se ha ledido de mayor a menor y => Ordenar los vertices de menor a mayor y
      if( !menormayor(perfil_original) )
         ordenarPerfil(perfil_original);
      
      //Guardamos el perfil completo sin gestionar polos y ordenado
      vPerfilOComp = perfil_original;
      tamPerfilOriginal = perfil_original.size();
      numInstancias = num_instancias;

      //si hay vértices en los extremos situados en el eje Y (polo norte y polo sur),
      //extraemos y los dejamos aparte.
      gestionarPolos(perfil_original,vPolos);
   
      // Crear la malla
      if(eje == 'x')
         crearMallaFinalX(perfil_original,num_instancias, true, true);
      else if(eje == 'y')
         crearMallaFinalY(perfil_original,num_instancias, true, true);
      else
         crearMallaFinalZ(perfil_original,num_instancias, true, true);

      //Práctica 5 ---- TEXTURAS----------------------
      //Calcular coordenadas de textura si se requiere
      if(conTextura){
         instaciaExtraPerfil(true, true); //copiar el primer perfil al final 
         calcularCoordTextura();
         tieneCoordTexturas = true;
      }


      completarObjeto();

   }
}

void ObjRevolucion::crearMalla( std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf, char eje, bool conTextura) {
   
   if(perfil_original.size() > 0 ){
      //Si el vector se ha ledido de mayor a menor y => Ordenar los vertices de menor a mayor y
      if( !menormayor(perfil_original) )
         ordenarPerfil(perfil_original);
      
      //Guardamos el perfil completo sin gestionar polos y ordenado
      vPerfilOComp = perfil_original;
      tamPerfilOriginal = perfil_original.size();
      numInstancias = num_instancias_perf;

      //si hay vértices en los extremos situados en el eje Y (polo norte y polo sur),
      //extraemos y los dejamos aparte.
      gestionarPolos(perfil_original,vPolos);


      
      //Crear la malla
      if(eje == 'x')
         crearMallaFinalX(perfil_original,num_instancias_perf,tapa_sup, tapa_inf);
      else if(eje == 'y')
         crearMallaFinalY(perfil_original,num_instancias_perf,tapa_sup, tapa_inf);
      else
         crearMallaFinalZ(perfil_original,num_instancias_perf,tapa_sup, tapa_inf);

      //Práctica 5 ---- TEXTURAS----------------------
      //Calcular coordenadas de textura si se requiere
      if(conTextura){
         instaciaExtraPerfil( tapa_sup,tapa_inf); //copiar el primer perfil al final 
         calcularCoordTextura();
         tieneCoordTexturas = true;
      }


      completarObjeto();
         
      
   }
}


/**
 * PRECONDICION: El vector perfil_original ya está ordenado segun el valor de y (de menor a mayor)
 */
void ObjRevolucion::crearMallaFinalX( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf){
   int a,b,c;
      eje = 'x';
   //Si hay polos cambiar las coordenadas x e y
   if(vPolos.size() > 0){
      for(int i=0; i < vPolos.size(); i++){
         float x = vPolos[i][1];
         vPolos[i]={x,0,0};
      }
   }
   
   if(perfil_original.size() > 0 ){
   
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
      

      v.clear(); v= vNoTapas;
      f.clear(); f= fNoTapas;
   }

   //3 Si es necesario crear las tapas------------------------------------------------------------------

   //Si se requieren las dos tapas
   if( tapa_sup && tapa_inf){
      //3.1 Añadir los vértices en el polo norte y sur 
      //el polo sur (tendrá índice N) y en el polo norte (que tendrá índice N + 1)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original los polos son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( poloSur && poloNorte){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float xSur, xNorte;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            xSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({xSur,0,0});//Insertamos la proyección del polo Sur

            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

            xNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({xNorte,0,0});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float xSur, xNorte;

            xSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            xNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({xSur,0,0});//Insertamos el polo Sur
            vTapas.push_back({xNorte,0,0});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
      //polo sur con los N primeros vértices de cada instancia 
      //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-2 es el índice del polor sur
            a = vTapas.size() - 2 ;
            b = perfil_original.size() * i;
            c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
            fTapas.push_back({a,c,b});//Añadir triángulo formado 
      }

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,b,c});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }
   else if( !tapa_sup && tapa_inf ){ //Si se requiere solo la tapa inferior
      //3.1 Añadir el vértice en el polo sur 
      //el polo sur (tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original el polo son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float xSur;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            xSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({xSur,0,0});//Insertamos la proyección del polo Sur

         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float xSur;

            xSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            
            //Añadimos al vector de vértices(CON TAPAS) el polo Sur
            vTapas.push_back({xSur,0,0});//Insertamos el polo Sur

         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;
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
   else if (!tapa_inf && tapa_sup){ //Si se requiere solo la tapa superior
      //3.1 Añadir el vértice en el polo norte
      //el polo norte (que tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existe en el perfil original el polo norte tiene las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float xNorte;

         if(!poloSur){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            xNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({xNorte,0,0});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float xNorte;
            xNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({xNorte,0,0});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,b,c});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }

   //completarObjeto();

}

/**
 * PRECONDICION: El vector perfil_original ya está ordenado segun el valor de y (de menor a mayor)
 */
void ObjRevolucion::crearMallaFinalY( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf){
int a,b,c;
   eje = 'y';
   if(perfil_original.size() > 0 ){
   
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
      

      v.clear(); v= vNoTapas;
      f.clear(); f= fNoTapas;
   }

   //3 Si es necesario crear las tapas------------------------------------------------------------------

   //Si se requieren las dos tapas
   if( tapa_sup && tapa_inf){
      //3.1 Añadir los vértices en el polo norte y sur 
      //el polo sur (tendrá índice N) y en el polo norte (que tendrá índice N + 1)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original los polos son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( poloSur && poloNorte){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float ySur, yNorte;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            ySur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({0,ySur,0});//Insertamos la proyección del polo Sur

            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

            yNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({0,yNorte,0});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float ySur, yNorte;

            ySur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            yNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({0,ySur,0});//Insertamos el polo Sur
            vTapas.push_back({0,yNorte,0});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
      //polo sur con los N primeros vértices de cada instancia 
      //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-2 es el índice del polor sur
            a = vTapas.size() - 2 ;
            b = perfil_original.size() * i;
            c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
            fTapas.push_back({a,b,c});//Añadir triángulo formado 
      }

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,c,b});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }
   else if( !tapa_sup && tapa_inf){ //Si se requiere solo la tapa inferior
      //3.1 Añadir el vértice en el polo sur 
      //el polo sur (tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original el polo son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float ySur;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            ySur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({0,ySur,0});//Insertamos la proyección del polo Sur

         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float ySur;

            ySur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            
            //Añadimos al vector de vértices(CON TAPAS) el polo Sur
            vTapas.push_back({0,ySur,0});//Insertamos el polo Sur

         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;
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
   else if( !tapa_inf && tapa_sup){ //Si se requiere solo la tapa superior
      //3.1 Añadir el vértice en el polo norte
      //el polo norte (que tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existe en el perfil original el polo norte tiene las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float yNorte;

         if(!poloSur){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            yNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({0,yNorte,0});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float yNorte;
            yNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({0,yNorte,0});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,c,b});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }

   //completarObjeto();

}

/**
 * PRECONDICION: El vector perfil_original ya está ordenado segun el valor de y (de menor a mayor)
 */
void ObjRevolucion::crearMallaFinalZ( const std :: vector < Tupla3f > & perfil_original, const int num_instancias_perf, bool tapa_sup, bool tapa_inf){
   int a,b,c;
   eje = 'z';
   //Si hay polos cambiar las coordenadas z e y
   if(vPolos.size() > 0){
      for(int i=0; i < vPolos.size(); i++){
         float z = vPolos[i][1];
         vPolos[i]={0,0,z};
      }
   }
   
   if(perfil_original.size() > 0 ){
   
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
      

      v.clear(); v= vNoTapas;
      f.clear(); f= fNoTapas;
   }

   //3 Si es necesario crear las tapas------------------------------------------------------------------

   //Si se requieren las dos tapas
   if( tapa_sup && tapa_inf){
      //3.1 Añadir los vértices en el polo norte y sur 
      //el polo sur (tendrá índice N) y en el polo norte (que tendrá índice N + 1)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original los polos son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( poloSur && poloNorte){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float zSur, zNorte;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            zSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({0,0,zSur});//Insertamos la proyección del polo Sur

            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

            zNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({0,0,zNorte});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float zSur, zNorte;

            zSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            zNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({0,0,zSur});//Insertamos el polo Sur
            vTapas.push_back({0,0,zNorte});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      //insertar los N triángulos en la tapa inferior, que conectan el vértice en el
      //polo sur con los N primeros vértices de cada instancia 
      //(el primer vértice de la i-ésima instancia tiene índice Mi, para i desde cero hasta N −1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-2 es el índice del polor sur
            a = vTapas.size() - 2 ;
            b = perfil_original.size() * i;
            c = (perfil_original.size() * ((i+1)%num_instancias_perf));   //Sea c = M ((i + 1) mod N)
            fTapas.push_back({a,b,c});//Añadir triángulo formado 
      }

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,c,b});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }
   else if( !tapa_sup && tapa_inf){ //Si se requiere solo la tapa inferior
      //3.1 Añadir el vértice en el polo sur 
      //el polo sur (tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existen en el perfil original el polo son las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[0]); //Insertamos polo sur
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float zSur;

         if(!poloSur){ //Si no hay polo sur hay que proyectarlo
            zSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            vTapas.push_back({0,0,zSur});//Insertamos la proyección del polo Sur

         }

         if(!poloNorte){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Sur

         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float zSur;

            zSur = perfil_original[0][1]; //perfil_original[0][1] es el vértice con un valor de Y menor
            
            //Añadimos al vector de vértices(CON TAPAS) el polo Sur
            vTapas.push_back({0,0,zSur});//Insertamos el polo Sur

         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;
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
   else if( !tapa_inf && tapa_sup){ //Si se requiere solo la tapa superior
      //3.1 Añadir el vértice en el polo norte
      //el polo norte (que tendrá índice N)

      vTapas.clear();
      vTapas = vNoTapas;

      //Si existe en el perfil original el polo norte tiene las coordenadas originales
      //Si no entonces son una proyección de los vértices extremos sobre el eje de rotación
      if( vPolos.size() == 2){   //Hay coordenadas para las dos tapas
         vTapas.push_back(vPolos[1]); //Insertamos polo norte
      }
      else if( vPolos.size() == 1){ //Hay coordenadas solo para un polo
         float zNorte;

         if(!poloSur){
            vTapas.push_back(vPolos[0]); //Isertamos el polo Norte
         }

         if(!poloNorte){
            zNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor
            vTapas.push_back({0,0,zNorte});//Insertamos la proyección del polo Norte
         }

      }
      else{ //No hay vértices en el ejer Y
         if( perfil_original.size() > 0){
            float zNorte;
            zNorte = perfil_original[perfil_original.size()-1][1]; //perfil_original[perfil_original.size()-1][1] es el vértice con un valor de Y mayor

            //Añadimos al vector de vértices(CON TAPAS) el polo Sur y el polo Norte
            vTapas.push_back({0,0,zNorte});//Insertamos el polo Norte
         }
      }

      //3.2 Añadir las caras correspondientes

      fTapas.clear();
      fTapas = fNoTapas;
      int c;

      //insertar los triángulos de la tapa superior, que conectan el vértice en el polo norte con
      // el último vértice de cada instancia 
      //(el último vértice de la i-ésima instancia tiene como índice M(i + 1) − 1, de nuevo con i entre 0 y N − 1)
      for(int i=0; i <= num_instancias_perf-1; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
            //vTapas.size()-1 es el índice del polor norte
            a = vTapas.size() - 1;
            b = (perfil_original.size() * (i+1))-1;
            c = ((perfil_original.size() * ( (i+2)%num_instancias_perf) ) - 1);    //Sea c = M ((i + 2) mod N)
            if( c == -1){
               c=(perfil_original.size() * num_instancias_perf ) - 1;
            }
            fTapas.push_back({a,c,b});//Añadir triángulo formado 

      }

      v.clear(); v= vTapas;
      f.clear(); f= fTapas;

   }

   //completarObjeto();
}


void ObjRevolucion::completarObjeto(){

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
   colorPunt.clear(); colorPunt.resize(v.size()); // tabla de color Modo puntos (ROJO)
   colorPunt.insert( colorPunt.begin(), v.size(), {255.0,0.0,0.0} );

   colorLin.clear();  colorLin.resize(v.size()); // tabla de color Modo Lineas (NEGRO)
   colorLin.insert( colorLin.begin(), v.size(), {0.0,0.0,0.0} );

   colorSol.clear(); colorSol.resize(v.size()); // tabla de color Modo Solido (MAGENTA)
   colorSol.insert( colorSol.begin(), v.size(),  {255.0,0.0,255.0} );

   colorFPar.clear(); colorFPar.resize(v.size()); // tabla de color Modo Ajedrez caras pares (ROJO)
   colorFPar.insert( colorFPar.begin(), v.size(), {255.0,0.0,0.0} );

   colorFImpar.clear(); colorFImpar.resize(v.size());// tabla de color Modo Ajedrez caras impares (VERDE)
   colorFImpar.insert( colorFImpar.begin(), v.size(), {0.0,255.0,0.0} );

   colorSeleccionado.clear(); colorSeleccionado.resize(v.size());// tabla de color Modo Sleccion (AMARIILO)
   colorSeleccionado.insert( colorSeleccionado.begin(), v.size(), {255.0,255.0,0.0} );

   colorSeleccionable.clear(); colorSeleccionable.resize(v.size());// tabla de color Modo Sleccion (AMARIILO)
   colorSeleccionable.insert( colorSeleccionable.begin(), v.size(), {255.0,255.0,0.0} );

   colorFParSeleccionado.clear(); // tabla de color Modo Ajedrez caras pares cuando esta seleccionado (AMARILLO)
   colorFParSeleccionado.insert( colorFParSeleccionado.begin(), v.size(), {255.0,255.0,0.0} );

   colorFImparSeleccionado.clear();// tabla de color Modo Ajedrez caras impares cuando esta seleccionado  (NEGRO)
   colorFImparSeleccionado.insert( colorFImparSeleccionado.begin(), v.size(), {0.0,0.0,0.0} );


   //Indicar el tamaño e los vectores de caras impares y pares con o sin tapa necesario para el offset del drawelements

   int parTapaSize=0, imparTapaSize=0, parNoTapaSize=0, imparNoTapaSize=0;

   //CARAS SIN TAPA
   for(int i=0; i < fNoTapas.size(); i++){
      if(i%2 == 0){ //Si es una cara par
         parNoTapaSize++;
      }
      else{ //Si es una cara impar
         imparNoTapaSize++; 
      }
   }

   //CARAS CON TAPA
   parTapaSize = fPar.size();
   imparTapaSize = fImpar.size();

   //{fTapas.size(), fparTapas.size(), fimparTapas.size()}
   sizeTapas.clear();
   sizeTapas.resize(3);
   sizeTapas[0] = f.size();
   sizeTapas[1] = parTapaSize;
   sizeTapas[2] = imparTapaSize;
   

   //{fNoTapas.size(), fparNoTapas.size(), fimparNoTapas.size()}
   sizeNoTapas.clear();
   sizeNoTapas.resize(3);
   sizeNoTapas[0] = fNoTapas.size();
   sizeNoTapas[1] = parNoTapaSize;
   sizeNoTapas[2] = imparNoTapaSize;


   //Tabla de normales
   calcular_normales();

   //Material por defecto
   Material mEsmeralda({ 0.0215, 0.1745, 0.0215, 0.55 },{0.633, 0.727811, 0.633, 0.55 },{0.07568, 0.61424, 0.07568, 0.55 },76.8) ;

   m = mEsmeralda;

   Material mAmarillo({0.329412, 0.223529, 0.027451,1.0},{ 0.992157, 0.941176, 0.807843, 1.0},{0.780392, 0.568627, 0.113725, 1.0},80.0);
   mSeleccion =mAmarillo;
}

//Practica 5: Texturas
//método  para crear una instancia extra del perfil, que coincidirá en coordenadas geométricas con la instancia 0 pero tendrá diferentes coordenadas de textura
void ObjRevolucion::instaciaExtraPerfil(bool tapa_sup, bool tapa_inf){

   //cout << "ANTES..v =  " << v.size() << "..f " << f.size() << endl << endl;

   //Extraer vertices y caras relacionados con las tapas
   std::vector<Tupla3f> auxv;
   for(int i=vNoTapas.size(); i < vTapas.size(); i++){
      auxv.push_back(v[i]);   
   }
   v = vNoTapas;

   std::vector<Tupla3i> auxf;
   for(int i=fNoTapas.size(); i < fTapas.size(); i++){
      auxf.push_back(f[i]);   
   }
   f = fNoTapas;


   //--VERTICES--
   //Añadimos los vertices del perfil extra
   for(int j=0; j < vPerfilOriginal.size(); j++){  //Para cada j desde 0 hasta M − 1 (ambos incluidos)
      v.push_back(v[j]);   
   }
   vNoTapas = v;


   //--CARAS--
   //Añadimos TODAS las caras (sin tapas)
   //Partimos de la tabla de triángulos vacía
   fNoTapas.clear();
   int a,b,c,N;
      
   if(vPerfilOriginal.size() >= 2){
      for(int i=0; i < numInstancias; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)
         for(int j=0; j <= vPerfilOriginal.size()-2; j++){  //Para cada j desde 0 hasta M − 2 (ambos incluidos)
            a = (vPerfilOriginal.size() * i) + j;     //Sea a = M i + j
            N = vPerfilOriginal.size()*(numInstancias+1);
            b = ((vPerfilOriginal.size() * (i+1))%N) + j;   //Sea b = M((i + 1) m´od N) + j
            fNoTapas.push_back({a, b+1, b});//Añadir triángulo formado por los índices a, b y b + 1.
            fNoTapas.push_back({a, a+1, b+1});//Añadir triángulo formado por los índices a, b + 1 y a + 1.
         }
      }
   }
   f=fNoTapas;

   
   

   //GESTION TAPAS------------------------------------
   //--VERTICES--
   //Añadimos los vertices asociados a las tapas = polos
   for(int i=0; i < auxv.size(); i++){
      v.push_back(auxv[i]);   
   }

   vTapas = v;

   //--CARAS--
   fTapas = f;
   //Añadimos las caras asociadas a las tapas de TODAS las instancias del perfil
   if(tapa_inf && tapa_sup){

      //Tapa inferior
      for(int i=0; i < numInstancias; i++){  //Para cada i desde 0 hasta N (ambos incluidos)
            //v.size()-2 es el índice del polor sur
            a = v.size() - 2 ;
            b = vPerfilOriginal.size() * i;
            N = vPerfilOriginal.size()*(numInstancias+1);
            c = ((vPerfilOriginal.size() * (i+1))%N);   //Sea c = M ((i + 1) mod N)
            fTapas.push_back({a,b,c});//Añadir triángulo formado 
      }

      //Tapa Superior
      for(int i=0; i < numInstancias; i++){  //Para cada i desde 0 hasta N-1 (ambos incluidos)
            //v.size()-1 es el índice del polor norte
            a = v.size() - 1 ;
            b = (vPerfilOriginal.size() * (i+1))-1;
            N = vPerfilOriginal.size()*(numInstancias+1);
            c = ((vPerfilOriginal.size() * (i+2))%N )-1;   //Sea c = M ((i + 1) mod N)
            if( c == -1)
               c=(vPerfilOriginal.size() * (numInstancias+1) ) - 1;

            fTapas.push_back({a,c,b});//Añadir triángulo formado 
      }
      
   }
   else if(!tapa_sup && tapa_inf){

      //Tapa inferior
      for(int i=0; i < numInstancias; i++){  //Para cada i desde 0 hasta N-1 (ambos incluidos)
            //v.size()-1 es el índice del polor sur
            a = v.size() - 1 ;
            b = vPerfilOriginal.size() * i;
            N = vPerfilOriginal.size()*(numInstancias+1);
            c = ((vPerfilOriginal.size() * (i+1))%N);   //Sea c = M ((i + 1) mod N)
            fTapas.push_back({a,b,c});//Añadir triángulo formado 
      }

   }
   else if(!tapa_inf && tapa_sup){

      //Tapa Superior
      for(int i=0; i < numInstancias; i++){  //Para cada i desde 0 hasta N-1 (ambos incluidos)
            //v.size()-1 es el índice del polor norte
            a = v.size() - 1 ;
            b = (vPerfilOriginal.size() * (i+1))-1;
            N = vPerfilOriginal.size()*(numInstancias+1);
            c = ((vPerfilOriginal.size() * (i+2))%N )-1;   //Sea c = M ((i + 1) mod N)
            if( c == -1)
               c=(vPerfilOriginal.size() * (numInstancias+1) ) - 1;

            fTapas.push_back({a,c,b});//Añadir triángulo formado 
      }

   }

   f= fTapas;

   

   
}

//método que calcula las coordenadas de textura para cada uno de los vértices y lo almacena en su tabla ct
void ObjRevolucion::calcularCoordTextura(){

   int N = numInstancias+1;

   //Si (coord. X, entre 0 y 1) = i/(N − 1) -- si va desde 0 --> primer perfil hasta 1--> último perfil
   //Tj (coord. Y, entre 0 y 1) = dj/d(M−1) -- Su valor es proporcional a la distancia dj entre el primer vertice del perfil y dicho vertice j -- 
         //Distancias-- d0 = 0 y d(j+1) = dj + || p(j+1) − pj||
   float Si, Tj;

   //Para el perfil i=0 vertice j=0: Si=0 Tj=0
   ct.clear();
  
   //Distancias
   std::vector<float> distancias; distancias.clear(); 
   distancias.push_back(0.0);
   for(int j=0; j < vPerfilOriginal.size()-1; j++){
      float d = distancias[j]  + sqrt( pow( (vPerfilOriginal[j+1][0]-vPerfilOriginal[j][0]) , 2) + pow( (vPerfilOriginal[j+1][1]-vPerfilOriginal[j][1]) , 2) + pow( (vPerfilOriginal[j+1][2]-vPerfilOriginal[j][2]) , 2) );
      distancias.push_back(d);
   }


   //Calcular coordenadas Si y Tj
   for(int i=0; i < N; i++){
      Si = 1- ((i)/((float)N-1.0)); // La coordenada S (coordenada X en el espacio de la textura) es común a todos los vértices en una instancia del perfil
      for(int j=0; j < vPerfilOriginal.size(); j++){
         Tj = 1- (distancias[j]/distancias[vPerfilOriginal.size()-1]);
         ct.push_back( {Si,Tj} );
      }
   }


}


//Metodo para asignar una textura-----------------------------------------------------------------------------
void ObjRevolucion::setTextura(string archivo){
   textura = new Textura(archivo);
   //Asignamos el color blanco al objeto
   setColor({255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0});
   Material mBlanco({ 0.25,0.25,0.25,1.0 }, { 1.0,1.0,1.0,1.0}, { 1.0,1.0,1.0,1.0}, 100.0); 
   setMaterial(mBlanco);

}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::draw(std::bitset<10> vision, bool seleccionado)
{
   // completar .....(práctica 1)
   bool inmediato=false;

   //Comprobamos los modos
   
   //-------MODO DE DIBUJADO---------------------------
   if(vision.test(4)){
      //Si esta activado el bit 4 es porque se dibuja en modo inmediato
      //por lo que ponemos inmediato a true
      inmediato=true;
     
   }
   
   ///-------MODO DE VISUALIZACIÓN---------------------------
   //--MODO AJEDREZ------
   if(vision.test(0)){   
      //Si esta activado el modo Ajedrez (bit 0) entonces llamamos a drawAjedrez
      drawAjedrez(inmediato,vision,seleccionado);
   }

   else{
      //--MODO PUNTOS LINEAS SOLDO-----
      if(inmediato){
         if(vision.test(5))
            draw_ModoInmediato(false, vision,sizeTapas,seleccionado);
         else
            draw_ModoInmediato(false, vision,sizeNoTapas,seleccionado);

      }
      else{
         if(vision.test(5))
            draw_ModoDiferido(false, vision,sizeTapas,seleccionado);
         else
            draw_ModoDiferido(false, vision,sizeNoTapas,seleccionado);
      }
   }

}


// -----------------------------------------------------------------------------
// Función de visualización de la malla PARA EL MODO AJEDREZ,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjRevolucion::drawAjedrez(bool inmediato, std::bitset<10> vision, bool seleccionado)
{

   glPolygonMode(GL_FRONT, GL_FILL); // Cara delantera rellena

   //Llamamos al modo de dibujado elegido indicando por el parámetro
   if(inmediato)
      if(vision.test(5))
         draw_ModoInmediato(true, vision, sizeTapas, seleccionado);
      else
         draw_ModoInmediato(true, vision, sizeNoTapas,seleccionado);

   else 
      if(vision.test(5))
         draw_ModoDiferido(true, vision, sizeTapas,seleccionado);
      else
         draw_ModoDiferido(true, vision, sizeNoTapas,seleccionado);


}