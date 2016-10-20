#ifndef PuntoVectorH
#define PuntoVectorH
#include <math>
#include <fstream>
#include <iostream>
//#include <string>
using namespace std;  // Necesario para que funcione fstream

class PuntoVector
 {
 private:
  float x,y;
 public:
  // Constructores
  PuntoVector();  // Por defecto
  PuntoVector(float,float);  // Constructor parametrizado (float,float)
  PuntoVector(PuntoVector*);  // Constructor por objeto
  // Getters y setters
  float dameX(); void ponX(float);
  float dameY(); void ponY(float);
  // Métodos
  void rotaP(PuntoVector*,float);
  /*void dibuja(GLfloat tam,GLfloat R,GLfloat G,GLfloat B);
  float distancia(Punto2F* p);
  bool cercano(Punto2F* p,float d);*/
  void salvaPunto(ofstream& f);
  void cargaPunto(ifstream& f);
 };

#endif
