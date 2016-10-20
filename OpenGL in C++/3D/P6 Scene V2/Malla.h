#ifndef MallaH
#define MallaH
#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>
#include "Cara.h"
#include "PV3d.h"
#include "Objeto3D.h"
#include <vector>
using namespace std;

#define SUC(i,N) (i+1)%N

class Malla: public Objeto3D  // Clase hija que hereda de Objeto3D
 {
 protected:
  // Atributos
  vector<PV3d*>* tn;  // Vector de normales
  vector<PV3d*>* tv;  // Vector de v�rtices
  vector<Cara*>* tc;  // Vector de caras
  // M�todos protegidos
  void genMallaCil4(int nelem);  // Genera un prisma de nelem lados de base que aproxima un cilindro
  void addCirculo(int np,double r,double h);  // Genera un pol�gono base que simula un c�rculo
  void genMallaCil3(int nelem);  // Genera un prisma de nelem lados de base que aproxima un cilindro pero de caras de 3 lados
  PV3d* normalNewell(Cara* c);  // Devuelve la normal de la cara c calculada por el m�todo de Newell

 public:
  // Constructores y destructor
  Malla();
  ~Malla();
  // M�todos p�blicos
  void dibuja();
 };

#endif
