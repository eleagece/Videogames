//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Escena.h"
#include <Menus.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Menu1;
        TMenuItem *F2;
        TMenuItem *R2;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);   
        void __fastcall Inicio11Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Inicio21Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall F2Click(TObject *Sender);
        void __fastcall R2Click(TObject *Sender);

private:	// User declarations
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLdouble xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLdouble RatioViewPort;
 //escena que contiene los objetos a dibujar
 Escena* _escena;
 // Indica si se ha cerrado la ventana
 bool _closing;
 // Para controlar la elección de donde se dispara la pelota
 int posTestigo;
 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
