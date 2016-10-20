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
 //crearObjetosEscena();
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
 // Dibujo de la escena
 // Dibujo de los ejes
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
 //glFlush();
 SwapBuffers(hdc);
 }

void __fastcall TGLForm3D::FormPaint(TObject *Sender)
 {
 GLScene();
 }

void __fastcall TGLForm3D::FormDestroy(TObject *Sender)
 {
 //liberarObjetosEscena();
 ReleaseDC(Handle,hdc);
 wglMakeCurrent(NULL,NULL);
 wglDeleteContext(hrc);
 }

void TGLForm3D::crearObjetosEscena()
 {
 }

void TGLForm3D::liberarObjetosEscena()
 {
 }




