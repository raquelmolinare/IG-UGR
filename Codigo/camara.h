// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
// -- declaraciones de clase Camara
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clase para objetos Camara
//
// *****************************************************************************



typedef enum {EXAMINAR, FIRSTPERSON} Modo;

class Camara
{
    public:
        //Constructor
        Camara (Tupla3f eyeCam,Tupla3f atCam,Tupla3f upCam, int tipoCam,float leftCam, float rightCam, float bottomCam, float topCam,float nearCam ,float farCam) ;
        Camara (Tupla3f eyeCam,Tupla3f atCam, int tipoCam) ;

        //Mover la camara de sitio
        void mover ( float x, float y, float z );

        //Pone la camara en posicion examinar un objeto que esta en el x,y,z
        void posicionarExaminar( float x, float y, float z );

        //Para los angulos de giro en modo examinar o modo first person
        void girarExaminar( float x, float y);
        void girarFirstPerson(float x, float y);

        //Zoom de la camara
        void zoom ( float factor );

        void rotarX( float angle );
        void rotarY( float angle );
        void rotarZ( float angle );


        void setObserver ();
        void setProyeccion ();

        void setAt(Tupla3f atNew);

        void setLeft(float nleft);
        void setRight(float nright);
        void setNear(float nnear);
        void setFar(float nfar);
        void setBottom(float nbottom);
        void setTop(float ntop);

        void setSeleccionaObjeto( bool selecciona);
        void setIndiceObjeto(int indice);

        float getLeft();
        float getRight();
        float getNear();
        float getFar();
        float getBottom();
        float getTop();
        int getModo();
        int getIndiceObjeto();
        bool getSeleccionaObjeto();


    protected:
        Tupla3f eye ;
        Tupla3f at ;
        Tupla3f up ;
        int tipo ; // ORTOGONAL (1) o Perspectiva (2)

        Modo modo = FIRSTPERSON;

        //Para el volumen de visualización
        float left , right , near , far, bottom, top ; // o bien aspect, fov, near, far;

        float anguloX, anguloY, cteGiro;
        float yaw, pitch;

        bool seleccionaObjeto;
        int indiceObjeto; //0 si ninguno

        //Rotaciones modo Examinar --> Rotaciones en torno a un punto
        void rotarXExaminar ( float angle );
        void rotarYExaminar ( float angle );
        void rotarZExaminar ( float angle );

        //Rotaciones en primera persona
        void rotarXFirstPerson ( float angle );
        void rotarYFirstPerson ( float angle );
        void rotarZFirstPerson ( float angle );

        

        
} ;

#endif