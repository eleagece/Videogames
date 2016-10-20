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
  Lista<DibujoLineas>* listaDibujosLineas;  // lista que almacena los dibujos de líneas (polilíneas, polígonos, espirales)
  Lista<Hipotrocoide>* listaHipotrocoides;  // lista que almacena los hipotrocoides
  DibujoLineas* dibLineasAux;  // dibujo de líneas auxiliar para las polilíneas. Se actualiza cada vez que se hace un nuevo segmento
  DibujoLineas* dibLineasSel;  // dibujo de líneas seleccionado al hacer clic
  Hipotrocoide* hipotrocoSel;  // hipotrocoide seleccionado al hacer clic
  PuntoVector* pSI;  // punto inicial del cuadrado de recorte
  PuntoVector* pID;  // punto final del cuadrado de recorte
  // Atributos normales
  float xRight,xLeft,yTop,yBot;  // floats que definen el area visible de la escena
  bool recortando;  // indica si se está recortando (o no) para dibujar (o no) el cuadrado de crop
  // Métodos privados
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
  // Métodos públicos que modifican el área visible de la escena
  void Resize(float);
  void Zoom(float);
  void Trasladar(int);
  // Métodos públicos que dibujan dibujos de líneas e hipotrocoides
  void Dibuja();
  void DibujaHipotrocoSel();
  void DibujaDibLineasSel();
  // Métodos públicos que modifican los dibujos de líneas e hipotrocoides
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
  // Métodos públicos que buscan dibujos de líneas e hipotrocoides en sus listas
  bool BuscarHipotrocoide(float,float);
  bool BuscarDibujoLineas(float,float);
  // Métodos que cargan y salvan dibujos de líneas e hipotrocoides
  void salvaBin(ofstream&);
  void cargaBin(float,ifstream&);
 };

#endif
