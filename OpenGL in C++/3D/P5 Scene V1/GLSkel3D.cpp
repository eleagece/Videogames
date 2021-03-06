#include <vcl.h>
#pragma hdrstop
#include "GLSkel3D.h"
#include <sstream>
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;

//****************************************************************************//
//*** Creaci�n/destrucci�n del formulario ************************************//
//****************************************************************************//
__fastcall TGLForm3D::TGLForm3D(TComponent* Owner): TForm(Owner)
 {
 }

void __fastcall TGLForm3D::FormCreate(TObject *Sender)
 {
 //---- Constructora por defecto ---------------------------------------------//
 //---------------------------------------------------------------------------//
 // ????????????????????????????????????????????????????????????????????????????
 hdc=GetDC(Handle);
 SetPixelFormatDescriptor();
 hrc=wglCreateContext(hdc);
 if(hrc==NULL) ShowMessage("Error CreateContex");
 if(wglMakeCurrent(hdc, hrc)==false) ShowMessage("Error MakeCurrent");
 glClearColor(0.6,0.7,0.8,1.0);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glEnable(GL_LIGHT0);
 GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
 glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
 GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
 glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
 PosicionLuz0[0]=25.0; PosicionLuz0[1]=15.0;
 PosicionLuz0[2]=0.0; PosicionLuz0[3]=1.0;
 glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
 glEnable(GL_COLOR_MATERIAL);
 glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 glShadeModel(GL_SMOOTH);
 // ????????????????????????????????????????????????????????????????????????????
 crearMenu();  // Inicia el men� a los valores correctos
 crearEscena();  // Crea los objetos de la escena
 crearCamara();  // Crea la c�mara que visualiza la escena
 }

void __fastcall TGLForm3D::SetPixelFormatDescriptor()
 {
 //---- SetPixelFormatDescriptor() -------------------------------------------//
 //-- ????????????????????????????????????????????????????????????????????? --//
 //---------------------------------------------------------------------------//
 // ????????????????????????????????????????????????????????????????????????????
 PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0 };
 int PixelFormat=ChoosePixelFormat(hdc,&pfd);
 SetPixelFormat(hdc,PixelFormat,&pfd);
 // ????????????????????????????????????????????????????????????????????????????
 }

void TGLForm3D::crearMenu()
 {
 //---- crearMenu() ----------------------------------------------------------//
 //-- M�todo auxiliar de la constructora para preparar el men�              --//
 //---------------------------------------------------------------------------//
 // Elementos del men� Ortogonal
 Esquina2->Checked=true;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 // Elementos del men� Perspectiva
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 // Elementos del men� Obl�cua
 Oblcua2->Checked=false;
 // Elementos del men� Objeto
 Escena2->Checked=true;
 Muebles2->Checked=false;
 Lmpara2->Checked=false;
 }

void TGLForm3D::crearEscena()
 {
 //---- crearEscena() --------------------------------------------------------//
 //-- M�todo auxiliar de la constructora para crear la escena               --//
 //---------------------------------------------------------------------------//
 escena=new Escena();
 selec=1;  // La escena est� seleccionada de manera predeterminada
 }

