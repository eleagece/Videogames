#ifndef Objeto3DH
#define Objeto3DH
#include "Color.h"
#include "TAfin.h"

class Objeto3D  // Clase abstracta por tener un método virtual puro 'dibuja()' y '~Objeto3D()'. No se pueden hacer instancias de la clase
 {
 protected:
  // Atributos protegidos
  Color* color;  // Color del objeto
  TAfin* m;  // Matriz que define el marco de coordenadas

 public:
  // Constructoras y destructora
  Objeto3D();
  virtual ~Objeto3D()=0;  // Destructora virtual (la han de redefinir los hijos)
  // Métodos públicos
  virtual void dibuja()=0;  // Dibuja virtual (lo han de redefinir los hijos)
  TAfin* getTAfin();  // Devuelve la matriz que define el marco de coordenadas
  Color* getColor();  // Devuelve el color del objeto
  void setColor(float r, float g, float b);  // Cambia el color del objeto
 };

#endif