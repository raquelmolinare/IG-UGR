

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************



Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;
   
    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...


   // Objetos de la escena ----------------------------------------------------------

   objeto = NINGUNO; //OBJETO
   primerMenu = true;

   cubo = new Cubo(1);
   tetraedro = new Tetraedro(1);
   
   //Practica 2
   //PLY's
   ant = new ObjPLY("./plys/ant.ply");
   beethoven = new ObjPLY("./plys/beethoven.ply");
   bigdodge = new ObjPLY("./plys/big_dodge.ply");

   //Objetos de revolucion
   //peon = new ObjRevolucion("./plys/peon.ply", 20,true, true,'y');
   peon = new ObjRevolucion("./plys/peon.ply", 50,true, true,'y');

   cilindro = new Cilindro(3, 6, 1.0, 1.0,true, true,'z');
   cono = new Cono(5,50,1.0,1.0,true,'x');
   esfera = new Esfera(30,50, 1.0, true, true,true);

   //MODELO JERARQUICO
   atraccion = new Atraccion();

   //P5 : Texturas
   latacue =  new ObjRevolucion("./plys/lata-pcue.ply", 100, false, false, 'y',true);
   latainf =  new ObjRevolucion("./plys/lata-pinf.ply", 50,'y');
   latasup =  new ObjRevolucion("./plys/lata-psup.ply", 50,'y');

  

   //cuadro = new Cuadro("./texturas/adoquin-1.jpg", 500.0);
   cuadro = new Cuadro("./texturas/verde.jpg", 500.0);
   skybox = new SkyBox("./texturas/sky-sphere.jpg");

   tiovivo = new ObjPLY("./plys/tiovivo.ply");
   noria = new ObjPLY("./plys/noria.ply");
   arbol = new ObjPLY("./plys/arbol.ply");
   farola = new ObjPLY("./plys/farola.ply");
   nubes = new ObjPLY("./plys/nubes.ply");
   persona = new ObjPLY("./plys/persona.ply");
   fuente = new ObjPLY("./plys/fuente.ply");
   avion = new ObjPLY("./plys/avion.ply");



   //lata9-esfera8-cono7-cilindro6-peon5-bigdodge4-beethoven3-ant2-tetraedro1-cubo0
   objetosEscena = 0; 


   //Vision de la escena ----------------------------------------------------------

   modoDibujado=true; //MODO DE DIBUJADO ( por defecto true es modo inmediato y false diferido)
  
   //COMPOSICION VISTA ESCENA:(Sombreado Luz Tapas Dibujado Puntos Lineas Solido Ajedrez ) 
   //ModoSeleccion-Seleccionado-luz encendida, con Tapas, Modo inmediato, Modo sólido por defecto (11110010)
   vision=242;//0011110010



   //Luces de la escena ----------------------------------------------------------
   //Luces Posicionales
   fuenteLuz0 = new LuzPosicional({0.0,150.0,0.0}, GL_LIGHT0, {0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0.4,0.4,0.4,1.0});
   fuenteLuz2 = new LuzPosicional({150.0,150.0,0.0}, GL_LIGHT2, {0.0,1.0,0.0,1.0},{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0});
   fuenteLuz4 = new LuzPosicional({0.0,-150.0,0.0}, GL_LIGHT4, {0.25,0.25,0.25,1.0},{0.25,0.25,0.25,1.0},{0.25,0.25,0.25,1.0});

   //Luces Dreccionales
   fuenteLuz1 = new LuzDireccional({45.0,60.0},GL_LIGHT1,{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0.4,0.4,0.4,1.0});
   fuenteLuz3 = new LuzDireccional({90.0,90.0},GL_LIGHT3,{0.0,0.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   
   
   lucesEscena = 19;
   gestionarluces = true;
   decrementarAlfa = false;
   decrementarBeta = false;
   incrementarAlfa = false;
   incrementarBeta = false;



   //Materiales de la escena -------------------------------------------------------
   Material mPerla( { 0.25, 0.20725, 0.20725, 0.922 },{0.296648, 0.296648, 0.296648, 0.922 }, {1.0, 0.829, 0.829, 0.922 } ,100.264);
   Material mOro( {0.75164,0.60648,0.22648,1.0}, {0.628281,0.555802,0.366065,1.0},{ 0.24725,0.1995,0.0745,1.0},51.2);
   Material mEsmeralda({ 0.0215, 0.1745, 0.0215, 0.55 },{0.633, 0.727811, 0.633, 0.55 },{0.07568, 0.61424, 0.07568, 0.55 },76.8) ;
   Material mRuby({ 0.1745, 0.01175, 0.01175, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, {0.61424, 0.04136, 0.04136, 0.55 }, 76.8);
   Material mPlata ({ 0.19225, 0.19225, 0.19225, 0.8},{ 0.508273, 0.508273, 0.508273,1.0}, { 0.50754, 0.50754, 0.50754,1.0}, 51.2);

   Material mBlancoDifuso({ 0.25,0.25,0.25,1.0 }, { 0.0,0.0,0.0,1.0}, { 1.0,1.0,1.0,1.0}, 0.0); //Difuso;

   Material mNegroESecular({ 0.0,0.0,0.0,1.0 }, { 1.0,1.0,1.0,1.0}, { 0.0,0.0,0.0,1.0}, 128.0); //Especular

   Material mBlanco({ 0.25,0.25,0.25,1.0 }, { 1.0,1.0,1.0,1.0}, { 1.0,1.0,1.0,1.0}, 100.0);
   Material mRojo({ 0.15, 0.00, 0.00, 1.00 }, {0.727811, 0.626959, 0.626959, 0.55}, { 0.332741, 0.328634, 0.346435, 0.82}, 100.0);
   Material mMarron({0.25, 0.148, 0.06475,1.0 }, { 0.18275, 0.17, 0.22525, 0.82}, { 0.332741, 0.328634, 0.346435, 0.82}, 100.0);
   Material mTurquesa({ 0.0, 0.15, 0.15, 1.0 }, { 1.0,1.0,1.0,1.0}, { 0.332741, 0.328634, 0.346435, 0.82}, 100.0);
   Material mObsidian({ 0.05375, 0.05, 0.06625, 0.82 }, { 0.18275, 0.17, 0.22525, 0.82}, { 0.332741, 0.328634, 0.346435, 0.82}, 100.0);

   //Especificar materiales
   cubo->setMaterial(mRuby);
   tetraedro->setMaterial(mRuby);

   ant->setMaterial(mEsmeralda);
   beethoven->setMaterial(mEsmeralda);
   bigdodge->setMaterial(mEsmeralda);

   peon->setMaterial(mNegroESecular);

   cilindro->setMaterial(mPerla);
   cono->setMaterial(mPerla);
   esfera->setMaterial(mPerla);

   latasup->setMaterial(mPlata);
   latainf->setMaterial(mPlata);


   tiovivo->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   noria->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{255.0,0.0,255.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   arbol->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   farola->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   nubes->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{255.0,255.0,255.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   persona->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   fuente->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{0.0,0.0,255.0},{255.0,0.0,0.0},{0.0,255.0,0.0});
   avion->setColor({0.0,255.0,255.0},{0.0,0.0,0.0},{0.0,0.0,255.0},{255.0,0.0,0.0},{0.0,255.0,0.0});


   tiovivo->setMaterial(mRojo);
   noria->setMaterial(mTurquesa);
   arbol->setMaterial(mMarron); 
   farola->setMaterial(mObsidian);
   nubes->setMaterial(mBlanco);
   persona->setMaterial(mNegroESecular);
   fuente->setMaterial(mPerla);
   avion->setMaterial(mPlata);

   //Animacion de la escena ------------------------------------------------------
   //Animacion automatica
   gestionarAAutomatica=true;
   restablecerValores=false;
   cteVelocidad = 0.03;
   velocidad = 0.25;

   //Animacion manual
   gestionarAManual =false;
   aumentarMan=false;
   gradosLibertad = 0;
   cteValor=0.05;


   //PRACTICA 5
   //Texturas ---------------------------------------------------------------------
   animarLuzPuntual = false;
   latacue->setTextura("./texturas/text-lata-1.jpg");

   esfera->setTextura("./texturas/text-world-map.jpg");

   //PRACTICA 6
   //Cámara. Interacción ---------------------------------------------------------------------
   camaras; //vector de camaras
   camaraActiva = 1; //de 0 a numero de camaras activas contiene el indice de la camara que se encuentra activa en el momento (inicialmente a la camara[1])
   estadoRaton = PARADO;
   //hayObjetoSeleccionado = false;

   Camara camara0({-300.0,100.0,-300.0},{100.0,0.0,0.0},{0.0,1.0,0.0},2,-70.0,70.0,-70.0, 70.0,Front_plane,Back_plane);
   Camara camara1({50.0,150.0,300.0},{-50.0,0.0,-300.0},1);
   Camara camara2({200.0,200.0,0.0},{-200,0.0,-200},1);

   camaras.push_back(camara0);
   camaras.push_back(camara1);
   camaras.push_back(camara2);

   verSeleccionables = false;


}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}


// **************************************************************************
// Practica4
// función de animacion Automatica del modelo jerarquico
// **************************************************************************
void Escena::animarModeloJerarquico(){
      
   if(gestionarAAutomatica){

      //Si se mulsa A se restablecen alpha y beta para que se coordinen pistones y brazos 
      if(restablecerValores){
         atraccion->restablecerValores();
         restablecerValores=false;
      }

      atraccion->movimientoPistonBrazo(velocidad);
   
      atraccion->modificaGiroEstructura(velocidad);
   }

   if(animarLuzPuntual){
      fuenteLuz0->animar(10);
   }
      
      
}

// **************************************************************************
// Practica 5
// función gestion de pulsacion de boton del raton
// **************************************************************************
void Escena::clickRaton( int boton , int estado , int x, int y){

	//std::cout << "Boton: " << boton << std::endl;
	//std::cout << "Estado: " << estado << std::endl;

   //std::cout << "GLUT_MIDDLE_BUTTON: " << GLUT_MIDDLE_BUTTON << std::endl;

   if( boton == GLUT_RIGHT_BUTTON ){ //SI SE PULSA EL BOTON DERECHO = Movimiento camara
      if ( estado == GLUT_DOWN ){ // Se pulsa el botón, por lo que se entra en el estado ’moviendo cámara’
         
         if(camaras[camaraActiva].getSeleccionaObjeto()){ //Si hay un objeto selccionado
            estadoRaton = MOVIENDO_CAMARA_EXAMINAR;
         }
         else{
            estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
         }
         xantCamara = x;
         yantCamara = y;

      }
      else{ // Se levanta el botón, por lo que se sale del estado ’moviendo cámara’
         estadoRaton = PARADO;
      }
      
   }
   else if(boton == 3 || boton == 4){ //SI SE hace scroll = Zoom

      if ( boton == 4 ){ // AUMENTAR
         camaras[camaraActiva].zoom(1.2);
         
      }
      else{ // DISMINUIR
         camaras[camaraActiva].zoom(1/1.2);
      }
   }
   else if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){ //SI SE PULSA EL BOTON IZQUIERDO = Seleccion de objeto
      //hayObjetoSeleccionado = true;
      //1-> Llamar al metodo dibujaSeleccion()
      dibujaSeleccion();
      //Leer pixel(x,y) y averiguar a qué objeto hemos asignado el color de dicho pixel
      processPick(x,y);

   }
   
      
}

// **************************************************************************
// Practica 5
// función gestion de movimiento del raton manteniendo pulsado algun boton
// Gestion del cambio de orientación de la cámara activa
// recibe la posicion del cursor
// **************************************************************************
void Escena::ratonMovido(int x, int y){
   //std::cout << "Escena X:" << X << " diferencia " << x-xantCamara << std::endl;
   //std::cout << "\tEscena Y:" << Y << " diferencia " << y-yantCamara  << std::endl;
   //si el boton que se ha pulsado en clickRaton ha sido el derecho se puede mover la cámara
   if ( estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON ) {
      camaras[camaraActiva].girarFirstPerson(x-xantCamara ,y-yantCamara );
      xantCamara = x;
      yantCamara = y;
   }
   else if(estadoRaton == MOVIENDO_CAMARA_EXAMINAR){
      camaras[camaraActiva].girarExaminar(x-xantCamara ,y-yantCamara );
      xantCamara = x;
      yantCamara = y;
   }

}


// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla


   if(glIsEnabled(GL_LIGHTING) == GL_TRUE) //Si las luces estan encedidas
      glDisable(GL_LIGHTING); //Desactivar las luces para pintar los ejes de color plano

	change_observer();

   
   ejes.draw();

   //mostrar menu principal en la terminal
   if(primerMenu){
      menuPrincipal();
      primerMenu = false;
   }
      


    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    // cubo.draw()
    // o
    // tetraedro.draw()

   //Activa el flag GL_CULL_FACE
   glEnable(GL_CULL_FACE);

   //Activa el flag GL_NORMALIZE para que no se altere su longitud con las transformaciones
   glEnable(GL_NORMALIZE);

   //----Luces Encendidas---- (Estan por defecto apagadas al llegar aquí)
   if( vision.test(6) ){   //Si las luces se quieren encendidas

      glEnable(GL_LIGHTING);  //Encender el cuadro de luces

      //Modificar la luz ambiente
      GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

      //Gestionar las luces a encender
      //---LUZ 0----
      if(lucesEscena.test(0)){
         fuenteLuz0->activar();
         glEnable(GL_LIGHT0);
      }
      else{
         glDisable(GL_LIGHT0);
      }
      //---LUZ 1----
      if(lucesEscena.test(1)){
         fuenteLuz1->activar();
         glEnable(GL_LIGHT1);
      }
      else{
         glDisable(GL_LIGHT1);
      }
      //---LUZ 2----
      if(lucesEscena.test(2)){
         fuenteLuz2->activar();
         glEnable(GL_LIGHT2);
      }
      else{
         glDisable(GL_LIGHT2);
      }
      //---LUZ 3----
      if(lucesEscena.test(3)){
         fuenteLuz3->activar();
         glEnable(GL_LIGHT3);
      }
      else{
         glDisable(GL_LIGHT3);
      }
      //---LUZ 4----
      if(lucesEscena.test(4)){
         fuenteLuz4->activar();
         glEnable(GL_LIGHT4);
      }
      else{
         glDisable(GL_LIGHT4);
      }


      //INFORMACIÓN DE LAS LUCES ENCENDIDAS
      if(gestionarluces){
         std::cout << "\t-----LUCES ENCENDIDAS:\t";
         if(glIsEnabled(GL_LIGHT0) == GL_TRUE)
            std::cout << "LUZ 0: SI\t";
         else
            std::cout << "LUZ 0: NO\t";

         if(glIsEnabled(GL_LIGHT1) == GL_TRUE)
            std::cout << "LUZ 1: SI\t";
         else
            std::cout << "LUZ 1: NO\t";

         if(glIsEnabled(GL_LIGHT2) == GL_TRUE)
            std::cout << "LUZ 2: SI\t";
         else
            std::cout << "LUZ 2: NO\t";

         if(glIsEnabled(GL_LIGHT3) == GL_TRUE)
            std::cout << "LUZ 3: SI\t" << std::endl;
         else
            std::cout << "LUZ 3: NO\t" << std::endl;
      }

      //Gestionar rotaciones 
      //LAS DIRECCIONALES SON LA 1 Y LA 3
      if(incrementarAlfa){
         bool variado = false;
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE ){
            fuenteLuz1->variarAnguloAlpha(20);
            variado = true;
            fuenteLuz1->activar();
         }
            
         if(glIsEnabled(GL_LIGHT3) == GL_TRUE){
            fuenteLuz3->variarAnguloAlpha(20);
            variado = true;
            fuenteLuz3->activar();
         }
            
         if(!variado)
            printf("\t--NO hay luces direccionales sobre las que variar alpha \n");
         else
           // printf("\t--Incrementando 20 grados alpa \n");

         incrementarAlfa = false;
      }

      if(incrementarBeta){
         bool variado = false;
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE ){
            fuenteLuz1->variarAnguloBeta(20);
            variado = true;
            fuenteLuz1->activar();
         }
            
         if(glIsEnabled(GL_LIGHT3) == GL_TRUE){
            fuenteLuz3->variarAnguloBeta(20);
            variado = true;
            fuenteLuz3->activar();
         }
            
         if(!variado)
            printf("\t--NO hay luces direccionales sobre las que variar beta \n");
         else
            //printf("\t--Incrementando 20 grados beta \n");
         incrementarBeta = false;
      }

      if(decrementarAlfa){
         bool variado = false;
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE ){
            fuenteLuz1->variarAnguloAlpha(-20);
            variado = true;
            fuenteLuz1->activar();
         }
            
         if(glIsEnabled(GL_LIGHT3) == GL_TRUE){
            fuenteLuz3->variarAnguloAlpha(-20);
            variado = true;
            fuenteLuz3->activar();
         }
            
         if(!variado)
            printf("\t--NO hay luces direccionales sobre las que variar alpha \n");
         else
           // printf("\t--Decrementando 20 grados alpa \n");
         decrementarAlfa = false;
      }

      if(decrementarBeta){
         bool variado = false;
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE ){
            fuenteLuz1->variarAnguloBeta(-20);
            variado = true;
            fuenteLuz1->activar();
         }
            
         if(glIsEnabled(GL_LIGHT3) == GL_TRUE){
            fuenteLuz3->variarAnguloBeta(-20);
            variado = true;
            fuenteLuz3->activar();
         }
            
         if(!variado)
            printf("\t--NO hay luces direccionales sobre las que variar beta \n");
         else
            //printf("\t--Decrementando 20 grados beta \n");
         decrementarBeta = false;
      }
      
      gestionarluces=false;
   
   }
   else{ 
      //Si no se requiere la luz entonces apagar las que nos quede encendidas
      if(glIsEnabled(GL_LIGHT0) == GL_TRUE)
         glDisable(GL_LIGHT3);
      
      if(glIsEnabled(GL_LIGHT1) == GL_TRUE)
         glDisable(GL_LIGHT3);
      
      if(glIsEnabled(GL_LIGHT2) == GL_TRUE)
         glDisable(GL_LIGHT3);

      if(glIsEnabled(GL_LIGHT3) == GL_TRUE)
         glDisable(GL_LIGHT3);

      //Apagar el cuadro de luces general
      glDisable(GL_LIGHTING);
   }

   //----Animacion----

   //ANIMACION MANUAL
   if(gestionarAManual){

      //Aumentar o disminuir el valor aplicado al grado de libertad seleccionado

      if(gradosLibertad.test(0)){
         if(aumentarMan)
            atraccion->aumentarAlturaPiston(cteValor);
         else
            atraccion->disminuirAlturaPiston(cteValor);
         
         //atraccion->modificaAlturaPiston(valor);
      }
      else if(gradosLibertad.test(1)){
         if(aumentarMan)
            atraccion->aumentarGiroZBrazos(cteValor);
         else
            atraccion->disminuirGiroZBrazos(cteValor);

         //atraccion->modificaGiroZBrazos(cteValor);
      }
      else if(gradosLibertad.test(2)){
         if(aumentarMan)
            atraccion->aumentarGiroEstructura(cteValor);
         else
            atraccion->disminuirGiroEstructura(cteValor);
         
         
         //atraccion->modificaGiroEstructura(cteValor);
      }

      gestionarAManual=false;
   }
   
   std::bitset<10> visionSeleccionable = vision;

   if(verSeleccionables)
      visionSeleccionable.set(9);
   else
      visionSeleccionable.set(9,0);
   


   //----Objetos----


   //SUELO
   glPushMatrix();
      //glTranslatef(0.0,50.0,-100.0);
      glRotatef(-90.0,1,0,0);
      cuadro->draw(vision,false);
   glPopMatrix();


   //CIELO
   glPushMatrix();
      glTranslatef(0.0,-150.0,0.0);
      skybox->draw(vision,false);
   glPopMatrix();

 

   //ATRACCION
   glPushMatrix();
      glTranslatef(-10.0,0.0,-300.0);
      glScalef(0.8,0.8,0.8);
      //Si esta seleccionado
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::ATRACCIONS)
         atraccion->draw(vision,true);
      else
         atraccion->draw(visionSeleccionable,false);
   glPopMatrix();

   //TIOVIVO
   glPushMatrix();
      glTranslatef(-250.0,0.0,-50.0);
      glScalef(0.3,0.3,0.3);
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::TIOVIVOS)
         tiovivo->draw(vision,true);
      else
         tiovivo->draw(visionSeleccionable,false);
   glPopMatrix();

   //NORIA
   glPushMatrix();
      glTranslatef(200.0,0.0,-250.0);
      glScalef(2.0,2.0,2.0);
      glRotatef(30.0,0,1,0);
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::NORIAS)
         noria->draw(vision,true);
      else
         noria->draw(visionSeleccionable,false);
   glPopMatrix();

   //NUBES
   glPushMatrix();
      glTranslatef(-100.0,200.0,0.0);
      glScalef(150.0,150.0,150.0);
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::NUBESS)
         nubes->draw(vision,true);
      else
         nubes->draw(visionSeleccionable,false);
   glPopMatrix();

   //FAROLA
   glPushMatrix();
      glTranslatef(270.0,0.0,0.0);
      glScalef(4.0,4.0,4.0);
      farola->draw(vision,false);
   glPopMatrix();

   //ARBOLES
   glPushMatrix();
      glTranslatef(300.0,50.0,50.0);
      glScalef(9.0,9.0,9.0);
      arbol->draw(vision,false);
   glPopMatrix();
   glPushMatrix();
      glTranslatef(300.0,50.0,-50.0);
      glScalef(9.0,9.0,9.0);
      arbol->draw(vision,false);
   glPopMatrix();

   //AVION
   glPushMatrix();
      glTranslatef(200.0,200.0,0.0);
      glScalef(10.0,10.0,10.0);
      glRotatef(-30.0,0,1,0);
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::AVIONS)
         avion->draw(vision,true);
      else
         avion->draw(visionSeleccionable,false);
   glPopMatrix();

   //FUENTE
   glPushMatrix();
      glScalef(110.0,110.0,110.0);
      //Si esta seleccionado
      if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::FUENTES)
         fuente->draw(vision,true);
      else
         fuente->draw(visionSeleccionable,false);
   glPopMatrix();

   
   //CUBO
   if(objetosEscena == 1){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(20,20,20);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::CUBOS)
            cubo->draw(vision,true);
         else
            cubo->draw(visionSeleccionable,false);
         
      glPopMatrix();
   }
        
   //TETRAEDRO
   if(objetosEscena == 2){
      glPushMatrix();
         glTranslatef(200.0,0.0,0.0);
         glScalef(30,30,30);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::TETRAEDROS)
            tetraedro->draw(vision,true);
         else
            tetraedro->draw(visionSeleccionable,false);
         
      glPopMatrix();
      
   }
    
   //ANT
   if(objetosEscena == 4){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(2,2,2);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::ANTS)
            ant->draw(vision,true);
         else
            ant->draw(visionSeleccionable,false);
         
      glPopMatrix();
      
   }         
     
   //BEETHOVEN
   if(objetosEscena == 8){
      glPushMatrix();
         glTranslatef(200.0,30.0,0.0);
         glScalef(4,4,4);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::BEETHOVENS)
            beethoven->draw(vision,true);
         else
            beethoven->draw(visionSeleccionable,false);
         
      glPopMatrix();
      
   }
     
   //BIGDODGE
   if(objetosEscena == 16){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(3,3,3);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::BIGDODGES)
            bigdodge->draw(vision,true);
         else
            bigdodge->draw(visionSeleccionable,false);
         
      glPopMatrix();
      
   }
   
   //PEON
   if(objetosEscena == 32){
      glPushMatrix();
         glTranslatef(200.0,20.0,0.0);
         glScalef(15,15,15);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::PEONS)
            peon->draw(vision,true);
         else
            peon->draw(visionSeleccionable,false);

      glPopMatrix();
   }

   //CILINDRO
   if(objetosEscena == 64){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(10.0,10.0,30.0);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::CILINDROS)
            cilindro->draw(vision,true);
         else
            cilindro->draw(visionSeleccionable,false);

      glPopMatrix();
      
   }
       
   //CONO 
   if(objetosEscena == 128){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(30.0,10.0,10.0);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::CONOS)
            cono->draw(vision,true);
         else
            cono->draw(visionSeleccionable,false);

      glPopMatrix();
      
   }
    
   //ESFERA
   if(objetosEscena == 256){
      glPushMatrix();
         glTranslatef(200.0,15.0,0.0);
         glScalef(15.0,15.0,15.0);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::ESFERAS)
            esfera->draw(vision,true); 
         else
            esfera->draw(visionSeleccionable,false); 
         
      glPopMatrix();
      
   }

   //LATA
   if(objetosEscena == 512){
      glPushMatrix();
         glTranslatef(200.0,0.0,0.0);
         glScalef(50,50,50);

         //Si esta seleccionado
         if(camaras[camaraActiva].getIndiceObjeto() == objetosSeleccionables::LATAS){
            latacue->draw(vision,true);
            latainf->draw(vision,true);
            latasup->draw(vision,true);
         }
         else{
            latacue->draw(visionSeleccionable,false);
            latainf->draw(visionSeleccionable,false);
            latasup->draw(visionSeleccionable,false);
         }

      glPopMatrix();
   }

   
}


