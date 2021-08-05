#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************


//Crear VBO, devuelve el identificador
GLuint Malla3D::CrearVBO( GLuint tipo_vbo , GLuint tamanio_bytes , GLvoid * puntero_ram )
{
   GLuint id_vbo ; // resultado: identificador de VBO
   glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );

   glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
   return id_vbo ; // devolver el identificador resultado
}


// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato(bool modoAjedrez, std::bitset<10> vision, std::vector<int> tamanios,bool seleccionado)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...

   //--ES SELCCIONABLE------
   if(vision.test(9)){

      bool flagLuz;

      if(glIsEnabled(GL_LIGHTING) == GL_TRUE) //Si las luces estan encedidas
         flagLuz = true;
      else
         flagLuz = false;

      glDisable ( GL_LIGHTING ); // deshabilita la luz

      glLineWidth(1.0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Ambas caras en alambres

      //COLORES---------------------------------------------------------
      glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores

      glColorPointer( 3, GL_FLOAT,  0, colorSeleccionable.data()); //Seleccionamos el vector de colores

      //VERTICES--------------------------------------------------------------------
      glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
      glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices

      glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
      glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
      glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores

      //Habilitar los flags que sean necesarios
      if(flagLuz) //Si las luces estaban encedidas
         glEnable( GL_LIGHTING ); // habilita la luz
   }

   //--MODO SELECCION------
   if(vision.test(8)){

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

      //COLORES---------------------------------------------------------
      glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores
      glColorPointer( 3, GL_FLOAT,  0, colorModoSeleccion.data()); //Seleccionamos el vector de colores


      //VERTICES--------------------------------------------------------------------
      glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
      glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices

      glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
      glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
      glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores
   }
   else{ //Si esta desactivado el bit del modo seleccion entonces se tienen en cuenta las texturaas

      //----TEXTURAS----------------------------------------------------------
      if( (textura!=nullptr && !ct.empty()) && !seleccionado){ //Si existen coordenadas de tectura y por lo tanto ct no está vacío
         textura->activar();
         
         glTexCoordPointer ( 2 , GL_FLOAT , 0 , ct.data() ); //indicar el formato y la dirección de memoria del array de coordenadas de textura
         glEnableClientState ( GL_TEXTURE_COORD_ARRAY ); // habilitar tabla de coordenadas de textura
         

      }
      else if(textura!=nullptr && !seleccionado )
      { 
         textura->activar();
         glEnable(GL_TEXTURE_GEN_S);
         glEnable(GL_TEXTURE_GEN_T);

         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
         glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
         
      }
   

      //----LUCES----------------------------------------------------------
      if( vision.test(6) ){ //Si esta activado el bit 6 entonces trabajamos con materiales Y DESACTIVADO EL MODO SELECCION

         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

         if( vision.test(7) ) //Si esta activo el modo suave
            glShadeModel(GL_SMOOTH);
         else //Si esta desactivado el modo suave entonces se pinta en modo plano
            glShadeModel(GL_FLAT);

         //MATERIALES---------------------------------------------------------

         if(seleccionado){ //Si está selccionado
            mSeleccion.aplicar();
         }
         else{
            m.aplicar();
         }


         //VERTICES y NORMALES DE VERTICES------------------------------------
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
         glEnableClientState ( GL_NORMAL_ARRAY ); // habilitar uso de un array de normales

         glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices
         glNormalPointer ( GL_FLOAT , 0 , nv.data() );// indicar el formato y la dirección de memoria del array de normales

         glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
         glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
         glDisableClientState ( GL_NORMAL_ARRAY  );// deshabilitar array de normales

      }
      else if(modoAjedrez){ //----MODO AJEDREZ----------------------------------------------------------
         
         glPolygonMode(GL_FRONT, GL_FILL); // Cara delantera rellena
      

         //-----CARAS PARES------------------------------------------------
         //COLORES---------------------------------------------------------
         glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores
         glColorPointer( 3, GL_FLOAT, 0, colorFPar.data()); //Seleccionamos el vector de colores
         
         //VERTICES--------------------------------------------------------
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices   
         glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() ); // indicar el formato y la dirección de memoria del array de vértices

         glDrawElements ( GL_TRIANGLES , tamanios[1]*3 , GL_UNSIGNED_INT , fPar.data() );// visualizar
         glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
         glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores


         //-----CARAS IMPARES------------------------------------------------
         //COLORES---------------------------------------------------------
         glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores
         if(seleccionado) //Si está selccionado
            glColorPointer( 3, GL_FLOAT,  0, colorSeleccionado.data()); //Seleccionamos el vector de colores
         else
            glColorPointer( 3, GL_FLOAT, 0, colorFImpar.data()); //Seleccionamos el vector de colores

         //VERTICES--------------------------------------------------------
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
         glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() ); // indicar el formato y la dirección de memoria del array de vértices

         glDrawElements ( GL_TRIANGLES , tamanios[2]*3 , GL_UNSIGNED_INT , fImpar.data() );// visualizar
         glDisableClientState ( GL_VERTEX_ARRAY ); // deshabilitar array de vértices
         glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores

      }
      else{ //----MODO NORMAL----------------------------------------------------------


         //--MODO PUNTOS------
         if(vision.test(3)){
            //Si esta activado el modo Puntos(bit 3) entonces usamos colorPunt

            glPointSize(5.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Cara delantera solo puntos

            //COLORES---------------------------------------------------------
            glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores

            if(seleccionado) //Si está selccionado
               glColorPointer( 3, GL_FLOAT,  0, colorSeleccionado.data()); //Seleccionamos el vector de colores
            else
               glColorPointer( 3, GL_FLOAT,  0, colorPunt.data()); //Seleccionamos el vector de colores


            //VERTICES--------------------------------------------------------------------
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices

            glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
            glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
            glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores
         }

         //--MODO LINEAS------
         if(vision.test(2)){
            //Si esta activado el modo Lineas(bit 2) entonces usamos colorLin
            glLineWidth(2.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Ambas caras en alambres

            //COLORES---------------------------------------------------------
            glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores

            if(seleccionado) //Si está selccionado
               glColorPointer( 3, GL_FLOAT,  0, colorSeleccionado.data()); //Seleccionamos el vector de colores
            else
               glColorPointer( 3, GL_FLOAT,  0, colorLin.data()); //Seleccionamos el vector de colores


            //VERTICES--------------------------------------------------------------------
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices

            glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
            glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
            glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores
         }

         //--MODO SOLIDO------
         if(vision.test(1)){
            //Si esta activado el modo Solido (bit 1) entonces usamos colorSol

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

            //COLORES---------------------------------------------------------
            glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de colores
            
            if(seleccionado) //Si está selccionado
               glColorPointer( 3, GL_FLOAT,  0, colorSeleccionado.data()); //Seleccionamos el vector de colores
            else
               glColorPointer( 3, GL_FLOAT,  0, colorSol.data()); //Seleccionamos el vector de colores


            //VERTICES--------------------------------------------------------------------
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar uso de un array de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , v.data() );// indicar el formato y la dirección de memoria del array de vértices

            glDrawElements ( GL_TRIANGLES , tamanios[0]*3 , GL_UNSIGNED_INT , f.data() );// visualizar
            glDisableClientState ( GL_VERTEX_ARRAY );// deshabilitar array de vértices
            glDisableClientState ( GL_COLOR_ARRAY  );// deshabilitar array de colores
         }


      }
      glDisableClientState( GL_TEXTURE_COORD_ARRAY );
      glDisable(GL_TEXTURE_2D);

   }
   
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool modoAjedrez, std::bitset<10> vision, std::vector<int> tamanios, bool seleccionado)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   //--MODO SELECCIONABLE----------------------------------------------------------
   if( vision.test(9)){

      bool flagLuz;

      if(glIsEnabled(GL_LIGHTING) == GL_TRUE) //Si las luces estan encedidas
         flagLuz = true;
      else
         flagLuz = false;

      glDisable ( GL_LIGHTING ); // deshabilita la luz

      glLineWidth(1.0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Ambas caras en alambres

      //COLORES---------------------------------------------------------

      if(id_vbo_colorSeleccionable == 0) id_vbo_colorSeleccionable = CrearVBO( GL_ARRAY_BUFFER , colorSeleccionable.size()*3*sizeof(float), colorSeleccionable.data());//TABLA DE COLORES

      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorSeleccionable); // activar VBO de colores
      glColorPointer( 3, GL_FLOAT, 0, 0);
      glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
      glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores

      //VERTICES--------------------------------------------------------
      //especificar localización y formato de la tabla de vértices, habilitar tabla
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
      glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
      glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

      
      // visualizar triángulos con glDrawElements (puntero a tabla == 0)
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
      glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
      
      // desactivar uso de array de colores y de vértices
      glDisableClientState ( GL_COLOR_ARRAY );
      glDisableClientState ( GL_VERTEX_ARRAY );

      //Habilitar los flags que sean necesarios
      if(flagLuz) //Si las luces estaban encedidas
         glEnable( GL_LIGHTING ); // habilita la luz

   }

   //--MODO SELECCION----------------------------------------------------------
   if( vision.test(8)){
      
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

      if(id_vbo_colorModoSeleccion == 0) id_vbo_colorModoSeleccion = CrearVBO( GL_ARRAY_BUFFER , colorModoSeleccion.size()*3*sizeof(float), colorModoSeleccion.data());//TABLA DE COLORES

      //COLORES---------------------------------------------------------
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorModoSeleccion); // activar VBO de colores
      glColorPointer( 3, GL_FLOAT, 0, 0);
      glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
      glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            

      //VERTICES--------------------------------------------------------
      //especificar localización y formato de la tabla de vértices, habilitar tabla
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
      glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
      glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

      
      // visualizar triángulos con glDrawElements (puntero a tabla == 0)
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
      glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
      
      // desactivar uso de array de colores y de vértices
      glDisableClientState ( GL_COLOR_ARRAY );
      glDisableClientState ( GL_VERTEX_ARRAY );

   }
   else{ //Si esta desactivado el bit del modo seleccion entonces se tienen en cuenta las texturaas

      //----TEXTURAS----------------------------------------------------------
      if( (textura!=nullptr && !ct.empty()) && !seleccionado){ //Si existen coordenadas de tectura y por lo tanto ct no está vacío

         textura->activar();      
         if(id_vbo_ct == 0) id_vbo_ct = CrearVBO( GL_ARRAY_BUFFER , ct.size()*2*sizeof(float), ct.data());  //TABLA DE COORDENADAS DE TEXTURAS

         glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ct ); // activar VBO de coordenadas de textura
         glTexCoordPointer(2,GL_FLOAT,0,0); // especifica formato y offset (=0) COORDENADAS DE TEXTURA
         glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
         glEnableClientState ( GL_TEXTURE_COORD_ARRAY ); // habilitar tabla de coordenadas de textura

      }
      else if(textura!=nullptr && !seleccionado)
      { 
         textura->activar();
         glEnable(GL_TEXTURE_GEN_S);
         glEnable(GL_TEXTURE_GEN_T);

         glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
         glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
         
      }
   
   

      //----LUCES----------------------------------------------------------
      if( vision.test(6) ){ //Si esta activado el bit 6 entonces trabajamos con materiales

         //identificar si los identificadires de los VBOs son 0
         //si lo son, entonces invocar a cerarVBO (una vez por cada tabla)
         //VBO vértices y caras
         if(id_vbo_ver == 0) id_vbo_ver = CrearVBO( GL_ARRAY_BUFFER , v.size()*3*sizeof(float), v.data());        //TABLA DE VERTICES
         if(id_vbo_nv == 0) id_vbo_nv = CrearVBO( GL_ARRAY_BUFFER , nv.size()*3*sizeof(float), nv.data());       //TABLA DE NORMALES DE VERTICES
         if(id_vbo_tri == 0) id_vbo_tri = CrearVBO( GL_ELEMENT_ARRAY_BUFFER , f.size()*3*sizeof(int), f.data());  //TABLA DE TRIANGULOS

         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

         if( vision.test(7) ) //Si esta activo el modo suave
            glShadeModel(GL_SMOOTH);
         else //Si esta desactivado el modo suave entonces se pinta en modo plano
            glShadeModel(GL_FLAT);

         //MATERIALES---------------------------------------------------------
         if(seleccionado){ //Si está selccionado
            mSeleccion.aplicar();
         }
         else{
            m.aplicar();
         }     
                  

         //VERTICES Y NORMALES-------------------------------------------------
         //especificar localización y formato de la tabla de vértices, habilitar tabla
         glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
         glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0) VERTICES
         glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

         glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_nv ); // activar VBO de normales de vértices
         glNormalPointer ( GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0) NORMALES DE VERTICES
         glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de normales de vértices.
         glEnableClientState ( GL_NORMAL_ARRAY ); // habilitar tabla de normales de vértices

            
         // visualizar triángulos con glDrawElements (puntero a tabla == 0)
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
         glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            
         // desactivar uso de array de colores y de vértices
         glDisableClientState ( GL_VERTEX_ARRAY );
         glDisableClientState ( GL_NORMAL_ARRAY );


      }
      else if(modoAjedrez){ //----MODO AJEDREZ----------------------------------------------------------

         //identificar si los identificadires de los VBOs son 0
         //si lo son, entonces invocar a cerarVBO (una vez por cada tabla)
         
         //VBO vértices y caras
         if(id_vbo_ver == 0) id_vbo_ver = CrearVBO( GL_ARRAY_BUFFER , v.size()*3*sizeof(float), v.data());        //TABLA DE VERTICES
         if(id_vbo_f_par== 0) id_vbo_f_par = CrearVBO( GL_ARRAY_BUFFER , fPar.size()*3*sizeof(float), fPar.data());   //TABLA DE TRIANGULOS CARAS PAR
         if(id_vbo_f_impar == 0) id_vbo_f_impar = CrearVBO( GL_ARRAY_BUFFER , fImpar.size()*3*sizeof(float), fImpar.data());   //TABLA DE TRIANGULOS CARAS IMPAR
         
         //VBO colores
         if(seleccionado){ //Si está selccionado
            if(id_vbo_col_parSeleccionado == 0) id_vbo_col_parSeleccionado = CrearVBO( GL_ARRAY_BUFFER , colorFParSeleccionado.size()*3*sizeof(float), colorFParSeleccionado.data());        //TABLA DE COLORES CARAS PAR
            if(id_vbo_col_imparSeleccionado == 0) id_vbo_col_imparSeleccionado = CrearVBO( GL_ARRAY_BUFFER , colorFImparSeleccionado.size()*3*sizeof(float), colorFImparSeleccionado.data());   //TABLA DE COLORES CARAS IMPAR
         }
         else{
            if(id_vbo_col_par == 0) id_vbo_col_par = CrearVBO( GL_ARRAY_BUFFER , colorFPar.size()*3*sizeof(float), colorFPar.data());        //TABLA DE COLORES CARAS PAR
            if(id_vbo_col_impar== 0) id_vbo_col_impar = CrearVBO( GL_ARRAY_BUFFER , colorFImpar.size()*3*sizeof(float), colorFImpar.data());   //TABLA DE COLORES CARAS IMPAR
         } 
         

         // especificar localización y formato de la tabla de colores, habilitar tabla
         glPolygonMode(GL_FRONT, GL_FILL); // Cara delantera rellena

         //-----CARAS PARES---------------------------------------------------
         //COLORES-------------------------------------------------------
         if(seleccionado){ //Si está selccionado
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_col_parSeleccionado ); // activar VBO de colores
            glColorPointer( 3, GL_FLOAT, 0, 0);
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
            glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
         }
         else{
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_col_par ); // activar VBO de colores
            glColorPointer( 3, GL_FLOAT, 0, 0);
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
            glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
         } 
         

         //VERTICES------------------------------------------------------
         // especificar localización y formato de la tabla de vértices, habilitar tabla
         glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
         glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
         glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

         
         // visualizar triángulos con glDrawElements (puntero a tabla == 0)
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_f_par); // activar VBO de triángulos
         glDrawElements ( GL_TRIANGLES , 3*tamanios[1] , GL_UNSIGNED_INT , 0 ) ;
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
         
         // desactivar uso de array y de vértices
         glDisableClientState ( GL_COLOR_ARRAY );
         glDisableClientState ( GL_VERTEX_ARRAY );


         //-----CARAS IMPARES------------------------------------------------
         //COLORES------------------------------------------------------
         if(seleccionado){ //Si está selccionado
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_col_imparSeleccionado ); // activar VBO de colores
            glColorPointer( 3, GL_FLOAT, 0, 0);
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
            glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
         }
         else{
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_col_impar ); // activar VBO de colores
            glColorPointer( 3, GL_FLOAT, 0, 0);
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
            glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
         } 
         

         //VERTICES------------------------------------------------------
         // especificar localización y formato de la tabla de vértices, habilitar tabla
         glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
         glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
         glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
         glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

         
         // visualizar triángulos con glDrawElements (puntero a tabla == 0)
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_f_impar ); // activar VBO de triángulos
         glDrawElements ( GL_TRIANGLES , 3*tamanios[2] , GL_UNSIGNED_INT , 0 ) ;
         glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
         
         // desactivar uso de array y de vértices
         glDisableClientState ( GL_COLOR_ARRAY );
         glDisableClientState ( GL_VERTEX_ARRAY );
            
      }
      else{ //----MODO NORMAL----------------------------------------------------------

         //identificar si los identificadires de los VBOs son 0
         //si lo son, entonces invocar a cerarVBO (una vez por cada tabla)
         //VBO vértices y caras
         if(id_vbo_ver == 0) id_vbo_ver = CrearVBO( GL_ARRAY_BUFFER , v.size()*3*sizeof(float), v.data());        //TABLA DE VERTICES
         if(id_vbo_tri == 0) id_vbo_tri = CrearVBO( GL_ELEMENT_ARRAY_BUFFER , f.size()*3*sizeof(int), f.data());  //TABLA DE TRIANGULOS
         //VBO colores

         //--MODO PUNTOS------
         if(vision.test(3)){

            glPointSize(5.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // Cara delantera solo puntos

            //COLORES---------------------------------------------------------
            if(seleccionado){ //Si está selccionado
               if(id_vbo_colorSeleccionado == 0) id_vbo_colorSeleccionado = CrearVBO( GL_ARRAY_BUFFER , colorSeleccionado.size()*3*sizeof(float), colorSeleccionado.data());//TABLA DE COLORES

               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorSeleccionado); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            }
            else{
               //Si esta activado el modo Puntos(bit 3) entonces usamos colorPunt
               if(id_vbo_colorPunt == 0) id_vbo_colorPunt = CrearVBO( GL_ARRAY_BUFFER , colorPunt.size()*3*sizeof(float), colorPunt.data());//TABLA DE COLORES

               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorPunt); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            } 

            //VERTICES--------------------------------------------------------
            //especificar localización y formato de la tabla de vértices, habilitar tabla
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

            
            // visualizar triángulos con glDrawElements (puntero a tabla == 0)
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
            glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            
            // desactivar uso de array de colores y de vértices
            glDisableClientState ( GL_COLOR_ARRAY );
            glDisableClientState ( GL_VERTEX_ARRAY );
         }

         //--MODO LINEAS------
         if(vision.test(2)){

            glLineWidth(2.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Ambas caras en alambres

            //COLORES---------------------------------------------------------
            if(seleccionado){ //Si está selccionado
               if(id_vbo_colorSeleccionado == 0) id_vbo_colorSeleccionado = CrearVBO( GL_ARRAY_BUFFER , colorSeleccionado.size()*3*sizeof(float), colorSeleccionado.data());//TABLA DE COLORES

               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorSeleccionado); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            }
            else{
               //Si esta activado el modo Lineas(bit 2) entonces usamos colorLin
               if(id_vbo_colorLin == 0) id_vbo_colorLin = CrearVBO( GL_ARRAY_BUFFER , colorLin.size()*3*sizeof(float), colorLin.data());//TABLA DE COLORES

               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorLin); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            } 

            //VERTICES--------------------------------------------------------
            //especificar localización y formato de la tabla de vértices, habilitar tabla
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

            
            // visualizar triángulos con glDrawElements (puntero a tabla == 0)
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
            glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            
            // desactivar uso de array de colores y de vértices
            glDisableClientState ( GL_COLOR_ARRAY );
            glDisableClientState ( GL_VERTEX_ARRAY );
         }

         //--MODO SOLIDO------
         if(vision.test(1)){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Cara delantera rellena

            //COLORES---------------------------------------------------------
            if(seleccionado){ //Si está selccionado
               if(id_vbo_colorSeleccionado == 0) id_vbo_colorSeleccionado = CrearVBO( GL_ARRAY_BUFFER , colorSeleccionado.size()*3*sizeof(float), colorSeleccionado.data());//TABLA DE COLORES

               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorSeleccionado); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            }
            else{
               //Si esta activado el modo Solido (bit 1) entonces usamos colorSol
               if(id_vbo_colorSol == 0) id_vbo_colorSol = CrearVBO( GL_ARRAY_BUFFER , colorSol.size()*3*sizeof(float), colorSol.data());//TABLA DE COLORES
               
               glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_colorSol); // activar VBO de colores
               glColorPointer( 3, GL_FLOAT, 0, 0);
               glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de colores.
               glEnableClientState ( GL_COLOR_ARRAY ); // habilitar tabla de colores
            } 
                 

            //VERTICES--------------------------------------------------------
            //especificar localización y formato de la tabla de vértices, habilitar tabla
            glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
            glVertexPointer ( 3 , GL_FLOAT , 0 , 0 ); // especifica formato y offset (=0)
            glBindBuffer ( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
            glEnableClientState ( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

            
            // visualizar triángulos con glDrawElements (puntero a tabla == 0)
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri ); // activar VBO de triángulos
            glDrawElements ( GL_TRIANGLES , 3*tamanios[0] , GL_UNSIGNED_INT , 0 ) ;
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            
            // desactivar uso de array de colores y de vértices
            glDisableClientState ( GL_COLOR_ARRAY );
            glDisableClientState ( GL_VERTEX_ARRAY );
         }
      
         
      }
      

      glDisableClientState( GL_TEXTURE_COORD_ARRAY );
      glDisable(GL_TEXTURE_2D);
   }

}




// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(std::bitset<10> vision, bool seleccionado)
{
   // completar .....(práctica 1)
   //PRACTICA 2
   //Vector para los offset
   std::vector<int> tamanios; //{f.size(), fpar.size(), fimpar.size()}
   tamanios.clear();
   tamanios.resize(3);
   tamanios[0] = f.size();
   tamanios[1] = fPar.size();
   tamanios[2] = fImpar.size();

   //Modo de dibujado
   bool inmediato=false;

   //Comprobamos los modos

   //-------MODO DE DIBUJADO---------------------------
   if(vision.test(4)){
      //Si esta activado el bit 4 es porque se dibuja en modo inmediato
      //por lo que ponemos inmediato a true
      inmediato=true;
     
   }
   
   ///-------MODO DE VISUALIZACIÓN---------------------------
   //--LUCES------
   if(vision.test(6)){ //SI LAS LUCES ESTAN ENCENSIDAS SE ACTIVA EL MATERIAL
  
      if(inmediato){
         draw_ModoInmediato(false, vision,tamanios,seleccionado);
      }
      else{
         draw_ModoDiferido(false, vision,tamanios,seleccionado);
      }

   }
   else{ //SI LAS LUCES ESTÁN APAGADAS ENTONCES SE TIENE EN CUENTA EL RESTO DE MODOS Y SE TIENEN EN CUENTA LOS COLORES
      //--MODO AJEDREZ------
      if(vision.test(0)){   
         //Si esta activado el modo Ajedrez (bit 0) entonces llamamos a drawAjedrez
         drawAjedrez(inmediato,vision,seleccionado);
      }

      else{

         //--MODO PUNTOS LINEAS SOLDO-----
         if(inmediato){
            draw_ModoInmediato(false, vision,tamanios,seleccionado);
         }
         else{
            draw_ModoDiferido(false, vision,tamanios,seleccionado);
         }
            

      }
   }

}


