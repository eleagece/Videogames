#ifndef MallaH
#define MallaH
#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include "Cara.h"
#include "PV3d.h"
#include <vector>
using namespace std;

#define SUC(i,N) (i+1)%N

class Malla
 {
 protected:
  // Atributos
  vector<PV3d*>* tn;  // Vector de normales
  vector<PV3d*>* tv;  // Vector de vértices
  vector<Cara*>* tc;  // Vector de caras
  double rotX;  // Ángulos de rotación de los ejes
  double rotY;
  double rotZ;
  // Métodos protected
  void genMallaCil4(int nelem);  // Genera un prisma de nelem lados de base que aproxima un cilindro
  //void addCirculo(int np,double r,double h);  // Genera un polígono base que simula un círculo

 private:
  // Métodos privados
  PV3d* normalNewell(Cara* c);  // Devuelve la normal de la cara c calculada por el método de Newell

 public:
  // Constructores y destructor
  Malla();
  ~Malla();
  // Métodos públicos
  void genMallaCubo();  // Genera una malla para un cubo
  void ponVertice(double x, double y, double z);
  void setGiro(int eje, int dir);
  void dibuja(bool b);
 };

#endif