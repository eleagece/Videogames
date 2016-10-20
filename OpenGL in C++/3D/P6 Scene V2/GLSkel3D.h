#ifndef GLSkel3DH
#define GLSkel3DH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Escena.h"
#include "Camara.h"

class TGLForm3D : public TForm
 {
 __published:
  TMainMenu *MainMenu1;
  TToolBar *ToolBar1;
  TToolButton *RollDown;
  TToolButton *RollUp;
  TToolButton *ToolButton3;
  TToolButton *YawDown;
  TToolButton *YawUp;
  TToolButton *ToolButton6;
  TToolButton *PitchDown;
  TToolButton *PitchUp;
  TToolButton *ToolButton9;
  TToolButton *XDown;
  TToolButton *XUp;
  TToolButton *YDown;
  TToolButton *ToolButton14;
  TToolButton *YUp;
  TToolButton *ToolButton16;
  TToolButton *ZDown;
  TToolButton *ZUp;
  TMenuItem *Ortogonal2;
  TMenuItem *Esquina2;
  TMenuItem *Cenital2;
  TMenuItem *Lateral2;
  TMenuItem *Frontal2;
  TMenuItem *Perspectiva3;
  TMenuItem *HabitacinInferior1;
  TMenuItem *Habitacinsuperior1;
  TMenuItem *Oblcua2;
  TMenuItem *Objeto1;
  TMenuItem *Escena2;
  TMenuItem *Muebles2;
  TMenuItem *Lmpara2;
  TMenuItem *Accin1;
  TMenuItem *Puerta1;
  TMenuItem *TV1;
  TToolBar *ToolBar2;
  TToolButton *RotaXDown;
  TToolButton *RotaXUp;
  TToolButton *RotaYDown;
  TToolButton *RotaYUp;
  TToolButton *RotaZDown;
  TToolButton *RotaZUp;
  TToolButton *EscalaDown;
  TToolButton *EscalaUp;
  TToolButton *TraslXDown;
  TToolButton *TraslXUp;
  TToolButton *TraslYDown;
  TToolButton *TraslYUp;
  TToolButton *TraslZDown;
  TToolButton *ToolButton22;
  TToolButton *TraslZUp;
  TToolButton *ToolButton24;
  TImageList *ImageList1;
  TMenuItem *Niebla1;
  TMenuItem *Luces1;
  TMenuItem *Ambiente1;
  TMenuItem *Direccional1;
  TMenuItem *Lmpara1;
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall Esquina2Click(TObject *Sender);
  void __fastcall Lateral2Click(TObject *Sender);
  void __fastcall Cenital2Click(TObject *Sender);
  void __fastcall Frontal2Click(TObject *Sender);
  void __fastcall HabitacinInferior1Click(TObject *Sender);
  void __fastcall Habitacinsuperior1Click(TObject *Sender);
  void __fastcall Oblcua2Click(TObject *Sender);
  void __fastcall Escena2Click(TObject *Sender);
  void __fastcall Lmpara2Click(TObject *Sender);
  void __fastcall Muebles2Click(TObject *Sender);
  void __fastcall Puerta1Click(TObject *Sender);
  void __fastcall TV1Click(TObject *Sender);
  void __fastcall RollDownClick(TObject *Sender);
  void __fastcall RollUpClick(TObject *Sender);
  void __fastcall YawDownClick(TObject *Sender);
  void __fastcall YawUpClick(TObject *Sender);
  void __fastcall PitchDownClick(TObject *Sender);
  void __fastcall PitchUpClick(TObject *Sender);
  void __fastcall XDownClick(TObject *Sender);
  void __fastcall XUpClick(TObject *Sender);
  void __fastcall YDownClick(TObject *Sender);
  void __fastcall YUpClick(TObject *Sender);
  void __fastcall ZDownClick(TObject *Sender);
  void __fastcall ZUpClick(TObject *Sender);
  void __fastcall EscalaDownClick(TObject *Sender);
  void __fastcall EscalaUpClick(TObject *Sender);
  void __fastcall TraslXDownClick(TObject *Sender);
  void __fastcall TraslXUpClick(TObject *Sender);
  void __fastcall TraslYDownClick(TObject *Sender);
  void __fastcall TraslYUpClick(TObject *Sender);
  void __fastcall TraslZDownClick(TObject *Sender);
  void __fastcall TraslZUpClick(TObject *Sender);
  void __fastcall RotaXDownClick(TObject *Sender);
  void __fastcall RotaXUpClick(TObject *Sender);
  void __fastcall RotaYDownClick(TObject *Sender);
  void __fastcall RotaYUpClick(TObject *Sender);
  void __fastcall RotaZDownClick(TObject *Sender);
  void __fastcall RotaZUpClick(TObject *Sender);
  void __fastcall Niebla1Click(TObject *Sender);
        void __fastcall Ambiente1Click(TObject *Sender);
        void __fastcall Direccional1Click(TObject *Sender);
        void __fastcall Lmpara1Click(TObject *Sender);

 private:
  // Atributos por defecto
  HDC hdc;
  HGLRC hrc;
  //GLfloat eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ; // Cámara
  GLdouble RatioViewPort, xLeft,xRight, yBot,yTop, N,F;  // Volumen de vista
  // Métodos privados por defecto
  void __fastcall SetPixelFormatDescriptor();
  void __fastcall GLScene();
  // Atributos de usuario
  GLfloat LuzAmbiente[4];  // Luz ambiente
  GLfloat PosicionLuz0[4];  // Luz de la ventana de la habitación superior
  GLfloat PosicionLuz1[4];  // Luz de la ventana
  Camara* usercam;  // Cámara del duplex
  Escena* escena;  // Escena del duplex
  int selec;  // Objeto seleccionado (1=escena, 2=muebles, 3=lámpara)
  // Métodos privados de usuario
  void crearMenu();  // Inicia el menú a los valores correctos

  void crearEscena();  // Crea los objetos de la escena
  void crearNiebla();  // Crea la niebla del duplex
  void crearLuces();  // Crea las luces del duplex
  void crearTexturas();  // Crea las texturas del duplex
  void crearCamara();  // Crea la cámara que visualiza la escena

  void liberarEscena();  // Libera los objetos de la escena
  void liberarCamara();  // Libera la cámara

 public:
  __fastcall TGLForm3D(TComponent* Owner);
 };

extern PACKAGE TGLForm3D *GLForm3D;
#endif
