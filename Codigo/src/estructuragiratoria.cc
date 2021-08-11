#include "auxiliar.h"
#include "estructuragiratoria.h"
#include <math.h> 

#define PI 3.141592 //Definimos PI


EstructuraGiratoria::EstructuraGiratoria(){

    //--OBJETOS
    piston = new Piston();
    brazo = new Brazo();
    estructura = new Estructura();

    //--Parametros Animacion

    //Animacion Estructura
    cteGiroEstructura = 60;
    gamma = 0.0;

    //Animacion brazos
    cteGiroBrazos = 30;
    beta = -15.0;
    subir = true;

}


void EstructuraGiratoria::dibujarBrazos(std::bitset<10> vision, bool seleccionado){

    //i=0
    glPushMatrix();
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=1
    glPushMatrix(); 
        glRotatef(45.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=2
    glPushMatrix();
        glRotatef(90.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=3
    glPushMatrix();
        glRotatef(135.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=4
    glPushMatrix();
        glRotatef(180.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=5
    glPushMatrix();
        glRotatef(225.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=6
    glPushMatrix();
        glRotatef(270.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    //i=7
    glPushMatrix();
        glRotatef(315.0,0,1,0); //i*45
        glRotatef(beta,0,0,1); //Beta [-15,15]
        brazo->draw(vision,seleccionado);
    glPopMatrix();
    
}

void EstructuraGiratoria::dibujarPistones(std::bitset<10> vision, bool seleccionado){

    //i=0
    glPushMatrix();
        glTranslatef(0.0,0.0,25.0); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=1
    glPushMatrix();
        glTranslatef(17.6777,0.0,17.6777); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(45.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=2
    glPushMatrix();
        glTranslatef(25.0,0.0,0.0); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(90.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=3
    glPushMatrix();
        glTranslatef(17.6777,0.0,-17.6777); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(135.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=4
    glPushMatrix();
        glTranslatef(0.0,0.0,-25.0); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(180.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=5
    glPushMatrix();
        glTranslatef(-17.6777,0.0,-17.6777); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(225.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=6
    glPushMatrix();
        glTranslatef(-25,0.0,0.0); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(270.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();
    //i=7
    glPushMatrix();
        glTranslatef(-17.6777,0.0,17.6777); //sin(i*45)*25.0,cos(i*45)*25
        glRotatef(315.0,0,1,0); //i*45
        glRotatef(20.0,1,0,0);
        piston->draw(vision,seleccionado);
    glPopMatrix();

}

void EstructuraGiratoria::draw(std::bitset<10> vision, bool seleccionado){

    
    glPushMatrix();
        glRotatef(gamma,0,1,0); //gamma
        //Brazos
        glPushMatrix();
            glTranslatef(0.0,32.0,0.0);
            glScalef(0.65,0.65,0.65);
            dibujarBrazos(vision,seleccionado);
        glPopMatrix();
        //Pistones
        glPushMatrix();
            glTranslatef(0.0,9.0,0.0);
            dibujarPistones(vision,seleccionado);
        glPopMatrix();
        //Estructura
        glPushMatrix();
            estructura->draw(vision,seleccionado);
        glPopMatrix();
    glPopMatrix();
    
}

/**
 * Funcion para reestablecer los valores de alpha y beta a los incicales para coordinar 
 * el los brazos y los pistones
 */
void EstructuraGiratoria::restablecerValores(){
    piston->restablecerValores();
    beta = -15.0;
}


/**
 * Devuelve el valor que debe tomar alpha para que se corresponda con el movimiento que genera el valor de beta
 * Para esta función se ha hecho uso de trigonometría y depende por completo
 * de los valores de las medidas de los objetos
 * @return float 
 */
float EstructuraGiratoria::calcularAlpha(){
    //alpha depende del valor de beta para x= (cos((70*PI)/180.0)*21)+25 
    //que es el valor de x para la punta del piston cuando esta en su menor valor

    //--Altura brazos
    float hBrazos = ( sin((beta*PI)/180.0) * (( cos((70*PI)/180.0) * 21 ) + 25) ) + 32;

    //--Altura piston
    float hPiston = 30 + piston->getAlpha();
    hPiston = sin((70*PI)/180.0)*hPiston;

    float aux = hBrazos * 19.7335 / 23.6706; //Factor de conversion para el nuevo valor de alpha
    //19.7335 es el valor minimo de y para el piston 
    //23.6706 es el valor minimo de y para el brazo en x = 33

    float alpha = piston->getAlpha() + aux - hPiston;

    return alpha;
}


/**
 * Funcion para coordinar el movimiento de los pistones con el de los brazos para
 * que no se descoordinen.
 */
void EstructuraGiratoria::movimientoPistonBrazo(float valor){

    if(valor > 0){

    if(subir){ //Si no se ha alcanzado el máximo de 15 se sigue subiendo

        //float incremento = beta + beta*valor;
        float incremento = beta + fabs (cteGiroBrazos*valor);

        if(incremento >= 15.0){
            //Establecemos beta al máximo
            beta =15.0;

            //Establecemos el valor de alpha al máximo
            piston->setAlpha(10.0);

            subir =false;
        }
        else{
            //Establecemos beta al que corresponda
            beta = incremento;

            //Modificamos alpha para que se muevan a la vez
            piston->setAlpha(calcularAlpha());
        }

    }
    else{ //Si hay que bajar

        float decremento = beta - fabs (cteGiroBrazos*valor);

        if(decremento <= -15.0){
            //Establecemos beta al minimo
            beta =-15.0;
            
            //Establecemos el valor de alpha al minimo
            piston->setAlpha(-9.0);

            subir =true;
        }
        else{
            //Establecemos beta al que corresponda
            beta = decremento;

            //Modificamos alpha para que se muevan a la vez
            piston->setAlpha(calcularAlpha());
        }
    }
    }
}

void EstructuraGiratoria::modificaAlturaPiston( float valor ){
    piston->modificaAlturaPiston(valor);

}
void EstructuraGiratoria::disminuirAlturaPiston( float valor ){
    piston->disminuirAlturaPiston(valor);

}
void EstructuraGiratoria::aumentarAlturaPiston( float valor ){
    piston->aumentarAlturaPiston(valor);

}
void EstructuraGiratoria::modificaGiroZBrazos( float valor ){

    if(subir){ //Si no se ha alcanzado el máximo de 15 se sigue subiendo

        //float incremento = beta + beta*valor;
        float incremento = beta + fabs (cteGiroBrazos*valor);

        if(incremento >= 15.0){
            beta =15.0;
            subir =false;
        }
        else{
            beta = incremento;
        }

    }
    else{ //Si hay que bajar

        float decremento = beta - fabs (cteGiroBrazos*valor);

        if(decremento <= -15.0){
            beta =-15.0;
            subir =true;
        }
        else{
            beta = decremento;
        }
    }

}

void EstructuraGiratoria::disminuirGiroZBrazos( float valor ){

    float decremento = beta - fabs (cteGiroBrazos*valor);

    if(decremento <= -15.0){
        std::cout << "\t  No es posible disminuir mas el giro del brazo "<< std::endl;
        beta =-15.0;
    }
    else{
        beta = decremento;
    }
    
}

void EstructuraGiratoria::aumentarGiroZBrazos( float valor ){

    float incremento = beta + fabs (cteGiroBrazos*valor);

    if(incremento >= 15.0){
        std::cout << "\t  No es posible aumentar mas el giro del brazo "<< std::endl;
        beta =15.0;
    }
    else{
        beta = incremento;
    }


}



void EstructuraGiratoria::modificaGiroEstructura(float valor ){

    if(valor > 0){

    float incremento = fabs (gamma) + 50*valor;

    gamma = fmod(incremento,360); //Hay que aplicarle el modulo de 360 al incremento para saber lo que rota

    gamma = -1 * gamma; //Para que la rotacion se haga en sentido horario
    
    }

}

void EstructuraGiratoria::aumentarGiroEstructura(float valor ){

    if(valor > 0){

    float incremento = fabs (gamma) + fabs (cteGiroEstructura*valor); 

    gamma = fmod(incremento,360); //Hay que aplicarle el modulo de 360 al incremento para saber lo que rota
    
    gamma = -1 * gamma; //Para que la rotacion se haga en sentido horario

    }


}

void EstructuraGiratoria::disminuirGiroEstructura(float valor ){

    if(valor > 0){

    float decremento = fabs (gamma) + fabs (cteGiroEstructura*valor); //Para que la rotacion se haga en sentido antihorario

    gamma = fmod(decremento,360); 
    
    }
    
}

// -----------------------------------------------------------------------------
// Función que modifica el color del objeto para el modo de seleecion
void EstructuraGiratoria::setColorModoSeleccion( Tupla3f cModoSeleccion){
    estructura->setColorModoSeleccion(cModoSeleccion);
    piston->setColorModoSeleccion(cModoSeleccion);
    brazo->setColorModoSeleccion(cModoSeleccion);
}

void EstructuraGiratoria::setColorModoLineas(Tupla3f cLin){
    estructura->setColorModoLineas(cLin);
    piston->setColorModoLineas(cLin);
    brazo->setColorModoLineas(cLin);
}