void Escena::menuPrincipal(){
   std::cout << "\n----MENU PRINCIPAL:---- \n\t'S': Visualizar OBJETOS SELCCIONABLES de una forma especial\n\t'O': Objeto\n\t'V': Modo de Visualización\n\t'D': Modo de dibujado\n\t'T': Tapas\n\t'A': Animación Automática\n\t'M': Animación Manual\n\t'C': Selección cámara\n\t'Q': Salir\n";

}


//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;

   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;

   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            if(modoMenu == SELPLY || modoMenu == SELREVOLUCION ){
               modoMenu=SELOBJETO;
               cout << "\n----MENU SELECCION OBJETO:---- \n\t'C': Cubo\n\t'T': Tetraedro\n\t'Y': Objeto Ply\n\t'R': Objeto de Revolucion\n\t'Q': Atrás\n";
            }
            else {
               if(modoMenu == AMANUAL)
                  gradosLibertad=0;
               modoMenu=NADA; 
               cout << "\n----MENU PRINCIPAL:---- \n\t'S': Visualizar OBJETOS SELCCIONABLES de una forma especial\n\t'O': Objeto\n\t'V': Modo de Visualización\n\t'D': Modo de dibujado\n\t'T': Tapas\n\t'A': Animación Automática\n\t'M': Animación Manual\n\t'C': Selección cámara\n\t'Q': Salir\n";
            }  
         }            
         else {
            salir=true ;
         }
         break ;
   }

   //--------MENU PRINCIPAL-----------------------------------------------------------------
   if( modoMenu==NADA ){

      switch( toupper(tecla) )
      {
         case 'S' :
            // ESTAMOS EN MODO VISION DE LOS OBJETOS SELECCIONABLES DE UNA FORMA ESPECIAL
            if(!verSeleccionables){
               verSeleccionables = true;
               printf("Los objetos seleccionables se visualizan de forma especial\n");
            }
            else
               verSeleccionables = false;

            cout << "\n----MENU PRINCIPAL:---- \n\t'S': Visualizar OBJETOS SELCCIONABLES de una forma especial\n\t'O': Objeto\n\t'V': Modo de Visualización\n\t'D': Modo de dibujado\n\t'T': Tapas\n\t'A': Animación Automática\n\t'M': Animación Manual\n\t'Q': Salir\n";
            
            break ;
         case 'O' :
            // ESTAMOS EN MODO SELECCION DE OBJETO
            if(modoMenu==NADA){
               modoMenu=SELOBJETO; 
               printf("Opciones disponibles: \n\t'C': Cubo\n\t'T': Tetraedro\n\t'Y': Objeto Ply\n\t'R': Objeto de Revolucion\n\t'Q': Atrás\n");
            }
            break ;
         
         case 'V' :
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            if(modoMenu==NADA){
               modoMenu=SELVISUALIZACION;
               //printf("Opciones disponibles:\n\t'1': Luz Encendida\t'0': Luz Apagada\n\t'P': Puntos\t'L': Lineas\t'S': Solido\t'A': Ajedrez\n\t'Q': Atrás\n");
               //printf("Opciones disponibles:\n\t'L': Luz \t'S': Sombreado\n\t'X': PLSA(Puntos, Lineas, Solido o Ajedrez)\n\t'Q': Atrás\n");
               printf("Opciones disponibles:\n\t'P': Puntos\t'L': Lineas\t'S': Solido\t'A': Ajedrez\n\t'I': Iluminación\n\t'G': Sombreado suave(Gouraud)\t'F': Sombreado Plano\n\t'Q': Atrás\n");
               if(vision.test(6)){
                  printf("\tGestion Luces: \n\t\t'0': Fuente de Luz 0\t'1': Fuente de Luz 1\n\t\t'2': Fuente de Luz 2\t'3': Fuente de Luz 3\n\t\t'A': Alpha\t'B': Beta\n\t\t'<':  decrementa el ángulo\t'>':  incrementa el ángulo\n\t\t'P': se anima automáticamente la luz puntual\n");
               } 
            }  
            break ;

         case 'D' :
            // ESTAMOS EN MODO SELECCION DE DIBUJADO
            if(modoMenu==NADA){
               modoMenu=SELDIBUJADO;
               printf("Opciones disponibles: \n\t'1': Modo inmediato (usando glDrawElements)\n\t'2': Modo diferido(usando VBOs)\n\t'Q': Atrás\n");
            }
            break ;
            
         // COMPLETAR con los diferentes opciones de teclado

         case 'T' :
            if(modoMenu==NADA){
               modoMenu=SELTAPAS;
               printf("Opciones disponibles: \n\t'1': Con Tapas\n\t'2': Sin tapas\n\t'Q': Atrás\n");;
            }
            break ;

         case 'A' :
            // ESTAMOS EN MODO DE ANIMACION AUTOMATICA
            if(!gestionarAAutomatica){
               gestionarAAutomatica = true;
               restablecerValores=true;
               velocidad = 0.07;
               printf("Opciones disponibles: \n\t'+': Aumentar la velocidad de la animacion\n\t'-': Disminuir la velocidad de la animacion\n");
            }
            else
               gestionarAAutomatica = false;

            cout << "\n----MENU PRINCIPAL:---- \n\t'S': Visualizar OBJETOS SELCCIONABLES de una forma especial\n\t'O': Objeto\n\t'V': Modo de Visualización\n\t'D': Modo de dibujado\n\t'T': Tapas\n\t'A': Animación Automática\n\t'M': Animación Manual\n\t'Q': Salir\n";
            
            break ;

         case 'M' :
            // ESTAMOS EN MODO ANIMACION MANUAL
            if(modoMenu==NADA){
               //Desactivar animacion automatica
               gestionarAAutomatica = false;
               modoMenu=AMANUAL;
               printf("Opciones disponibles: \n\t'0': GL 0\n\t'1': GL 1\n\t'2': GL 2\n\t'+': Aumentar valor GL\n\t'-': Disminuir valor GL\n\t'>': Aumentar velocidad cambio\n\t'<: Disminuir velocidad de cambio\n\t'Q': Atrás\n");
                
            }
            break ;
         
         case 'C' :
            // ESTAMOS EN MODO SELECCION CAMARA
            if(modoMenu==NADA){
               modoMenu=CAMARA;
               printf("Opciones disponibles: \n\t'0': Ativar camara 0\n\t'1': Ativar camara 1\n\t'2': Ativar camara 2\n\t'Q': Atrás\n");
                
            }
            break ;
      }

   }


   //--------SELOBJETO-----------------------------------------------------------------
   if(modoMenu == SELOBJETO ){
      switch( toupper(tecla) )
      {
         case 'C' :
            if (objeto == NINGUNO) objeto = CUBO;
            else if(objeto == CUBO) objeto = NINGUNO;
            else objeto = CUBO;
            if(!objetosEscena.test(0)) objetosEscena = 1;
            else objetosEscena = 0;
            break ;
         
         case 'T' :
            if (objeto == NINGUNO) objeto = TETRAEDRO;
            else if(objeto == TETRAEDRO) objeto = NINGUNO;
            else objeto = TETRAEDRO;
            if(!objetosEscena.test(1)) objetosEscena = 2;
            else objetosEscena = 0;
            
            break ;
         
         case 'Y':
            modoMenu=SELPLY;
            objeto = OBJPLY;
            printf("Opciones disponibles: \n\t'A': Ant\t'B': Beethoven\t'D': Big Dodge\n\t'Q': Atrás\n");
            break;
         case 'R':
            modoMenu=SELREVOLUCION;
            objeto = OBJREVOLUCION;
            printf("Opciones disponibles: \n\t'P': Peon\t'C': Cilindro\t'X': Cono\t'E': Esfera\t'L': Lata\n\t'Q': Atrás\n");
            break;
      }
   }

   //--------SELVISUALIZACION----------------------------------------------------------
   //MODO DE VISUALIZACIÓN: PLSA (Puntos Lineas Solido Ajedrez)
   // si el bit no esta activado (1) se activa
   if (modoMenu == SELVISUALIZACION){
      switch( toupper(tecla) )
      {
         case 'P' :
            //Solo se gestiona si las luces están apagadas
            // if(vision.test(6)){ //Si las luces estan encendias las apaga
            //    printf("\tDebes apagar las luces para usar este modo\n\tPulsa 'I' descacctivar la iluminación y después 'P' para activar el modo puntos\n");
            //    //vision.set(6,0); vision.set(7,0);
            // }
            //else{ //Si las luces estan apagadas
               if(vision.test(0))//Si tiene activado el fal de ajedrez
                  printf("\tPulsa 'A' para desactivar el modo Ajedrez y después 'P' para cambiar el falg de modo puntos\n");
               else{
                  if(!vision.test(3)) vision.set(3);
                  else vision.set(3,0);
               }
            //}
            
            break ;
         
         case 'L' :
            //Solo se gestiona si las luces están apagadas
            if(vision.test(6)){ //Si las luces estan encendias
               printf("\tDebes apagar las luces para usar este modo\n\tPulsa 'I' descacctivar la iluminación y después 'L' para activar el modo lineas\n");
               //vision.set(6,0); vision.set(7,0);
            }
            else{ //Si las luces estan apagadas
               if(vision.test(0))//Si tiene activado el fal de ajedrez
                  printf("\tPulsa 'A' para desactivar el modo Ajedrez y después 'L' para cambiar el falg de modo líneas\n");
               else{
                  if(!vision.test(2)) vision.set(2);
                  else vision.set(2,0);
               }
            }
            break ;

         case 'S' :
            //Solo se gestiona si las luces están apagadas
            if(vision.test(6)){ //Si las luces estan encendias
               printf("\tDebes apagar las luces para usar este modo\n\tPulsa 'I' descacctivar la iluminación y después 'S' para activar el modo solido\n");
               //vision.set(6,0); vision.set(7,0);
            }
            else{ //Si las luces estan apagadas
               if(vision.test(0))//Si tiene activado el fal de ajedrez
               printf("\tPulsa 'A' para desactivar el modo Ajedrez y después 'S' para cambiar el falg de modo sólido\n");
               else{
                  if(!vision.test(1)) vision.set(1);
                  else vision.set(1,0);
               }
            }
            break ;
         
         case 'A' :
            if(!vision.test(6)){ //Si las luces están apagadas se gestiona el modo ajedrez
               //Solo se gestiona si las luces están apagadas
               if(vision.test(6)){ //Si las luces estan encendias
                  printf("\tDebes apagar las luces para usar este modo\n\tPulsa 'I' descacctivar la iluminación y después 'P' para activar el modo puntos\n");
                  //vision.set(6,0); vision.set(7,0);
               }
               else{ //Si las luces estan apagadas
                  if(!vision.test(0)) vision.set(0);
                  else vision.set(0,0);
               }
            }
            else { //Si las luces están encendidas a es gestionar alpha
               rotacionluz = ALPHA;
                  printf("\tSELCCIONADO ANGULO DE ROTACION SOBRE ALPHA\n");
            }
            break ;


         case 'I' :
            if(!vision.test(6)){
               vision.set(6);
               vision.set(7); //Encender el modo de sombreado suave al encender las luces
               gestionarluces = true;
               printf("Opciones disponibles: \n\t'0': Fuente de Luz 0\t'1': Fuente de Luz 1\n\t'2': Fuente de Luz 2\t'3': Fuente de Luz 3\n\t'A': Alpha\t'B': Beta\n\t'<':  decrementa el ángulo\t'>':  incrementa el ángulo\n\t\t'P': se anima automáticamente la luz puntual\n");

            } 
            else{
               vision.set(6,0); 
               vision.set(7,0);
               gestionarluces = false;
            }
            break ;
         
         case 'G' :
            //Solo se gestiona si las luces están encendidas
            if(!vision.test(6)){ //Si las luces estan apagadas
               printf("\tDebes encender las luces para usar este modo\n\tPulsa 'I' acctivar la iluminación y después 'G' para activar el sombreado suave\n");
            }
            else{ //Si las luces estan encendidas
               vision.set(7); 
            }
            
            break ;

         case 'F' :
            //Solo se gestiona si las luces están encendidas
            if(!vision.test(6)){ //Si las luces estan apagadas
               printf("\tDebes encender las luces para usar este modo\n\tPulsa 'I' acctivar la iluminación y después 'F' para activar el sombreado plano\n");
            }
            else{ //Si las luces estan encendidas
               vision.set(7,0);
            }
            break ;
         
      }
   }


   //--------SELDIBUJADO---------------------------------------------------------------
   //Modo de dibujado ( por defecto true o 1 en bitset es modo inmediato y false o 0 diferido)
   if(modoMenu == SELDIBUJADO){
      switch( toupper(tecla) )
      {
         case '1' :
            modoDibujado = true;
            vision.set(4);
            break ;
         
         case '2' :
            modoDibujado = false;
            vision.set(4,0);
            break ;
      }
   }

   //--------SELTAPAS---------------------------------------------------------------
   //1 = Con tapas ---- 2 = Sin Tapas
   if(modoMenu == SELTAPAS){
      switch( toupper(tecla) )
      {
         case '1' :
            vision.set(5);
            break ;
         
         case '2' :
            vision.set(5,0);
            break ;
      }
   }

   //--------SELPLY----------------------------------------------------------
   if (modoMenu == SELPLY){
      switch( toupper(tecla) )
      {
         case 'A' :
            if (objetoply == NONE) objetoply = ANT;
            else if(objetoply == ANT) objetoply = NONE;
            else objetoply = ANT;
            if(!objetosEscena.test(2)) objetosEscena = 4;
            else objetosEscena = 0;
            break ;
         
         case 'B' :
            if (objetoply == NONE) objetoply = BEETHOVEN;
            else if(objetoply == BEETHOVEN) objetoply = NONE;
            else objetoply = BEETHOVEN;
            if(!objetosEscena.test(3)) objetosEscena = 8;
            else objetosEscena = 0;
            break ;

         case 'D' :
            if (objetoply == NONE) objetoply = BIGDODGE;
            else if(objetoply == BIGDODGE) objetoply = NONE;
            else objetoply = BIGDODGE;
            if(!objetosEscena.test(4)) objetosEscena = 16;
            else objetosEscena = 0;
            break ;
      }
   }

   //--------SELREVOLUCION----------------------------------------------------------
   if (modoMenu == SELREVOLUCION){
      switch( toupper(tecla) )
      {
         case 'P' :
            if (objetorevolucion == NOTHING) objetorevolucion = PEON;
            else if(objetorevolucion  == PEON) objetorevolucion = NOTHING;
            else objetorevolucion = PEON;
            if(!objetosEscena.test(5)) objetosEscena = 32;
            else objetosEscena = 0;     
            break ;
         
         case 'C' :
            if (objetorevolucion == NOTHING) objetorevolucion = CILINDRO;
            else if(objetorevolucion == CILINDRO) objetorevolucion = NOTHING;
            else objetorevolucion = CILINDRO;
            if(!objetosEscena.test(6)) objetosEscena = 64;
            else objetosEscena = 0;
            break ;

         case 'X' :
            if (objetorevolucion == NOTHING) objetorevolucion = CONO;
            else if(objetorevolucion == CONO) objetorevolucion = NOTHING;
            else objetorevolucion = CONO;
            if(!objetosEscena.test(7)) objetosEscena = 128;
            else objetosEscena = 0;
            break ;

         case 'E' :
            if (objetorevolucion == NOTHING) objetorevolucion = ESFERA;
            else if(objetorevolucion == ESFERA) objetorevolucion = NOTHING;
            else objetorevolucion = ESFERA;
            if(!objetosEscena.test(8)) objetosEscena = 256;
            else objetosEscena = 0;
            break ;
         case 'L' :
            if (objetorevolucion == NOTHING) objetorevolucion = LATA;
            else if(objetorevolucion == LATA) objetorevolucion = NOTHING;
            else objetorevolucion = LATA;
            if(!objetosEscena.test(9)) objetosEscena = 512;
            else objetosEscena = 0;
            break ;
      }
   }

   //--------GESTION LUCES-----------------------------------------------------------------
   if( vision.test(6) && modoMenu == SELVISUALIZACION ){ //SI LAS LUCES ESTÁN ACTIVAS

      switch( toupper(tecla) )
      {

         case '0' :
            if(!lucesEscena.test(0))
               lucesEscena.set(0);
            else
               lucesEscena.set(0,0);

            gestionarluces = true;
            break ;

         case '1' :
            if(!lucesEscena.test(1))
               lucesEscena.set(1);
            else
               lucesEscena.set(1,0);

            gestionarluces = true;
            break ;
         
         case '2' :
            if(!lucesEscena.test(2))
               lucesEscena.set(2);
            else
               lucesEscena.set(2,0);

            gestionarluces = true;
            break ;

         case '3' :
            if(!lucesEscena.test(3))
               lucesEscena.set(3);
            else
               lucesEscena.set(3,0);

            gestionarluces = true;
            break ;

         //case A junto al modo ajedrez

         case 'B' :
            printf("\tSELCCIONADO ANGULO DE ROTACION SOBRE BETA\n");
            rotacionluz = BETA;
            break ;

         case '>' :
            if(rotacionluz == NO){
               printf("\tELIGE UN ANGULO SOBRE EL QUE INCREMENTAR EL VALOR  A--> ALFA B-->BETA\n");
            }
            else{
               if(rotacionluz == ALPHA){
                  incrementarAlfa = true;
               }
               if(rotacionluz == BETA){
                  incrementarBeta = true;    
               }
               
            }
            break ;

         case '<' :
            if(rotacionluz == NO){
               printf("\tELIGE UN ANGULO SOBRE EL DECREMENTAR EL VALOR   A--> ALFA B-->BETA\n");
            }
            else{
               if(rotacionluz == ALPHA){
                  decrementarAlfa = true;
               }
               if(rotacionluz == BETA){
                  decrementarBeta = true;
               }
            }
            break ;
         case 'P' :
            if(animarLuzPuntual){
               animarLuzPuntual = false;
               printf("\tStop animacion luz puntual\n");
            }
            else{
               animarLuzPuntual = true;
               printf("\tStart animacion luz puntual\n");
            }
            break ;
      }
   
   }

   //--------AAutomatica---------------------------------------------------------------
   if(gestionarAAutomatica){
      switch( toupper(tecla) )
      {
        case '+' :
            printf("\tAumentando velocidad de animacion...\n");
            velocidad += cteVelocidad;
            break ;
         
         case '-' :
            printf("\tDisminuyendo velocidad de animacion...\n");
            if (velocidad > 0)
               velocidad -= 0.025;
            break ;
      }
   }

   //--------AMANUAL---------------------------------------------------------------
   if(modoMenu == AMANUAL){
      switch( toupper(tecla) )
      {
         case '0' :
            if(!gradosLibertad.test(0)){
               printf("\tSELCCIONADO GRADO DE LIBERTAD 0\n");
               gradosLibertad.set(0);
               gradosLibertad.set(1,0);
               gradosLibertad.set(2,0);
               cteValor = 0.05;
            }
            break ;
         
         case '1' :
            if(!gradosLibertad.test(1)){
               printf("\tSELCCIONADO GRADO DE LIBERTAD 1\n");
               gradosLibertad.set(1);
               gradosLibertad.set(0,0);
               gradosLibertad.set(2,0);
               cteValor = 0.05;
            }
            break ;
         case '2' :
            if(!gradosLibertad.test(2)){
               printf("\tSELCCIONADO GRADO DE LIBERTAD 2\n");
               gradosLibertad.set(2);
               gradosLibertad.set(0,0);
               gradosLibertad.set(1,0);
               cteValor = 0.05;
            }
            break ;
         case '+' :
            aumentarMan=true;
            gestionarAManual = true;
            break ;
         
         case '-' :
            aumentarMan=false;
            gestionarAManual = true;
            break ;
         case '>' :
            printf("\tAumentando velocidad de animacion manual...\n");
            cteValor+=0.05;
            break ;
         
         case '<' :
            printf("\tDisminuyendo velocidad de animacion manual...\n");
            cteValor=cteValor/2;
            break ;
      }
   }

   //--------CAMARA---------------------------------------------------------------
   if(modoMenu == CAMARA){
      switch( toupper(tecla) )
      {
         case '0' :
            if(camaraActiva != 0){
               printf("\tCAMBIO A CÁMARA 0\n");
               camaraActiva = 0;
               change_projection(1.0);
            }
            break ;
         
         case '1' :
            if(camaraActiva != 1){
               printf("\tCAMBIO A CÁMARA 1\n");
               camaraActiva = 1;
               change_projection(1.0);
            }
            break ;
         case '2' :
            if(camaraActiva != 2){
               printf("\tCAMBIO A CÁMARA 2\n");
               camaraActiva = 2;
               change_projection(1.0);
            }
            break ;
      }
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         //Observer_angle_y-- ;
         camaras[camaraActiva].rotarY(-1.0);
         break;
	   case GLUT_KEY_RIGHT:
         //Observer_angle_y++ ;
         camaras[camaraActiva].rotarY(1.0);
         
         break;
	   case GLUT_KEY_UP:
         //Observer_angle_x-- ;
         camaras[camaraActiva].rotarX(-1.0);
         
         break;
	   case GLUT_KEY_DOWN:
         //Observer_angle_x++ ;
         camaras[camaraActiva].rotarX(1.0);
         break;
	   case GLUT_KEY_PAGE_UP:
         //Observer_distance *=1.2 ;
         camaras[camaraActiva].zoom(1.2);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         //Observer_distance /= 1.2 ;
         camaras[camaraActiva].zoom(1/1.2);
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   //const float wx = float(Height)*ratio_xy ;
   //glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   

   //Practica 6
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   for(int i = 0; i < camaras.size(); i++){
      camaras[i].setLeft(camaras[i].getBottom()*Width/Height);
      camaras[i].setRight(camaras[i].getTop()*Width/Height);
   }
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   //glTranslatef( 0.0, 0.0, -Observer_distance );
   //glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   //glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );

   //Practica 6
   camaras[camaraActiva].setObserver();
}


