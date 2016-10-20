#include <vcl.h>
#pragma hdrstop
#include "GLSkel3D.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;

__fastcall TGLForm3D::TGLForm3D(TComponent* Owner): TForm(Owner)
 {
 }

void __fastcall TGLForm3D::FormCreate(TObject *Sender)
 {
 // Datos por defecto
 hdc=GetDC(Handle);
 SetPixelFormatDescriptor();
 hrc=wglCreateContext(hdc);
 if(hrc==NULL)
  ShowMessage("Error CreateContex");
 if(wglMakeCurrent(hdc, hrc)==false)
  ShowMessage("Error MakeCurrent");
 glClearColor(0.6,0.7,0.8,1.0);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glEnable(GL_LIGHT0);
 GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
 glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
 GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
 glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
 PosicionLuz0[0]=25.0; PosicionLuz0[1]=25.0;
 PosicionLuz0[2]=0.0; PosicionLuz0[3]=1.0;
 glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
 glEnable(GL_COLOR_MATERIAL);
 glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 glShadeModel(GL_SMOOTH);
 // Escena
 crearObjetosEscena();
 // Cámara
 eyeX=100.0,
 eyeY=100.0,
 eyeZ=100.0,
 lookX=0.0,
 lookY=0.0,
 lookZ=0.0,
 upX=0;
 upY=1;
 upZ=0;
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);
 // Volumen de vista
 N=1; F=1000;
 xRight=10; xLeft=-xRight;
 yTop=10; yBot=-yTop;
 //Ratio del volumen de vista =1
 //ClientWidth=400;
 //ClientHeight=400;
 RatioViewPort=1.0;
 dibujaCoche=0;
 }

void __fastcall TGLForm3D::SetPixelFormatDescriptor()
 {
 PIXELFORMATDESCRIPTOR pfd=
  {
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
         0,0,0
  };
 int PixelFormat=ChoosePixelFormat(hdc,&pfd);
 SetPixelFormat(hdc,PixelFormat,&pfd);
 }

void __fastcall TGLForm3D::FormResize(TObject *Sender)
 {
 // Puerto de vista
 if ((ClientHeight<=1.0) || (ClientHeight<=1.0))  // Si el resize hace la ventana muy pequeña...
  {
  ClientWidth=400;  // ...se pone a 400x400 y...
  ClientHeight=400;
  RatioViewPort=1.0;  // ...con un ratio de 400/400=1
  }
 else  // Si el resize es adecuado se calcula el ratio de la ventana según el resize
  RatioViewPort=(GLfloat)ClientWidth/(GLfloat)ClientHeight;
 glViewport(0,0,ClientWidth,ClientHeight);
 // Volumen de vista
 GLfloat RatioVolVista=xRight/yTop;
 if (RatioVolVista>=RatioViewPort)  // Si el resize ha provocado que RatioVolVista>=RatioViewPort...
  {
  yTop= xRight/RatioViewPort;  // ...aumentamos yTop-yBot
  yBot=-yTop;
  }
 else  // Si el resize ha provocado que RatioVolVista<RatioViewPort...
  {
  xRight=RatioViewPort*yTop;  // ...aumentamos xRight-xLeft
  xLeft=-xRight;
  }
 // Modificación de la proyección por el resize
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(xLeft,xRight, yBot,yTop, N,F);
 GLScene();
 }

void __fastcall TGLForm3D::GLScene()
 {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);
 glBegin(GL_LINES);
  glColor4f(1.0,0.0,0.0,1.0);  // Eje x
  glVertex3d(0,0,0);
  glVertex3d(10,0,0);
  glColor4f(0.0,1.0,0.0,1.0);  // Eje y
  glVertex3d(0,0,0);
  glVertex3d(0,10,0);
  glColor4f(0.0,0.0,1.0,1.0);  // Eje z
  glVertex3d(0,0,0);
  glVertex3d(0,0,10);
 glEnd();
 glColor4f(1,1,1,1);
 dibuja();
 SwapBuffers(hdc);
 }

void __fastcall TGLForm3D::FormPaint(TObject *Sender)
 {
 GLScene();
 }

