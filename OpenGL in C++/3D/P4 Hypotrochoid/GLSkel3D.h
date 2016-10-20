#ifndef GLSkel3DH
#define GLSkel3DH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Hipotrocoide3D.h"

const int HIPOTROCOIDE=1;
const int HIPOTROCOIDE_COCHE=2;

class TGLForm3D : public TForm
 {
 __published:
  TMainMenu *MainMenu1;
  TMenuItem *Hipotrocoide1;
  TMenuItem *Hipotrocoidecoche1;
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall Hipotrocoide1Click(TObject *Sender);
  void __fastcall Hipotrocoidecoche1Click(TObject *Sender);

 private:
  // Atributos base
  HDC hdc;
  HGLRC hrc;
  GLfloat eyeX,eyeY,eyeZ,lookX,lookY,lookZ,upX,upY,upZ;  // Cámara
  GLdouble RatioViewPort,xLeft,xRight,yBot,yTop,N,F;  // Volumen de vista
  GLfloat PosicionLuz0[4];  // Luz
  // Métodos privados base
  void __fastcall SetPixelFormatDescriptor();
  void __fastcall GLScene();
  // Atributos
  Hipotrocoide3D* hipotrocoide;
  int activa;
  bool dibujaCoche;
  // Métodos privados
  void crearObjetosEscena();
  void liberarObjetosEscena();
  void dibuja();

 public:
  // Métodos públicos base
  __fastcall TGLForm3D(TComponent* Owner);
 };

extern PACKAGE TGLForm3D *GLForm3D;
#endif
