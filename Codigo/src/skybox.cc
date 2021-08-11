#include "auxiliar.h"
#include "skybox.h"

#define PI 3.141592 //Definimos PI



SkyBox::SkyBox(string imagen,float r)
{

    radio = r;
    numInstancias = 50;
    numVertPerfil = 50;

    crearSemiesfera();

    //Tabla de normales
   calcular_normales();

   coordTexturas();


    //Material por defecto
    Material mBlanco({ 0.25,0.25,0.25,1.0 }, { 0.0,0.0,0.0,0.0}, { 1.0,1.0,1.0,1.0}, 80.0); 
    m = mBlanco;

    //Tablas de colores
    setColor({255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0},{255.0,255.0,255.0});

    textura = new Textura(imagen);

}



void SkyBox::crearSemiesfera(){

    int num_vert_perfil = numVertPerfil;
    int num_instancias_perf = numInstancias;

    float x,y,z;

    std::vector<Tupla3f> vector; vector.clear();


    for(int i=1; i < num_vert_perfil; i++){ 
        x = radio * cos((PI*i)/(num_vert_perfil*2));
        y = radio * sin((PI*i)/(num_vert_perfil*2));
        vector.push_back({x,y,0});
    }

    vPerfil.push_back({0,-radio,0}); //incluimos el polo sur

    for(int i=1; i < num_vert_perfil; i++){ //incluimos la parte negativa (y)
        x = vector[vector.size()-i][0];
        y = vector[vector.size()-i][1];
        vPerfil.push_back({x,-y,0}); //incluimos el polo sur
    }

    vPerfil.push_back({radio,0,0});

    for(int i=0; i < num_vert_perfil-1; i++){ //incluimos la parte positiva (y)
        x = vector[i][0];
        y = vector[i][1];
        vPerfil.push_back({x,y,0}); //incluimos el polo sur
    }

    //ordenar perfil
    vector.clear();

    std::vector<Tupla3f> ::const_reverse_iterator it;

    for(it = vPerfil.crbegin(); it != vPerfil.crend(); ++it){
        vector.push_back(*it);
    }

    vPerfil.clear();
    vPerfil = vector;

    // for(int j=0; j < vPerfil.size(); j++){
    //  cout << "------"<<j<<"--:" << vPerfil[j] << endl;
    // }

    // vPerfil.push_back({0,radio,0}); //incluimos el polo norte

    //Crear la malla
    
    int a,b,c;
    //1 Crear la tabla de vértices------------------------------------------------------------------------
    //Partimos de la tabla de vértices vacía.

    for(int i=0; i <= num_instancias_perf-1; i++){       //Para cada i desde 0 hasta N − 1 (ambos incluidos)
        for(int j=0; j <= vPerfil.size()-1; j++){  //Para cada j desde 0 hasta M − 1 (ambos incluidos)
        //Sea v vértice obtenido rotando j un ángulo igual a 2πi/N radianes.
        x = cos(PI*i/num_instancias_perf)*vPerfil[j][0];  //La coordenada x de O' = cos(2*pi*i/N) * hipotenusa (h=Ox)
        y = vPerfil[j][1];                                  //La coordenada y de O' = Oy
        z = sin(PI*i/num_instancias_perf)*vPerfil[j][0];  //La coordenada z de O' = sin(2*pi*i/N) * hipotenusa (h=Ox)

        //Añadir v a la tabla de vértices (al final)
        v.push_back({x,y,z});
        }
    }

    //2 Crear la tabla de triángulos---------------------------------------------------------------------

    //Partimos de la tabla de triángulos vacía
    f.clear();
    
    for(int i=0; i <= num_instancias_perf-2; i++){  //Para cada i desde 0 hasta N − 1 (ambos incluidos)

        for(int j=0; j <= vPerfil.size()-2; j++){  //Para cada j desde 0 hasta M − 2 (ambos incluidos)
            a = (vPerfil.size() * i) + j;     //Sea a = M i + j
            b = (vPerfil.size() * ((i+1)%num_instancias_perf)) + j;   //Sea b = M((i + 1) m´od N) + j

            f.push_back({a,b+1, b});//Añadir triángulo formado por los índices a, b y b + 1.
            f.push_back({a,a+1,b+1});//Añadir triángulo formado por los índices a, b + 1 y a + 1.
        }
    }

    
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

    //ROTACION incremento GRADOS EN X
    for(int i=0; i < v.size(); i++){
        x = v[i][0];
        y = (v[i][1] * cos((-90.0*PI)/180.0)) + (v[i][2] * -sin((-90.0*PI)/180.0));
        z = (v[i][1] * sin((-90.0*PI)/180.0)) + (v[i][2] * cos((-90.0*PI)/180.0)) ;

        v[i][0]=x;
        v[i][1]=y;
        v[i][2]=z;
   }

    
}

void SkyBox::coordTexturas(){

    int N = numInstancias;

   //Si (coord. X, entre 0 y 1) = i/(N − 1) -- si va desde 0 --> primer perfil hasta 1--> último perfil
   //Tj (coord. Y, entre 0 y 1) = dj/d(M−1) -- Su valor es proporcional a la distancia dj entre el primer vertice del perfil y dicho vertice j -- 
         //Distancias-- d0 = 0 y d(j+1) = dj + || p(j+1) − pj||
   float Si, Tj;

   //Para el perfil i=0 vertice j=0: Si=0 Tj=0
   ct.clear();
  
   //Distancias
   std::vector<float> distancias; distancias.clear(); 
   distancias.push_back(0.0);
   for(int j=0; j < vPerfil.size(); j++){
      //float d = distancias[j]  + sqrt( (vPerfilOComp[j+1]-vPerfilOComp[j]).lengthSq() );
      float d = distancias[j]  + sqrt( pow( (vPerfil[j+1][0]-vPerfil[j][0]) , 2) + pow( (vPerfil[j+1][1]-vPerfil[j][1]) , 2) + pow( (vPerfil[j+1][2]-vPerfil[j][2]) , 2) );
      distancias.push_back(d);
   }


    float ymax,ymin;
    ymax = radio;
    ymax = -radio;

   //Calcular coordenadas Si y Tj
   for(int i=0; i < N; i++){
      Si = 1.0- ((i)/((float)N-1.0)); // La coordenada S (coordenada X en el espacio de la textura) es común a todos los vértices en una instancia del perfil
      for(int j=0; j < vPerfil.size(); j++){
        Tj = 1.0- (distancias[j]/distancias[vPerfil.size()-1]);
        ct.push_back( {Si,Tj} );
      }
   }

//    for(int j=0; j < ct.size(); j++){
//      cout << "-- "<<j<<"--:" << ct[j] << endl;
//    }
}