void Escena::dibujaSeleccion()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla

   change_observer();

   bool flagLuz, flagTExtura;

   if(glIsEnabled(GL_LIGHTING) == GL_TRUE) //Si las luces estan encedidas
      flagLuz = true;
   else
      flagLuz = false;

   if(glIsEnabled(GL_TEXTURE) == GL_TRUE) //Si las texturas estan activas
      flagTExtura= true;
   else
      flagTExtura = false;

   //Desactivar flags
   glDisable ( GL_DITHER ); // deshabilita el degradado
   glDisable ( GL_LIGHTING ); // deshabilita la luz
   glDisable ( GL_TEXTURE); // deshabilita las texturas

   std::bitset<10> visionSeleccion = 290; //ACTIVOS EL MODO SELECCION, CON TAPAS Y MODO SOLIDO
	
   if(vision.test(4))  //Si esta activo el bit de mod de dinujado se activa tambien en visionSeleccion
      visionSeleccion.set(4);
   else //Si no se desactiva
      visionSeleccion.set(4,0);


   //ATRACCION --> ROJO
   glPushMatrix();
      glTranslatef(-10.0,0.0,-300.0);
      glScalef(0.8,0.8,0.8);
      atraccion->setColorModoSeleccion({255.0,0.0,0.0});
      atraccion->draw(visionSeleccion,false);
   glPopMatrix();

   //TIOVIVO --> AZUL
   glPushMatrix();
      glTranslatef(-250.0,0.0,-50.0);
      glScalef(0.3,0.3,0.3);
      tiovivo->setColorModoSeleccion({0.0,0.0,255.0});
      tiovivo->draw(visionSeleccion,false);
   glPopMatrix();

   //NORIA --> VERDE
   glPushMatrix();
      glTranslatef(200.0,0.0,-250.0);
      glScalef(2.0,2.0,2.0);
      glRotatef(30.0,0,1,0);
      noria->setColorModoSeleccion({0.0,255.0,0.0});
      noria->draw(visionSeleccion,false);
   glPopMatrix();

   //NUBES --> MAGENTA
   glPushMatrix();
      glTranslatef(-100.0,200.0,0.0);
      glScalef(150.0,150.0,150.0);
      nubes->setColorModoSeleccion({255.0,0.0,255.0});
      nubes->draw(visionSeleccion,false);
   glPopMatrix();

   //AVION --> NEGRO
   glPushMatrix();
      glTranslatef(200.0,200.0,0.0);
      glScalef(10.0,10.0,10.0);
      glRotatef(-30.0,0,1,0);
      avion->setColorModoSeleccion({0.0,0.0,0.0});
      avion->draw(visionSeleccion,false);
   glPopMatrix();

   //FUENTE --> CYAN
   glPushMatrix();
      glScalef(110.0,110.0,110.0);
      fuente->setColorModoSeleccion({0.0,255.0,255.0});
      fuente->draw(visionSeleccion,false);
   glPopMatrix();

   //Objetos individuales de las practicas  --> AMARILLO  

   //CUBO
   if(objetosEscena == 1){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(20,20,20);
         cubo->setColorModoSeleccion({255.0,255.0,0.0});
         cubo->draw(visionSeleccion,false);
      glPopMatrix();
   }
        
   //TETRAEDRO
   if(objetosEscena == 2){
      glPushMatrix();
         glTranslatef(200.0,0.0,0.0);
         glScalef(30,30,30);
         tetraedro->setColorModoSeleccion({255.0,255.0,0.0});
         tetraedro->draw(visionSeleccion,false);
      glPopMatrix();
      
   }
    
   //ANT
   if(objetosEscena == 4){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(2,2,2);
         ant->setColorModoSeleccion({255.0,255.0,0.0});
         ant->draw(visionSeleccion,false);
      glPopMatrix();
      
   }         
     
   //BEETHOVEN
   if(objetosEscena == 8){
      glPushMatrix();
         glTranslatef(200.0,30.0,0.0);
         glScalef(4,4,4);
         beethoven->setColorModoSeleccion({255.0,255.0,0.0});
         beethoven->draw(visionSeleccion,false);
      glPopMatrix();
      
   }
     
   //BIGDODGE
   if(objetosEscena == 16){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(3,3,3);
         bigdodge->setColorModoSeleccion({255.0,255.0,0.0});
         bigdodge->draw(visionSeleccion,false);
      glPopMatrix();
      
   }
   
   //PEON
   if(objetosEscena == 32){
      glPushMatrix();
         glTranslatef(200.0,20.0,0.0);
         glScalef(15,15,15);
         peon->setColorModoSeleccion({255.0,255.0,0.0});
         peon->draw(visionSeleccion,false);
      glPopMatrix();
   }

   //CILINDRO
   if(objetosEscena == 64){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(10.0,10.0,30.0);
         cilindro->setColorModoSeleccion({255.0,255.0,0.0});
         cilindro->draw(visionSeleccion,false);
      glPopMatrix();
      
   }
       
   //CONO 
   if(objetosEscena == 128){
      glPushMatrix();
         glTranslatef(200.0,10.0,0.0);
         glScalef(30.0,10.0,10.0);
         cono->setColorModoSeleccion({255.0,255.0,0.0});
         cono->draw(visionSeleccion,false);
      glPopMatrix();
      
   }
    
   //ESFERA
   if(objetosEscena == 256){
      glPushMatrix();
         glTranslatef(200.0,15.0,0.0);
         glScalef(15.0,15.0,15.0);
         esfera->setColorModoSeleccion({255.0,255.0,0.0});
         esfera->draw(visionSeleccion,false);
      glPopMatrix();
      
   }

   //LATA
   if(objetosEscena == 512){
      glPushMatrix();
         glTranslatef(200.0,0.0,0.0);
         glScalef(50,50,50);
         latacue->setColorModoSeleccion({255.0,255.0,0.0});
         latainf->setColorModoSeleccion({255.0,255.0,0.0});
         latasup->setColorModoSeleccion({255.0,255.0,0.0});

         latacue->draw(visionSeleccion,false);
         latainf->draw(visionSeleccion,false);
         latasup->draw(visionSeleccion,false);
      glPopMatrix();
   }
   


   //Habilitar los flags que sean necesarios
   if(flagLuz) //Si las luces estaban encedidas
      glEnable( GL_LIGHTING ); // habilita la luz

   if(flagTExtura) //Si las texturas estanban activas
      glEnable( GL_TEXTURE); // habilita las texturas

   glEnable( GL_DITHER ); // habilita el degradado
       
}

