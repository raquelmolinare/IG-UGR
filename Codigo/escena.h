#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "cuadro.h"
#include "skybox.h"

#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"

#include "atraccion.h"

#include "camara.h"

#include <string>
#include <bitset>

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELTAPAS,SELPLY,SELREVOLUCION,AMANUAL,CAMARA} menu;
typedef enum {NINGUNO, CUBO, TETRAEDRO, OBJPLY, OBJREVOLUCION} objetoVisible;
typedef enum {NONE, ANT, BEETHOVEN, BIGDODGE} objetoPly;
typedef enum {NOTHING, PEON, CILINDRO, CONO, ESFERA, LATA} objetoRevolucion;
typedef enum {NO, ALPHA, BETA} angulo;
typedef enum {PARADO, MOVIENDO_CAMARA_FIRSTPERSON, MOVIENDO_CAMARA_EXAMINAR} estadosRaton;
typedef enum {ANY, CUBOS, TETRAEDROS, ANTS, BEETHOVENS, BIGDODGES,PEONS, CILINDROS, CONOS, ESFERAS, LATAS,ATRACCIONS,NORIAS,TIOVIVOS,FUENTES,NUBESS,AVIONS} objetosSeleccionables;


class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
    // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   bool primerMenu;

   // Objetos de la escena ----------------------------------------------------------
    Ejes ejes;
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'

    //Practica2 
    //PLY's
    ObjPLY * ant = nullptr;
    ObjPLY * beethoven = nullptr;
    ObjPLY * bigdodge = nullptr;

    //Objetos de revolucion 
    ObjRevolucion * peon = nullptr;

    Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;

    //Practica4
    //MODELO JERARQUICO------
    Atraccion * atraccion = nullptr;

    //Practica 5
    //Texturas------
    ObjRevolucion * latacue = nullptr;
    ObjRevolucion * latasup = nullptr;
    ObjRevolucion * latainf = nullptr;

    Cuadro * cuadro = nullptr;
    SkyBox * skybox = nullptr;

    ObjPLY * tiovivo = nullptr;
    ObjPLY * noria = nullptr;
    ObjPLY * nubes = nullptr;
    ObjPLY * farola = nullptr;
    ObjPLY * arbol = nullptr;
    ObjPLY * avion = nullptr;
    ObjPLY * fuente = nullptr;
    ObjPLY * persona = nullptr;

    //OBJETOS 
    //Cada objeto es un bit
    //lata-esfera-cono-cilindro-peonN-peonB-bigdodge-beethoven-ant-tetraedro-cubo
    std::bitset<10> objetosEscena = 0; 

    objetoVisible objeto = NINGUNO; //objeto que estará visible
    
    //Practica2 
    objetoPly objetoply = NONE;
    objetoRevolucion objetorevolucion = NOTHING;


    //Vision de la escena ----------------------------------------------------------

    // 110010 Tapas - Modo de dibujado y- visualización TDPLSA 
    //(Tapas Dibujado Puntos Lineas Solido Ajedrez) Con tapas Modo inmediato y sólido por defecto
    //std::bitset<6> vision = 50; 


    //Practica 3
    // Sombreado -Luz - Tapas - Modo de dibujado y- visualización SLTDPLSA
    //  ModoSeleccion-Seleccionado-Sombreado Luz Tapas Dibujado Puntos Lineas Solido Ajedrez) Con tapas Modo inmediato y sólido luces apagadas por defecto
    std::bitset<10> vision = 0; 

    bool modoDibujado = true; //Modo de dibujado ( por defecto true es modo inmediato y false diferido)


    //PRACTICA 3
    //Luces de la escena ----------------------------------------------------------
    LuzPosicional * fuenteLuz0 = nullptr;
    LuzDireccional * fuenteLuz1 = nullptr;
    LuzPosicional * fuenteLuz2 = nullptr;
    LuzDireccional * fuenteLuz3 = nullptr;
    LuzPosicional * fuenteLuz4 = nullptr;
 

    std::bitset<5> lucesEscena = 0; 
    bool gestionarluces = false;
    bool decrementarAlfa = false;
    bool decrementarBeta = false;
    bool incrementarAlfa = false;
    bool incrementarBeta = false;


    angulo rotacionluz = NO; 
    

    //PRACTICA 4
    //Animacion de la escena ----------------------------------------------------------
    //Animacion automatica
    bool gestionarAAutomatica;
    bool restablecerValores;
    float cteVelocidad;
    float velocidad;
    //Animacion manual
    bool gestionarAManual = false;
    float cteValor;
    bool aumentarMan;
    //Selccion grados de LIbertad
    //GL0 --> piston GL1--> Brazos arriba y abajo GL3--> Gira la estrutura
    std::bitset<3> gradosLibertad = 0;


    //PRACTICA 5
    //Texturas ---------------------------------------------------------------------
    bool animarLuzPuntual;
    

    //PRACTICA 6
    //Cámara. Interacción ---------------------------------------------------------------------
    std::vector<Camara> camaras; //vector de camaras
    int camaraActiva; //de 0 a numero de camaras activas contiene el indice de la camara que se encuentra activa en el momento
    estadosRaton estadoRaton = PARADO;
    float xantCamara,yantCamara;

    bool verSeleccionables;


   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

    //Muestra el menu principal
    void menuPrincipal();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    // Animacion automatica
    void animarModeloJerarquico();

    //Control de eventos
    void clickRaton( int boton , int estado , int x, int y);
    void ratonMovido(int x, int y);

    void dibujaSeleccion();
    void processPick(int x, int y);

};
#endif
