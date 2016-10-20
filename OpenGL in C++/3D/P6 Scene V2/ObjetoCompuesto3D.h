#ifndef ObjetoCompuesto3DH
#define ObjetoCompuesto3DH
#include "Objeto3D.h"
#include <vector>
using namespace std;

class ObjetoCompuesto3D: public Objeto3D  // Clase hija que hereda de Objeto3D
 {
 protected:
  // Atributos
  vector<Objeto3D*>* objetos;  // vector de Objeto3D que componen el ObjetoCompuesto3D

 public:
  // Constructoras y destructor
  ObjetoCompuesto3D();
  ~ObjetoCompuesto3D();
  // Métodos públicos
  void dibuja();  // Dibuja todos los objetos que componen el objeto compuesto
 };

#endif