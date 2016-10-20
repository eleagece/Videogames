//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormCreate(TObject *Sender)
{
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    	ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
    	ShowMessage("Could not MakeCurrent");
    //Cor de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicializaci�n del volumen de vista
    xRight=250.0; xLeft=-xRight;
    yTop=xRight; yBot=-yTop;
    //Radio del volumen de vista == 1

    //inicializaci�n del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;
    
    // inicializaci�n de las variables del programa
    _escena=new Escena();
    _closing=false;
    posTestigo=200;
    _escena->DaTestigo(posTestigo);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
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
    int PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------
void __fastcall TGLForm2D::FormResize(TObject *Sender)
{

 //se actualiza puerto de vista y su radio
  if ((ClientWidth<=1)||(ClientHeight<=1)){
     ClientWidth=500;
     ClientHeight=500;
     RatioViewPort=1.0;
     }
  else RatioViewPort= (float)ClientWidth/(float)ClientHeight;

  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  // para que su radio coincida con ratioViewPort
  GLdouble RatioVolVista=xRight/yTop;

  if (RatioVolVista>=RatioViewPort){
     //Aumentamos yTop-yBot
     yTop= xRight/RatioViewPort;
     yBot=-yTop;
     }
  else{
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }
  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft,xRight, yBot,yTop);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLScene();

}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
{
glClear(GL_COLOR_BUFFER_BIT);

// comandos para dibujar la escena
if (!_closing)
_escena->dibuja();

glFlush();
SwapBuffers(hdc);
}

//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    // eliminar objetos creados
    _closing=true;
    delete _escena;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Inicio11Click(TObject *Sender)
{
        _escena->inicia1(false);
        GLScene();
}
//---------------------------------------------------------------------------


void __fastcall TGLForm2D::Timer1Timer(TObject *Sender)
{
        _escena->timeout();
        GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Salir1Click(TObject *Sender)
{
        Application->Terminate();        
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Inicio21Click(TObject *Sender)
{
        _escena->inicia1(true);
        GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch (Key)
   {
   /*case 39:  // Tecla derecha -> mover derecha
    if (posTestigo>=1 && posTestigo<1600)
     posTestigo++;
    else if (posTestigo==1600)
     posTestigo=1;
    break;
   case 37:  // Tecla Izquierda -> mover izquierda
    if (posTestigo<=1600 && posTestigo>1)
     posTestigo--;
    else if (posTestigo==1)
     posTestigo=1600;
    break;
   case 38:  // Tecla arriba -> disparar
    _escena->inicia1(true);
    break;*/
   case 39:  // Tecla derecha -> mover derecha
    if (posTestigo>=1 && posTestigo<1600)
     posTestigo=posTestigo+4;
    else if (posTestigo>=1600)
     posTestigo=1;
    break;
   case 37:  // Tecla Izquierda -> mover izquierda
    if (posTestigo<=1600 && posTestigo>1)
     posTestigo=posTestigo-4;
    else if (posTestigo<=1)
     posTestigo=1600;
    break;
   case 38:  // Tecla arriba -> disparar
    _escena->IniciaTiro(true);
    break;
   }
  _escena->DaTestigo(posTestigo);
  GLScene();
          
}
//---------------------------------------------------------------------------



void __fastcall TGLForm2D::F2Click(TObject *Sender)
{
if (_escena->freno=true)
 {
 _escena->freno=false;
 R2->Enabled=true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::R2Click(TObject *Sender)
{
if (_escena->_recubrimiento=true)
 _escena->_recubrimiento=false;
}
//---------------------------------------------------------------------------

