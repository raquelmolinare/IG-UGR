#include "auxiliar.h"
#include "material.h"

Material::Material(){}

// -----------------------------------------------------------------------------
// Constructor material de un objeto
Material::Material(Tupla4f mambiente, Tupla4f mespecular, Tupla4f mdifuso, float mbrillo ){
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;

    if(mbrillo < 0.0 || mbrillo > 128.0)
        brillo = 128.0;
    else
        brillo = mbrillo;
}

// -----------------------------------------------------------------------------
// Funcion para aplicar el material a un objeto
void Material::aplicar (){

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, difuso );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, especular );
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, brillo ); 

}