void __fastcall TGLForm3D::FormDestroy(TObject *Sender)
 {
 liberarObjetosEscena();
 ReleaseDC(Handle,hdc);
 wglMakeCurrent(NULL,NULL);
 wglDeleteContext(hrc);
 }

void TGLForm3D::crearObjetosEscena()
 {
 activa=0;
 }

void TGLForm3D::liberarObjetosEscena()
 {
 activa=0;
 if (hipotrocoide!=NULL)
  delete hipotrocoide;
 }

void __fastcall TGLForm3D::Hipotrocoide1Click(TObject *Sender)
 {
 if (hipotrocoide!=NULL)
  delete hipotrocoide;
 activa=HIPOTROCOIDE;
 // Hipotrocoide enunciado - menor a mayor precisión
 //hipotrocoide=new Hipotrocoide3D(8,15,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(16,20,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(20,30,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(30,60,7,4,2);
 // Hipotrocoide pke
 //hipotrocoide=new Hipotrocoide3D(16,52,7,4,7);
 // Mi hipotrocoide - menor a mayor precisión
 //hipotrocoide=new Hipotrocoide3D(10,30,11,5,8);
 hipotrocoide=new Hipotrocoide3D(15,40,11,5,8);
 //hipotrocoide=new Hipotrocoide3D(20,60,11,5,8);
 dibujaCoche=false;
 GLScene();
 }

void __fastcall TGLForm3D::Hipotrocoidecoche1Click(TObject *Sender)
 {
 if (hipotrocoide!=NULL)
  delete hipotrocoide;
 activa=HIPOTROCOIDE_COCHE;
 // Hipotrocoide enunciado - menor a mayor precisión
 //hipotrocoide=new Hipotrocoide3D(8,15,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(16,20,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(20,30,7,4,2);
 //hipotrocoide=new Hipotrocoide3D(30,60,7,4,2);
 // Hipotrocoide pke
 //hipotrocoide=new Hipotrocoide3D(16,52,7,4,7);
 // Mi hipotrocoide - menor a mayor precisión
 //hipotrocoide=new Hipotrocoide3D(10,30,11,5,8);
 hipotrocoide=new Hipotrocoide3D(15,40,11,5,8);
 //hipotrocoide=new Hipotrocoide3D(20,60,11,5,8);
 dibujaCoche=true;
 GLScene();
 }

void TGLForm3D::dibuja()
 {
 switch (activa)
  {
  case HIPOTROCOIDE:
   {
   glPushMatrix();
   hipotrocoide->dibuja(false);
   if (dibujaCoche)
    hipotrocoide->dibujaCoche();
   glPopMatrix();
   break;
   }
  case HIPOTROCOIDE_COCHE:
   {
   glPushMatrix();
   hipotrocoide->dibuja(true);
   if (dibujaCoche)
    hipotrocoide->dibujaCoche();
   glPopMatrix();
   break;
   }
  default: break;
  }
 }

void __fastcall TGLForm3D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
 {
 if (activa==HIPOTROCOIDE)
  {
  switch (Key)
   {
   // Tecla: IZQUIERDA, eje x
   case 37:
    hipotrocoide->setGiro(1,0);
    break;
   // Tecla: DERECHA, eje x
   case 39:
    hipotrocoide->setGiro(1,1);
    break;
   // Tecla: ABAJO, eje y
   case 40:
    hipotrocoide->setGiro(2,0);
    break;
   // Tecla: ARRIBA, eje y
   case 38:
    hipotrocoide->setGiro(2,1);
    break;
   // Tecla: A, eje z
   case 65:
    hipotrocoide->setGiro(3,0);
    break;
   // Tecla: Z, eje z
   case 90:
    hipotrocoide->setGiro(3,1);
    break;
   }
  GLScene();
  }
 else if (activa==HIPOTROCOIDE_COCHE)
  {
  switch (Key)
   {
   // Tecla: Q, mover hacia adelante
   case 81:
    hipotrocoide->setCoche(true);
    break;
   // Tecla: W, mover hacia atrás
   case 87:
    hipotrocoide->setCoche(false);
    break;
   }
  GLScene();
  }
 }