void TGLForm3D::crearCamara()
 {
 //---- crearCamara() --------------------------------------------------------//
 //-- M�todo auxiliar de la constructora para crear la c�mara               --//
 //---------------------------------------------------------------------------//
 // C�mara
 PV3d* eye=new PV3d(100.0,100.0,100.0,1);
 PV3d* look=new PV3d(0.0,3.3,0.0,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 this->usercam=new Camara(eye,look,up);
 // Volumen de vista
 xRight=10; xLeft=-xRight; yTop=10; yBot=-yTop; N=1; F=1000;
 usercam->setLimits(xLeft,xRight,yBot,yTop,N,F);  // Se indica a la c�mara los valores del volumen de vista
 usercam->setTipoP(ORTO);  // Se indica a la c�mara que estamos en proyecci�n ortogonal
 usercam->setProyeccion();  // Se hace la proyecci�n
 }

void __fastcall TGLForm3D::FormDestroy(TObject *Sender)
 {
 //---- Destructora ----------------------------------------------------------//
 //---------------------------------------------------------------------------//
 // ????????????????????????????????????????????????????????????????????????????
 ReleaseDC(Handle,hdc);
 wglMakeCurrent(NULL,NULL);
 wglDeleteContext(hrc);
 // ????????????????????????????????????????????????????????????????????????????
 liberarEscena();
 liberarCamara();
 }

void TGLForm3D::liberarEscena()
 {
 //---- liberarEscena() ------------------------------------------------------//
 //-- M�todo auxiliar de la constructora para eliminar la escena            --//
 //---------------------------------------------------------------------------//
 delete escena;
 }

void TGLForm3D::liberarCamara()
 {
 //---- crearMenu() ----------------------------------------------------------//
 //-- M�todo auxiliar de la constructora para eliminar la c�mara            --//
 //---------------------------------------------------------------------------//
 delete usercam;
 }

//****************************************************************************//
//*** Acciones sobre el formulario *******************************************//
//****************************************************************************//
void __fastcall TGLForm3D::FormResize(TObject *Sender)
 {
 //---- FormResize(...) ------------------------------------------------------//
 //-- Lo que ocurre al redimensionar el formulario                          --//
 //---------------------------------------------------------------------------//
 }

void __fastcall TGLForm3D::FormPaint(TObject *Sender)
 {
 //---- FormPaint(...) -------------------------------------------------------//
 //-- Lo que ocurre al pintarse el formulario                               --//
 //---------------------------------------------------------------------------//
 GLScene();
 }

//****************************************************************************//
//*** M�todos comunes ********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::GLScene()
 {
 //---- GLScene() ------------------------------------------------------------//
 //-- M�todo que llama a dibuja() de la escena                              --//
 //---------------------------------------------------------------------------//
 // ????????????????????????????????????????????????????????????????????????????
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);
 // ????????????????????????????????????????????????????????????????????????????
 glMatrixMode(GL_MODELVIEW);
 escena->dibuja();
 SwapBuffers(hdc);
 }

//****************************************************************************//
//*** Tool Bar: Roll *********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::RollDownClick(TObject *Sender)
 {
 //---- RollDownClick(...) ---------------------------------------------------//
 //-- La c�mara hace un roll hacia la izquierda                             --//
 //---------------------------------------------------------------------------//
 usercam->roll(5.0);
 GLScene();
 }

