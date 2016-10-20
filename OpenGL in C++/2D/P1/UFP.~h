//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Precisar1;
        TMenuItem *Acercar1;
        TMenuItem *Alejar1;
        TMenuItem *Trasladar1;
        TMenuItem *Centrar1;
        TMenuItem *Tiling1;
        TMenuItem *Opcional1;
        TMenuItem *Valores1;
        TMenuItem *Animacin2;
        TMenuItem *Colores1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Precisar1Click(TObject *Sender);
        void __fastcall Acercar1Click(TObject *Sender);
        void __fastcall Alejar1Click(TObject *Sender);
        void __fastcall Trasladar1Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Centrar1Click(TObject *Sender);
        void __fastcall Tiling1Click(TObject *Sender);
        void __fastcall Valores1Click(TObject *Sender);
        void __fastcall Animacin2Click(TObject *Sender);
        void __fastcall Colores1Click(TObject *Sender);

private:	// User declarations
 int segmentosVueltaDefault;
 int columnasTiling;
 int hipoA,hipoB,hipoC;
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLfloat xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLfloat RatioViewPort;
 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();
 int MCD(int,int);
 void Zoom(float,float&,float&);
 void PintaHipotrocoide(float,float,float,int);
 void PintaHipotrocoideAnimado(float,float,float,int);
 void Espera(float);
 void SeleccionaColor(int);
 void PintaCentro();

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif




 //*/
 /*
 // VERSIÓN NO FUNCIONAL. ¿POR QUÉ?
 {
 float x, y;
 int numVueltas=b/MCD(a,b);  // Número de vueltas totales
 int segmentosTotal=numVueltas*segmentosVuelta;  // Número de segmentos de todas las vueltas
 float anguloSegmento=2*M_PI/segmentosVuelta;  // Ángulo que cubre un solo segmento
 float anguloTotal=segmentosTotal*anguloSegmento;  // Ángulo total que cubren los segmentos de todas las vueltas
 glBegin(GL_LINE_STRIP);
 for (float t=0; t<=anguloTotal; t=t+anguloSegmento)
  {
  x=((a-b)*cos(t))+(c*cos(t*((a-b)/b)));
  y=((a-b)*sin(t))-(c*sin(t*((a-b)/b)));
  glVertex2f(x,y);
  }
 glEnd;
 }
 */
 /* {
 float x, y, v, w;
 int numVueltas=b/MCD(a,b);  // Número de vueltas totales
 int segmentosTotal=numVueltas*segmentosVuelta;  // Número de segmentos de todas las vueltas
 int anguloSegmento=2*M_PI/segmentosVuelta;  // Ángulo que cubre un solo segmento
 int anguloTotal=segmentosTotal*anguloSegmento;  // Ángulo total que cubren los segmentos de todas las vueltas
 for (int t=0; t<=segmentosTotal; t++)
  {
  x=((a-b)*cos(t))+(c*cos(t*((a-b)/b)));
  y=((a-b)*sin(t))-(c*sin(t*((a-b)/b)));
  if (t==0)  // Primera iteración para guardar el primer punto
   {
   v=x; w=y;
   }
  else
   {
   glBegin(GL_LINES);
    glVertex2f(v,w);
    glVertex2f(x,y);
   glEnd();
   v=x; w=y;
   Espera(0.01);
   SwapBuffers(hdc);
   }
  }
 }    */

   /*  int x=24, x1=24;
    int y=18, y1=18;
    int z=11, z1=11;
    x+=y-z;
    x1=x1+(y1-z1);  */