// -----------------------------------------------------------------------------
// Función de visualización de la malla PARA EL MODO AJEDREZ,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::drawAjedrez(bool inmediato, std::bitset<10> vision,bool seleccionado)
{
   // completar .....(práctica 1)
   //Vector para los offset
   std::vector<int> tamanios; //{f.size(), fpar.size(), fimpar.size()}
   tamanios.clear();
   tamanios.resize(3);
   tamanios[0] = f.size();
   tamanios[1] = fPar.size();
   tamanios[2] = fImpar.size();

   glPolygonMode(GL_FRONT, GL_FILL); // Cara delantera rellena

   //Llamamos al modo de dibujado elegido indicando por el parámetro
   if(inmediato) 
      draw_ModoInmediato(true, vision,tamanios,seleccionado);

   else 
      draw_ModoDiferido(true, vision,tamanios,seleccionado);

}

// -----------------------------------------------------------------------------
// Función que calcula tabla de normales de vértices y las inserta en nv

void Malla3D::calcular_normales(){

   //--------------------------------------------------------------------------------------------------
   //Primero calcular la tabla de normales de las caras
   std::vector<Tupla3f> ncaras;  // tabla de normales de caras
   ncaras.clear();

   for(int i=0; i < f.size(); i++){
      //Cada cara está compuesta por p q r
      Tupla3f p = v[f[i][0]];
      Tupla3f q = v[f[i][1]];
      Tupla3f r = v[f[i][2]];

      //Vector a = q - p
      Tupla3f a = { q[0]-p[0], q[1]-p[1], q[2]-p[2] };
      

      //Vector b = r - p
      Tupla3f b = { r[0]-p[0], r[1]-p[1], r[2]-p[2] };
      
      
      //Producto vectorial a x b = mc
      Tupla3f mc = { (a[1]*b[2])-(a[2]*b[1]), (a[0]*b[2])-(a[2]*b[0]), (a[0]*b[1])-(a[1]*b[0]) };

      //Normalizar el mc => nc = mc / |Mc|
      float modMc = sqrt( mc[0]*mc[0] + mc[1]*mc[1] + mc[2]*mc[2] );
      Tupla3f nc = { mc[0]/modMc, mc[1]/modMc, mc[2]/modMc};

      ncaras.push_back(nc); //Guardamos en el vector de normales de caras

   }

   //--------------------------------------------------------------------------------------------------
   //Segundo calcular llas nomales de los vértices
   std::vector<Tupla3f> nvertices;  // tabla de normales de vertices
   nvertices.clear();

   //Rellenamos nvetices a {0,0,0} para cada vértice para hacer la suma correctamente
   nvertices.insert( nvertices.begin(), v.size(), {0.0,0.0,0.0} );



   for(int i=0; i < f.size(); i++){

      Tupla3f nc = ncaras[i]; //Tupla con la normal de la cara i
      Tupla3i indice = f[i]; //Tupla con los indices de la cara i

      //Primer indice 
      nvertices[indice[0]] = { nvertices[indice[0]][0]+nc[0], nvertices[indice[0]][1]+nc[1],nvertices[indice[0]][2]+nc[2] };


      //Segundo indice
      nvertices[indice[1]] = { nvertices[indice[1]][0]+nc[0], nvertices[indice[1]][1]+nc[1],nvertices[indice[1]][2]+nc[2] };

      //Tercer indice
      nvertices[indice[2]] = { nvertices[indice[2]][0]+nc[0], nvertices[indice[2]][1]+nc[1],nvertices[indice[2]][2]+nc[2] };

   }
   

   //--------------------------------------------------------------------------------------------------
   //Tercero Normalizar
   for(int i=0; i < nvertices.size(); i++){
      Tupla3f mv = nvertices[i];

      float modMv = sqrt( mv[0]*mv[0] + mv[1]*mv[1] + mv[2]*mv[2] );
      Tupla3f nvert = { mv[0]/modMv, mv[1]/modMv, mv[2]/modMv};

      nvertices[i] = nvert;
   }

   nv = nvertices; //Igualar nv a nvertices
      
}


