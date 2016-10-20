#ifndef EscenaH
#define EscenaH
#include <gl\gl.h>
#include <gl\glu.h>
#include "Lista.h"
#include "Lapiz.h"
#include "Hipotrocoide.h"
#include "DibujoLineas.h"

class Escena   
 {
 private:
  // Atributos new
  Lista<DibujoLineas>* listaDibujosLineas;  // lista que almacena los dibujos de l�neas (polil�neas, pol�gonos, espirales)
  Lista<Hipotrocoide>* listaHipotrocoides;  // lista que almacena los hipotrocoides
  DibujoLineas* dibLineasAux;  // dibujo de l�neas auxiliar para las polil�neas. Se actualiza cada vez que se hace un nuevo segmento
  DibujoLineas* dibLineasSel;  // dibujo de l�neas seleccionado al hacer clic
  Hipotrocoide* hipotrocoSel;  // hipotrocoide seleccionado al hacer clic
  PuntoVector* pSI;  // punto inicial del cuadrado de recorte
  PuntoVector* pID;  // punto final del cuadrado de recorte
  // Atributos normales
  float xRight,xLeft,yTop,yBot;  // floats que definen el area visible de la escena
  bool recortando;  // indica si se est� recortando (o no) para dibujar (o no) el cuadrado de crop
  // M�todos privados
  void ZoomPrivado(float,float&,float&);
  void PintaRecorte();

 public:
  // Constructores, destructor
  Escena();
  ~Escena();
  // Getters
  float DamexLeft();
  float DamexRight();
  float DameyTop();
  float DameyBot();
  // Setters
  void PonpSI(float,float);
  void PonpID(float,float);
  void PonRecortando(bool);
  // M�todos p�blicos que modifican el �rea visible de la escena
  void Resize(float);
  void Zoom(float);
  void Trasladar(int);
  // M�todos p�blicos que dibujan dibujos de l�neas e hipotrocoides
  void Dibuja();
  void DibujaHipotrocoSel();
  void DibujaDibLineasSel();
  // M�todos p�blicos que modifican los dibujos de l�neas e hipotrocoides
  void InsertarSegmento(float,float,float,float,bool);
  void InsertarEspiral(float,float,int,float,float,int);
  void InsertarPoligono(float,float,int,float);
  void InsertarHipotrocoide(float,float,float,float,float,float);
//****************************************************************************//
//****************************************************************************//
  void Recorta();
  void CambiaPrecHipotrocoSel(bool);
  void GiraHipotrocoSel();
  void BorraDibLineasSel();
  void BorraHipotrocoSel();
  // M�todos p�blicos que buscan dibujos de l�neas e hipotrocoides en sus listas
  bool BuscarHipotrocoide(float,float);
  bool BuscarDibujoLineas(float,float);
  // M�todos que cargan y salvan dibujos de l�neas e hipotrocoides
  void salvaBin(ofstream&);
  void cargaBin(float,ifstream&);
 };

#endif
