#ifndef UFPH
#define UFPH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Escena.h"

class TGLForm2D: public TForm
 {
 __published:
  TMainMenu *MainMenu1;
  TMenuItem *Archivo1;
  TMenuItem *Nuevo1;
  TMenuItem *Abrir1;
  TMenuItem *Guardar1;
  TMenuItem *Salir1;
  TMenuItem *Dibujar1;
  TMenuItem *Polilneas1;
  TMenuItem *Polgono1;
  TMenuItem *Espiral1;
  TMenuItem *Hipotrocoide1;
  TMenuItem *Hipotrocoide2;
  TMenuItem *Girar1;
  TMenuItem *Precisar1;
  TMenuItem *Desprecisar1;
  TMenuItem *Editar1;
  TMenuItem *Seleccionar1;
  TMenuItem *BOrrar1;
  TMenuItem *Explorar1;
  TMenuItem *Zoom1;
  TMenuItem *Traslacin1;
  TMenuItem *Cortar1;
  TOpenDialog *OpenDialog1;
  TSaveDialog *SaveDialog1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
   TShiftState Shift);
  void __fastcall Polilneas1Click(TObject *Sender);
  void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
   TShiftState Shift, int X, int Y);
  void __fastcall Zoom1Click(TObject *Sender);
  void __fastcall Traslacin1Click(TObject *Sender);
  void __fastcall Hipotrocoide1Click(TObject *Sender);
  void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
   int X, int Y);
  void __fastcall Cortar1Click(TObject *Sender);
  void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
   TShiftState Shift, int X, int Y);
  void __fastcall Polgono1Click(TObject *Sender);
  void __fastcall Espiral1Click(TObject *Sender);
  void __fastcall Seleccionar1Click(TObject *Sender);
  void __fastcall Precisar1Click(TObject *Sender);
  void __fastcall Desprecisar1Click(TObject *Sender);
  void __fastcall Girar1Click(TObject *Sender);
  void __fastcall BOrrar1Click(TObject *Sender);
        void __fastcall Abrir1Click(TObject *Sender);
        void __fastcall Guardar1Click(TObject *Sender);
        void __fastcall Nuevo1Click(TObject *Sender);

 private:
  // Atributos
  Escena* escena;
  int estado;  // 0:  CERRANDO (cuando se destruye)
               // 1:  ACTIVO (cuando se crea)
               // 2:  TRASLADAR
               // 3:  ZOOM
               // 4:  POLILÍNEA (origen)
               // 5:  POLILÍNEA (primer intermedio)
               // 6:  POLILÍNEA (intermedios y destino)
               // 7:  POLÍGONO (con Lápiz)
               // 8:  ESPIRAL (con Lápiz)
               // 9:  HIPOTROCOIDE (con ecuaciones paramétricas)
               // 10: SELECCIÓN (de hipotrocoides y dibujos de líneas)
               // 11: CROP (origen)
               // 12: CROP (arrastrando)
               // 13: SELECCIÓN (hipotrocoide -calidad y giro-)

               // 14: MODIFICACIÓN (calidad hipotrocoide)
               // 15: MODIFICACIÓN (giro hipotrocoide)
               // 16: SELECCIÓN (polilínea)
  float oX,oY;  // Coordenadas origen de una línea definida por el usuario
  float nlados,lini,ilado,igiro;  // Atributos para el dibujo de polígonos y espirales
  bool precision;  // true: se precisa la hipotrocoide, false: se desprecisa
  GLfloat RatioViewPort;  //guarda el radio del puerto de vista
  // Atributos que yo no toco
  HDC hdc;
  HGLRC hrc;
  // Métodos
  void __fastcall GLScene();
  void TransformarXY(float&,float&);
  // Métodos que yo no toco
  void __fastcall SetPixelFormatDescriptor();

 public:
  __fastcall TGLForm2D(TComponent* Owner);
 };

extern PACKAGE TGLForm2D *GLForm2D;
#endif
