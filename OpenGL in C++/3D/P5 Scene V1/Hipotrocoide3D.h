#ifndef Hipotrocoide3DH
#define Hipotrocoide3DH
#include "Malla.h"
#include <math.h>

class Hipotrocoide3D: public Malla
 {
 private:
  // Atributos
  double a,b,c;
  vector<PV3d*>* base;  // Puntos del pol�gono que se toma como base de la hipotrocoide
  Malla* carroceriaA;
  Malla* carroceriaB;
  GLUquadricObj* ruedaA; GLUquadricObj* tapaA;
  GLUquadricObj* ruedaB; GLUquadricObj* tapaB;
  GLUquadricObj* ruedaC; GLUquadricObj* tapaC;
  GLUquadricObj* ruedaD; GLUquadricObj* tapaD;
  double posX,posY;  // Posici�n inicial del coche
  int nqInt;  // Numero de rodajas por vuelta, necesarias para calcular tCoche
  int iInt;  // Contador de n�mero de rodajas, necesario para calcular tCoche
  double tCoche;  // �ngulo para calcular la posici�n de la hipotrocoide por la que va el coche
  PV3d* orient;  // Vector que indica la direcci�n inicial del coche
  PV3d* tangente;  // Vector que indica la tangente a la posici�n del punto por donde va el coche
  double rotCoche;  // �ngulo de rotaci�n del coche (en grados)
  // M�todos privados
  int MCD(int,int);
  PV3d* marcoFrenet(PV3d* p,double t);  // Calcula el t-�simo marco de Frenet para el punto p
  void genCirculo(int np,double r);  // Genera el pol�gono tomado como base de la hipotrocoide en el plano XY
  void dibujaRueda(GLUquadric* obj, double x, double z);  // Pinta una rueda
  void dibujaTapa(GLUquadric* obj, double x, double z);  // Pinta una tapa de rueda

 public:
  // Constructores y destructor
  Hipotrocoide3D(int np, int nq, int a, int b, int c);
  ~Hipotrocoide3D();
  // M�todos p�blicos
  void setCoche(bool b);
  void dibujaCoche();
 };

#endif