// -----------------------------------------------------------------------------
// Función que modifica el material del objeto

void Malla3D::setMaterial( Material mat ){
   m = mat;
}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para los diferentes modos
void Malla3D::setColor( Tupla3f cPunt, Tupla3f cLin,  Tupla3f cSol, Tupla3f cFPar, Tupla3f cFImpar){
   
   //Diferentes tablas de colores

   //Color modo puntos
   colorPunt.clear();
   colorPunt.insert( colorPunt.begin(), v.size(), cPunt );

   //Color modo lineas
   colorLin.clear();
   colorLin.insert( colorLin.begin(), v.size(), cLin);

   //Color modo solido
   colorSol.clear();
   colorSol.insert( colorSol.begin(), v.size(), cSol );

   //Color modo ajedrez caras pares
   colorFPar.clear();
   colorFPar.insert( colorFPar.begin(), v.size(), cFPar);

   //Color modo ajedrez caras impares
   colorFImpar.clear();
   colorFImpar.insert( colorFImpar.begin(), v.size(), cFImpar );

}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void Malla3D::setColorModoSeleccion( Tupla3f cModoSeleccion){
   colorModoSeleccion.clear();
   colorModoSeleccion.insert( colorModoSeleccion.begin(), v.size(), cModoSeleccion );
}
// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para cuando esta seleccionado
void Malla3D::setColorSeleccionado( Tupla3f cSeleccionado){
   colorSeleccionado.clear();
   colorSeleccionado.insert( colorSeleccionado.begin(), v.size(), cSeleccionado );
}

void Malla3D::setColorModoLineas(Tupla3f cLin){
   colorLin.clear();
   colorLin.insert( colorLin.begin(), v.size(), cLin );
}