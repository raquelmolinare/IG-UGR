#include "auxiliar.h"
#include "textura.h"


Textura::Textura ( string archivo ){

    //---Lectura de los texel del archivo de imagen------------
    jpg::Imagen * pimg = NULL ; //Puntero a imagen (pimg)

    // cargar la imagen (una sola vez!)
    pimg = new jpg::Imagen(archivo);

    // usar con:
    width= pimg-> tamX (); // núm. columnas (unsigned)
    height = pimg->tamY (); // núm. filas (unsigned)

    //Lectura de ternas rgb de la imagen
    for(int i=0; i < pimg->tamY(); i++){
        for(int j=0; j < pimg->tamX(); j++){
            unsigned char * rgb = pimg->leerPixel(j,i); // puntero texels (unsigned char *)
            data.push_back(rgb[0]); //componente roja
            data.push_back(rgb[1]); //componente verde
            data.push_back(rgb[2]); //componente azul
        }
    }

}


//Carga de texturas en el sistema gráfico
void Textura::activar (){
    
    glEnable(GL_TEXTURE_2D);
    if(textura_id==0){ //Si es la primera vez que se activa
        //Generar identificador
        glGenTextures( 1, &textura_id ); // textura_id almacena el nuevo identificador
        //Activar textura
        glBindTexture( GL_TEXTURE_2D, textura_id ); // activa textura con id ’textura_id’ 
        //---Alojamiento en RAM de imágenes de textura---------------------------------------------------------------------
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
        gluBuild2DMipmaps ( GL_TEXTURE_2D , GL_RGB , width, height, GL_RGB ,  GL_UNSIGNED_BYTE , data.data());

    }

    //Activar textura
    glBindTexture( GL_TEXTURE_2D, textura_id ); // activa textura con id ’textura_id’ 
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_REPLACE);

    //---Configuración de las texturas---------------------------------------------------------------------
    //---Iluminación--------------
    //glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR); //Se usa el color de la textura y no las reflectividades del material (para la iluminación)
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);    //color de la textura se usa en lugar de MA y MD, pero no MS (iluminación)
                                                                                //permite brillos especulares de color blanco cuando hay texturas de color


    //---Seleccion del texel o texels a partir de una coordenada de textura--------------
    //más cercano
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); //cuando nos acercamos
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); //cuando nos alejamos
    //interpolacion
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //cuando nos acercamos
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //cuando nos alejamos

    //--Seleccion del texel cuando las coordenadas de textura no están en el rango [0, 1]
    //replicado
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); //Repetir en S
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); //Repetir en T
    //truncamiento
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP ); //Repetir en S
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP ); //Repetir en T

    
}
