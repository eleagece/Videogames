#ifndef DibujoLineasH
#define DibujoLineasH
#include "Segmento.h"
#include "Lista.h"

class DibujoLineas
 {
 private:
  // Atributos
  Lista<Segmento>* listaSegmentos;  // lista que almacena los segmentos del dibujo de líneas

 public:
  // Constructores, destructor
  DibujoLineas();
  ~DibujoLineas();
  // Getters
  Lista<Segmento>* DameLista();
  // Métodos públicos que dibujan el dibujo de líneas
  void Dibuja();
  void DibujaSelec();
  // Método públicos que modifican el dibujo de líneas
  void PonSegmento(Segmento*);
  void Recorta(PuntoVector*,PuntoVector*);
  // Método público que selecciona el dibujo de líneas
  bool SelecDibujoLineas(float,float);
  // Métodos públicos que cargan y salvan el dibujo de líneas
  void salvaDibLineas(ofstream& f);
  void cargaDibLineas(ifstream&);
 };

#endif
