#include "auxiliar.h"
#include "luz.h"
#include "esfera.h"


// -----------------------------------------------------------------------------
// Función dpara activar las fuentes de luz
void Luz::activar(){

    //Configuración de colores de la fuente a activar 
    //Configuración de posicion/dirección de la fuente a activar
    
    //Colores
    glLightfv( id, GL_AMBIENT, colorAmbiente ) ;
    glLightfv( id, GL_DIFFUSE, colorDifuso ) ;
    glLightfv( id, GL_SPECULAR, colorEspecular ) ;
            
    //Posicion / Dirección
    glLightfv( id, GL_POSITION, posicion);

}