void Escena::processPick (int x, int y) {
   GLint viewport[4];
   GLubyte pixel[3];

   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels( x, viewport[3]-y, 1, 1, GL_RGB,  GL_UNSIGNED_BYTE, (void *)pixel);


   //printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
   
   if(pixel[0] == 255.0 && pixel[1] == 0.0 && pixel[2] == 0.0){ //ROJO --> ATRACCION
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::ATRACCIONS ){
         printf ("Atraccion desseleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Atraccion seleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ATRACCIONS);
         camaras[camaraActiva].posicionarExaminar(-10.0,0.0,-300.0);
      }
   }
   else if (pixel[0] == 0.0 && pixel[1] == 255.0 && pixel[2] == 0.0 ) //VERDE --> NORIA
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::NORIAS ){
         printf ("Noria desseleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Noria seleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::NORIAS);
         camaras[camaraActiva].posicionarExaminar(200.0,0.0,-250.0);
      } 
   else if (pixel[0] == 0.0 && pixel[1] == 0.0 && pixel[2] ==  255.0 ) //AZUL --> TIOVIVO
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::TIOVIVOS ){
         printf ("Tiovivo desseleccionado");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Tiovivo seleccionado");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::TIOVIVOS);
         camaras[camaraActiva].posicionarExaminar(-250.0,0.0,-50.0);
      } 
   else if (pixel[0] == 0.0 && pixel[1] == 0.0 && pixel[2] == 0.0 ) //NEGRO --> AVION
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::AVIONS ){
         printf ("Avion desseleccionado");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Avion seleccionado");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::AVIONS);
         camaras[camaraActiva].posicionarExaminar(200.0,200.0,0.0);
      } 
   else if (pixel[0] == 0.0 && pixel[1] == 255.0 && pixel[2] == 255.0 ) //CYAN --> FUENTE
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::FUENTES ){
         printf ("Fuente desseleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Fuente seleccionada");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::FUENTES);
         camaras[camaraActiva].posicionarExaminar(0.0,0.0,0.0);
      } 
   else if (pixel[0] == 255.0 && pixel[1] == 0.0 && pixel[2] == 255.0 ) //MAGENTA --> NUBES
      if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::NUBESS ){
         printf ("Nubes desseleccionadas");
         camaras[camaraActiva].setSeleccionaObjeto(false);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
      }
      else{
         printf ("Nubes seleccionadas");
         camaras[camaraActiva].setSeleccionaObjeto(true);
         camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::NUBESS);
         camaras[camaraActiva].posicionarExaminar(-100.0,200.0,0.0);
      } 
   else if (pixel[0] == 255.0 && pixel[1] == 255.0 && pixel[2] == 0.0 ){ //AMARILLO --> OBJETO INDIVIDUAL DE LAS PRACTICAS
      if(objetosEscena == 1){ //CUBO
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::CUBOS ){
            printf ("Cubo desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Cubo seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::CUBOS);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }
      if(objetosEscena == 2){ //TETRAEDRO
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::TETRAEDROS ){
            printf ("Tetraedro desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Tetraedro seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::TETRAEDROS);
            camaras[camaraActiva].posicionarExaminar(200.0,0.0,0.0);
         }
      }
      if(objetosEscena == 4){ //ANT
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::ANTS ){
            printf ("Ants desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Ants seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANTS);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }
      if(objetosEscena == 8){ //BEETHOVEN
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::BEETHOVENS ){
            printf ("Beethoven desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Beethoven seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::BEETHOVENS);
            camaras[camaraActiva].posicionarExaminar(200.0,30.0,0.0);
         } 
      }
      if(objetosEscena == 16){ //BIGDODGE
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::BIGDODGES ){
            printf ("Bigdodge desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Bigdodge seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::BIGDODGES);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }
      if(objetosEscena == 32){ //PEON
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::PEONS ){
            printf ("Peon desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Peon seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::PEONS);
            camaras[camaraActiva].posicionarExaminar(200.0,20.0,0.0);
         }
      }
      if(objetosEscena == 64){ //CILINDRO
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::CILINDROS ){
            printf ("Cilindro desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Cilindro seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::CILINDROS);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }
      if(objetosEscena == 128){ //CONO
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::CONOS ){
            printf ("Cono desseleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Cono seleccionado");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::CONOS);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }
      if(objetosEscena == 256){ //ESFERA
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::ESFERAS ){
            printf ("Esfera desseleccionada");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Esfera seleccionada");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ESFERAS);
            camaras[camaraActiva].posicionarExaminar(200.0,15.0,0.0);
         }
      }
      if(objetosEscena == 512){ //LATA
         if( camaras[camaraActiva].getSeleccionaObjeto() && camaras[camaraActiva].getIndiceObjeto()==objetosSeleccionables::LATAS ){
            printf ("Lata desseleccionada");
            camaras[camaraActiva].setSeleccionaObjeto(false);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::ANY);
         }
         else{
            printf ("Lata seleccionada");
            camaras[camaraActiva].setSeleccionaObjeto(true);
            camaras[camaraActiva].setIndiceObjeto(objetosSeleccionables::LATAS);
            camaras[camaraActiva].posicionarExaminar(200.0,10.0,0.0);
         }
      }

   } 
   else
      printf("No se puede seleccionar");
   
   printf ("\n");

}