void __fastcall TGLForm3D::RollUpClick(TObject *Sender)
 {
 //---- RollUpClick(...) -----------------------------------------------------//
 //-- La c�mara hace un roll hacia la derecha                               --//
 //---------------------------------------------------------------------------//
 usercam->roll(-5.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Yaw **********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::YawDownClick(TObject *Sender)
 {
 //---- YawDownClick(...) ----------------------------------------------------//
 //-- La c�mara hace un yaw hacia la izquierda                              --//
 //---------------------------------------------------------------------------//
 usercam->yaw(5.0);
 GLScene();
 }

void __fastcall TGLForm3D::YawUpClick(TObject *Sender)
 {
 //---- YawUpClick(...) ------------------------------------------------------//
 //-- La c�mara hace un yaw hacia la derecha                                --//
 //---------------------------------------------------------------------------//
 usercam->yaw(-5.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Pitch ********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::PitchDownClick(TObject *Sender)
 {
 //---- PitchDownClick(...) --------------------------------------------------//
 //-- La c�mara hace un pitch hacia abajo                                   --//
 //---------------------------------------------------------------------------//
 usercam->pitch(5.0);
 GLScene();
 }

void __fastcall TGLForm3D::PitchUpClick(TObject *Sender)
 {
 //---- PitchUpClick(...) ----------------------------------------------------//
 //-- La c�mara hace un pitch hacia arriba                                  --//
 //---------------------------------------------------------------------------//
 usercam->pitch(-5.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Move X *******************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::XDownClick(TObject *Sender)
 {
 //---- XDownClick(...) ------------------------------------------------------//
 //-- La c�mara se desplaza hacia atr�s en su eje x                         --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(-1.0,0.0,0.0);
 GLScene();
 }

void __fastcall TGLForm3D::XUpClick(TObject *Sender)
 {
 //---- XUpClick(...) --------------------------------------------------------//
 //-- La c�mara se desplaza hacia delante en su eje x                       --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(1.0,0.0,0.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Move Y *******************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::YDownClick(TObject *Sender)
 {
 //---- YDownClick(...) ------------------------------------------------------//
 //-- La c�mara se desplaza hacia atr�s en su eje y                         --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(0.0,-1.0,0.0);
 GLScene();
 }

void __fastcall TGLForm3D::YUpClick(TObject *Sender)
 {
 //---- YUpClick(...) --------------------------------------------------------//
 //-- La c�mara se desplaza hacia delante en su eje y                       --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(0.0,1.0,0.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Move Z *******************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::ZDownClick(TObject *Sender)
 {
 //---- ZDownClick(...) ------------------------------------------------------//
 //-- La c�mara se desplaza hacia atr�s en su eje z                         --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(0.0,0.0,-1.0);
 GLScene();
 }

void __fastcall TGLForm3D::ZUpClick(TObject *Sender)
 {
 //---- ZUpClick(...) --------------------------------------------------------//
 //-- La c�mara se desplaza hacia delante en su eje z                       --//
 //---------------------------------------------------------------------------//
 usercam->desplazamiento(0.0,0.0,1.0);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Rotar ********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::RotaXDownClick(TObject *Sender)
 {
 //---- XDownClick(...) ------------------------------------------------------//
 //-- El objeto seleccionado gira -10� sobre el eje                         --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,-10,1,0,0);
 GLScene();
 }

void __fastcall TGLForm3D::RotaXUpClick(TObject *Sender)
 {
 //---- XUpClick(...) --------------------------------------------------------//
 //-- El objeto seleccionado gira 10� sobre el eje x                        --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,10,1,0,0);
 GLScene();
 }

void __fastcall TGLForm3D::RotaYDownClick(TObject *Sender)
 {
 //---- YDownClick(...) ------------------------------------------------------//
 //-- El objeto seleccionado gira -10� sobre el eje y                       --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,-10,0,1,0);
 GLScene();
 }

void __fastcall TGLForm3D::RotaYUpClick(TObject *Sender)
 {
 //---- YUpClick(...) --------------------------------------------------------//
 //-- El objeto seleccionado gira 10� sobre el eje y                        --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,10,0,1,0);
 GLScene();
 }

void __fastcall TGLForm3D::RotaZDownClick(TObject *Sender)
 {
 //---- ZUpClick(...) --------------------------------------------------------//
 //-- El objeto seleccionado gira -10� sobre el eje z                       --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,-10,0,0,1);
 GLScene();
 }

void __fastcall TGLForm3D::RotaZUpClick(TObject *Sender)
 {
 //---- ZUpClick(...) --------------------------------------------------------//
 //-- El objeto seleccionado gira 10� sobre el eje z                        --//
 //---------------------------------------------------------------------------//
 escena->rota(selec,10,0,0,1);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Escalar ******************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::EscalaDownClick(TObject *Sender)
 {
 //---- EscalaDownClick(...) -------------------------------------------------//
 //-- El objeto seleccionado se hace m�s peque�o                            --//
 //---------------------------------------------------------------------------//
 escena->escala(selec,0.9,0.9,0.9);
 GLScene();
 }

void __fastcall TGLForm3D::EscalaUpClick(TObject *Sender)
 {
 //---- EscalaUpClick(...) ---------------------------------------------------//
 //-- El objeto seleccionado se hace m�s grande                             --//
 //---------------------------------------------------------------------------//
 escena->escala(selec,1.1,1.1,1.1);
 GLScene();
 }

//****************************************************************************//
//*** Tool Bar: Trasladar ****************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::TraslXDownClick(TObject *Sender)
 {
 //---- TraslXDownClick(...) -------------------------------------------------//
 //-- El objeto seleccionado se traslada -1 en eje x                        --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,-1,0,0);
 GLScene();
 }

void __fastcall TGLForm3D::TraslXUpClick(TObject *Sender)
 {
 //---- TraslXUpClick(...) ---------------------------------------------------//
 //-- El objeto seleccionado se traslada 1 en eje x                         --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,1,0,0);
 GLScene();
 }

void __fastcall TGLForm3D::TraslYDownClick(TObject *Sender)
 {
 //---- TraslYDownClick(...) -------------------------------------------------//
 //-- El objeto seleccionado se traslada -1 en eje y                        --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,0,-1,0);
 GLScene();
 }

void __fastcall TGLForm3D::TraslYUpClick(TObject *Sender)
 {
 //---- TraslYUpClick(...) ---------------------------------------------------//
 //-- El objeto seleccionado se traslada 1 en eje y                         --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,0,1,0);
 GLScene();
 }

void __fastcall TGLForm3D::TraslZDownClick(TObject *Sender)
 {
 //---- TraslZDownClick(...) -------------------------------------------------//
 //-- El objeto seleccionado se traslada -1 en eje z                        --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,0,0,-1);
 GLScene();
 }

void __fastcall TGLForm3D::TraslZUpClick(TObject *Sender)
 {
 //---- TraslZUpClick(...) ---------------------------------------------------//
 //-- El objeto seleccionado se traslada 1 en eje z                         --//
 //---------------------------------------------------------------------------//
 escena->traslada(selec,0,0,1);
 GLScene();
 }

//****************************************************************************//
//*** Men�: Ortogonal ********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::Esquina2Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Ortogonal->Esquina'
 Esquina2->Checked=true;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n ortogonal
 usercam->setTipoP(ORTO);  // Se indica a la c�mara que estamos en proyecci�n ortogonal
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(100.0,100.0,100.0,1);
 PV3d* look=new PV3d(0.0,3.3,0.0,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

void __fastcall TGLForm3D::Cenital2Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Ortogonal->Cenital'
 Esquina2->Checked=false;
 Cenital2->Checked=true;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n ortogonal
 usercam->setTipoP(ORTO);  // Se indica a la c�mara que estamos en proyecci�n ortogonal
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(3,100,2,1);
 PV3d* look=new PV3d(3,0,2,1);
 PV3d* up=new PV3d(0,0,-1,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

void __fastcall TGLForm3D::Lateral2Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Ortogonal->Lateral'
 Esquina2->Checked=false;
 Cenital2->Checked=false;
 Lateral2->Checked=true;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n ortogonal
 usercam->setTipoP(ORTO);  // Se indica a la c�mara que estamos en proyecci�n ortogonal
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(100,6,2.3,1);
 PV3d* look=new PV3d(0.0,6,2.3,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

void __fastcall TGLForm3D::Frontal2Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Ortogonal->Frontal'
 Esquina2->Checked=false;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=true;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n ortogonal
 usercam->setTipoP(ORTO);  // Se indica a la c�mara que estamos en proyecci�n ortogonal
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(3.0,6,100,1);
 PV3d* look=new PV3d(3.0,6,0.0,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

//****************************************************************************//
//*** Men�: Perspectiva ******************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::HabitacinInferior1Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Perspectiva->Habitaci�n inferior'
 Esquina2->Checked=false;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=true;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n perspectiva
 usercam->setTipoP(PERS);  // Se indica a la c�mara que estamos en proyecci�n perspectiva
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(-6,4,8.5,1);
 PV3d* look=new PV3d(0,0,0,1);
 PV3d* up=new PV3d(0,1.0,0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

void __fastcall TGLForm3D::Habitacinsuperior1Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Perspectiva->Habitaci�n superior'
 Esquina2->Checked=false;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=true;
 Oblcua2->Checked=false;
 // Establecemos la proyecci�n perspectiva
 usercam->setTipoP(PERS);  // Se indica a la c�mara que estamos en proyecci�n perspectiva
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(14,9,8.5,1);
 PV3d* look=new PV3d(0.0,0.0,0.0,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

//****************************************************************************//
//*** Men�: Obl�cua **********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::Oblcua2Click(TObject *Sender)
 {
 // En el men�, en las proyecciones, s�lo aparece con tick la opci�n 'Obl�cua'
 Esquina2->Checked=false;
 Cenital2->Checked=false;
 Lateral2->Checked=false;
 Frontal2->Checked=false;
 HabitacinInferior1->Checked=false;
 Habitacinsuperior1->Checked=false;
 Oblcua2->Checked=true;
 // Establecemos la proyecci�n perspectiva
 usercam->setTipoP(OBLI);  // Se indica a la c�mara que estamos en proyecci�n obl�cua
 usercam->setVO(0.09,0.09,1);  // Se establece el vector de la proyecci�n obl�cua muy cercano a (1,1,1)
 usercam->setProyeccion();
 // Establecemos la c�mara
 glMatrixMode(GL_MODELVIEW);
 PV3d* eye=new PV3d(5.0,5.0,10.0,1);
 PV3d* look=new PV3d(5.0,5.0,0.0,1);
 PV3d* up=new PV3d(0.0,1.0,0.0,0);
 usercam->setView(eye,look,up);
 GLScene();
 }

//****************************************************************************//
//*** Men�: Objeto ***********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::Escena2Click(TObject *Sender)
 {
 Escena2->Checked=true;
 Muebles2->Checked=false;
 Lmpara2->Checked=false;
 selec=1;
 }

void __fastcall TGLForm3D::Muebles2Click(TObject *Sender)
 {
 Escena2->Checked=false;
 Muebles2->Checked=true;
 Lmpara2->Checked=false;
 selec=2;
 }

void __fastcall TGLForm3D::Lmpara2Click(TObject *Sender)
 {
 Escena2->Checked=false;
 Muebles2->Checked=false;
 Lmpara2->Checked=true;
 selec=3;
 }

//****************************************************************************//
//*** Men�: Acci�n ***********************************************************//
//****************************************************************************//
void __fastcall TGLForm3D::Puerta1Click(TObject *Sender)
 {
 escena->setPuerta();
 GLScene();
 }

void __fastcall TGLForm3D::TV1Click(TObject *Sender)
 {
 escena->setTV();
 GLScene();
 }
