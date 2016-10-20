#include <vcl.h>
#pragma hdrstop
#include "UFP.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TGLForm2D *GLForm2D;
// DONE ---------------------------------------------------------------------------
__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
 {
 escena=NULL;
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormCreate(TObject *Sender)
 {
 hdc=GetDC(Handle);
 SetPixelFormatDescriptor();
 hrc=wglCreateContext(hdc);
 if(hrc==NULL)
  {
  ShowMessage(":-)~ hrc == NULL");
  }
 if(wglMakeCurrent(hdc, hrc) == false)
  {
  ShowMessage("Could not MakeCurrent");
  }
 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Color de fondo de la ventana (negro)
 //inicialización del puerto de vista
 //ClientWidth=400;
 //ClientHeight=400;
 RatioViewPort=1.0;
 // inicialización de las variables del programa
 this->escena=new Escena();
 estado=1;  // activo
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::SetPixelFormatDescriptor()
 {
 PIXELFORMATDESCRIPTOR pfd={sizeof(PIXELFORMATDESCRIPTOR),
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
 int PixelFormat=ChoosePixelFormat(hdc,&pfd);
 SetPixelFormat(hdc,PixelFormat,&pfd);
 }

// DONE ---------------------------------------------------------------------
void __fastcall TGLForm2D::FormResize(TObject *Sender)
 {
 // Establecimiento de "PUERTO DE VISTA" (view port, ventana)
 if (estado!=0)
  {
  if ((ClientWidth<=1)||(ClientHeight<=1))  // Si se hace un resize con ancho o largo menor de 1 pixel
   {
   ClientWidth=400;  // Tamaño 400x400
   ClientHeight=400;
   RatioViewPort=1.0;  // Ratio 1.0
   }
  else  // Si se hace un resize con ancho o largo mayor de 1 pixel
   {
   RatioViewPort=(float)ClientWidth/(float)ClientHeight;  // Tamaño ClientWidth*ClientHeight, Ratio nuevo
   }
  glViewport(0,0,ClientWidth,ClientHeight);  // Establece el "puerto de vista" según los nuevos datos
  this->escena->Resize(this->RatioViewPort);
  GLScene();
  }
 }
 
// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
 {
 glClear(GL_COLOR_BUFFER_BIT);
 escena->Dibuja();
 if (estado==13)
  escena->DibujaHipotrocoSel();
 if (estado==14)
  escena->DibujaDibLineasSel();
 glFlush();
 SwapBuffers(hdc);
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
 {
 GLScene();
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
 {
 ReleaseDC(Handle,hdc);
 wglMakeCurrent(NULL, NULL);
 wglDeleteContext(hrc);
 delete this->escena;
 escena=NULL;
 estado=0; // cerrando
 }

// DONE ---------------------------------------------------------------------------
// Si no hubiese zoom o traslaciones este método sería trivial, pero como las hay, no lo es
void TGLForm2D::TransformarXY(float& x,float& y)
 {
 x=escena->DamexLeft()+((escena->DamexRight()-escena->DamexLeft())*x/ClientWidth);
 y=(escena->DameyBot()+((escena->DameyTop()-escena->DameyBot())*y/ClientHeight));
 //y=-(((escena->DameyTop()-escena->DameyBot())*y+(escena->DameyBot()*ClientHeight))/ClientHeight);
 //pke version y=((yT-yB)*y+(yB*CH))/CH
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
 {
 if (estado==2)
  {
  int dir=0;
  switch (Key)
   {
   case 39:  // Tecla derecha
    dir=1;
    break;
   case 40:  // Tecla abajo
    dir=2;
    break;
   case 37:  // Tecla Izquierda
    dir=3;
    break;
   case 38:  // Arriba
    dir=4;
    break;
   }
  escena->Trasladar(dir);
  GLScene();
  }
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::Polilneas1Click(TObject *Sender)
 {
 estado=4;
 }

// DONE para las polilíneas ---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
 {
 float xAVE=(float)X;  // Coordenadas en "formato" de AVE (Área visible de la escena)
 float yAVE=ClientHeight-(float)Y;
 TransformarXY(xAVE,yAVE);
 switch(estado)
  {
  case 4:  // POLILÍNEA (origen)
   {
   oX=xAVE;  // Origen de la polilínea en formato de AVE (Área visible de la escena)
   oY=yAVE;
   estado=5;  // La siguiente vez que se haga click será para calcular el destino
   break;
   }
  case 5:  // POLILÍNEA (primer segmento)
   {
   escena->InsertarSegmento(oX,oY,xAVE,yAVE,true);  // Inserta un segmento de la polilínea en un dibujo de líneas
   oX=xAVE;
   oY=yAVE;
   estado=6;
   break;
   }
  case 6:  // POLILÍNEA (resto de segmentos)
   {
   escena->InsertarSegmento(oX,oY,xAVE,yAVE,false);  // Inserta un segmento de la polilínea en un dibujo de líneas
   oX=xAVE;
   oY=yAVE;
   break;
   }
  case 7:  // POLÍGONO
   {
   AnsiString numLadosAnsi=InputBox("Número de lados","Introduzca el número de lados",5);
   AnsiString longLadoAnsi=InputBox("Longitud del lado","Introduzca la longitud del lado",20);
   int numLados=numLadosAnsi.ToInt();
   float longLado=(float)longLadoAnsi.ToDouble();
   escena->InsertarPoligono(xAVE,yAVE,numLados,longLado);
   break;
   }
  case 8:  // ESPIRAL
   {
   AnsiString numIteracionesAnsi=InputBox("Número de iteraciones","Introduzca el número de iteraciones",50);
   AnsiString longLadoAnsi=InputBox("Longitud del lado","Introduzca la longitud del lado",10);
   AnsiString incrementoAnsi=InputBox("Incremento del lado","Introduzca el incremento del lado",10);
   AnsiString anguloGiroAnsi=InputBox("Ángulo de giro","Introduzca el ángulo de giro",45);
   int numIteraciones=numIteracionesAnsi.ToInt();
   float longLado=(float)longLadoAnsi.ToDouble();
   float incremento=(float)incrementoAnsi.ToDouble();
   int anguloGiro=anguloGiroAnsi.ToInt();
   escena->InsertarEspiral(xAVE,yAVE,numIteraciones,longLado,incremento,anguloGiro);
   break;
   }
  case 9:  // HIPOTROCOIDE
   {
   AnsiString aAnsi=InputBox("Parámetro a","Introduzca el parámetro a",170);
   AnsiString bAnsi=InputBox("Parámetro b","Introduzca el parámetro b",56);
   AnsiString cAnsi=InputBox("Parámetro c","Introduzca el parámetro c",80);
   AnsiString precAnsi=InputBox("Parámetro c","Introduzca la precisión",20);
   float a=(float)aAnsi.ToDouble();
   float b=(float)bAnsi.ToDouble();
   float c=(float)cAnsi.ToDouble();
   float prec=(float)precAnsi.ToDouble();
   escena->InsertarHipotrocoide(xAVE,yAVE,a,b,c,prec);
   break;
   }
  case 10:  // SELECCIÓN (de hipotrocoides y dibujos de líneas)
   {
   bool b=false;
   bool b2=false;
   b=escena->BuscarHipotrocoide(xAVE,yAVE);
   b2=escena->BuscarDibujoLineas(xAVE,yAVE);
   if (b)
    estado=13;  // EDICIÓN (hipotrocoide)
   else if (b2)
    {
    estado=14;  // EDICIÓN (dibujos de líneas)
    }
   break;
   }
  case 11:  // CROP (origen)
   {
   estado=12;
   escena->PonpSI(xAVE,yAVE);
   escena->PonpID(xAVE,yAVE);
   escena->PonRecortando(true);
   break;
   }
  }
 GLScene();
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::Zoom1Click(TObject *Sender)
 {
 estado=3;  // zoom
 float zoomFloat;
 AnsiString zoomAnsi=InputBox("Zoom","Introduzca el aumento de zoom","");
 zoomFloat=(float)zoomAnsi.ToDouble();
 escena->Zoom(zoomFloat);
 GLScene();
 }

// DONE ---------------------------------------------------------------------------
void __fastcall TGLForm2D::Traslacin1Click(TObject *Sender)
 {
 estado=2;
 }

//---------------------------------------------------------------------------
void __fastcall TGLForm2D::Hipotrocoide1Click(TObject *Sender)
 {
 estado=9;
 ShowMessage("Haga click en lo que será el centro de la hipotrocoide");
 }

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
 {
 if (estado==12)
  {
  GLfloat auxX=(float)X;
  GLfloat auxY=ClientHeight-(float)Y;
  TransformarXY(auxX,auxY);
  if (escena!=NULL)
   escena->PonpID(auxX,auxY);
  }
 GLScene();
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Cortar1Click(TObject *Sender)
 {
 estado=11;
 }
//---------------------------------------------------------------------------


void __fastcall TGLForm2D::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
 {
 if (estado==12)
  {
  estado=1;
  escena->Recorta();
  escena->PonRecortando(false);
  }
 GLScene();
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Polgono1Click(TObject *Sender)
 {
 estado=7;
 ShowMessage("Haga click en lo que será el centro del polígono");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Espiral1Click(TObject *Sender)
 {
 estado=8;
 ShowMessage("Haga click en lo que será el centro de la espiral");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Seleccionar1Click(TObject *Sender)
 {
 estado=10;
 ShowMessage("Seleccione una figura. En caso de ambigüedad los hipotrocoides son prioritarios");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Precisar1Click(TObject *Sender)
 {
 if (estado==13)
  {
  precision=true;
  escena->CambiaPrecHipotrocoSel(precision);
  estado=1;
  GLScene();
  }
 else
  ShowMessage("Debe seleccionar una hipotrocoide");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Desprecisar1Click(TObject *Sender)
 {
 if (estado==13)
  {
  precision=false;
  escena->CambiaPrecHipotrocoSel(precision);
  estado=1;
  GLScene();
  }
 else
  ShowMessage("Debe seleccionar una hipotrocoide");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Girar1Click(TObject *Sender)
 {
 if (estado==13)
  {
  escena->GiraHipotrocoSel();
  estado=1;
  GLScene();
  }
 else
  ShowMessage("Debe seleccionar una hipotrocoide");
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::BOrrar1Click(TObject *Sender)
 {
 if (estado==13)
  {
  escena->BorraHipotrocoSel();
  estado=1;
  GLScene();
  }
 else if (estado==14)
  {
  escena->BorraDibLineasSel();
  estado=1;
  GLScene();
  }
 else
  ShowMessage("Debe seleccionar una figura");
 }
//---------------------------------------------------------------------------



void __fastcall TGLForm2D::Guardar1Click(TObject *Sender)
 {
 if (SaveDialog1->Execute())  // Si se cierra obteniendo una ruta para el archivo
  {
  AnsiString archivo=SaveDialog1->FileName;  // guarda en archivo el nombre del archivo seleccionado
  ofstream f;  // Archivo de salida
  f.open(archivo.c_str(),ios::binary);  // Abre el archivo (obtiene ruta en formato c-string (era un AnsiString))
  escena->salvaBin(f);  // Guarda en el archivo
  f.close();  // Cierra el archivo
  }
 else  // Si se cierra cancelando
  {
  }
 GLScene();
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Abrir1Click(TObject *Sender)
 {
 if (OpenDialog1->Execute())  // Si se cierra obteniendo una ruta para el archivo
  {
  AnsiString archivo=OpenDialog1->FileName;  // Guarda en archivo el nombre del archivo seleccionado
  ifstream f;  // Archivo de entrada
  f.open(archivo.c_str(),ios::binary);  // Abre el archivo (obtiene ruta en formato c-string (era un AnsiString))
  float ratio=(float)ClientWidth/(float)ClientHeight;  // Para que se cargue bien la escena si la ventana es distinta a como se guardó
  escena->cargaBin(ratio,f);  // Lee del archivo
  f.close();  // Cierra el archivo
  }
 else  // Si se cierra cancelando
  {
  }
 GLScene();
 }
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Nuevo1Click(TObject *Sender)
 {
 delete escena;
 escena=new Escena();
 estado=1;  // activo
 }
//---------------------------------------------------------------------------

