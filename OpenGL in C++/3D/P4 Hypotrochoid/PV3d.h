#ifndef PV3dH
#define PV3dH
#include <math.h>
#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>

class PV3d
 {
 private:
  // Atributos
  double _x,_y,_z;  // Coordenadas
  int _ext;  // 1 punto, 0 vector

 public:
  // Constructores y destructor
  PV3d(double,double,double,int);
  PV3d(PV3d*);
  // Getters y setters
  double getX() {return _x;}
  double getY() {return _y;}
  double getZ() {return _z;}
  double getExt() {return _ext;}
  void setX(double x) {_x=x;}
  void setY(double y) {_y=y;}
  void setZ(double z) {_z=z;}
  void setExt(double ext) {_ext=ext;}
  // Métodos públicos
  double dot(PV3d* w);  // Realiza el producto escalar con del vector actual con el vector w
  PV3d* prodVect(PV3d* w);  // Realiza el producto vectorial del vector actual con el vector w y lo devuelve
  double module();  // Devuelve el módulo del vector actual
  double alpha(PV3d* w);  // Devuelve el ángulo que forma el vector actual con el vector w (en grados)
  void dibuja(GLdouble tam,GLfloat R,GLfloat G,GLfloat B);  // Dibuja el punto con tamaño y color especificado
  void dibuja();
 };

#endif