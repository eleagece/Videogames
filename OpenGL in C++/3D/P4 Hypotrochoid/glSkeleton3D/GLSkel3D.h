#ifndef GLSkel3DH
#define GLSkel3DH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <gl\gl.h>
#include <gl\glu.h>

class TGLForm3D : public TForm
 {
 __published:
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);

 private:
  // Atributos base
  HDC hdc;
  HGLRC hrc;
  GLfloat eyeX,eyeY,eyeZ, lookX,lookY,lookZ,upX,upY,upZ;  // C�mara
  GLdouble RatioViewPort, xLeft,xRight,yBot,yTop,N,F;  // Volumen de vista
  GLfloat PosicionLuz0[4];  // Luz
  // M�todos privados base
  void __fastcall SetPixelFormatDescriptor();
  void __fastcall GLScene();
  void crearObjetosEscena();
  void liberarObjetosEscena();

 public:
  // M�todos p�blicos base
  __fastcall TGLForm3D(TComponent* Owner);
 };

extern PACKAGE TGLForm3D *GLForm3D;
#endif
