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
  // Constructoras y destructora
  PV3d(double,double,double,int);
  PV3d(PV3d*);
  // M�todos p�blicos
  double getX() {return _x;}
  double getY() {return _y;}
  double getZ() {return _z;}
  double getExt() {return _ext;}
  void setX(double x) {_x=x;}
  void setY(double y) {_y=y;}
  void setZ(double z) {_z=z;}
  void setExt(double ext) {_ext=ext;}
  double dot(PV3d* w);  // Realiza el producto escalar con del vector actual con el vector w
  void normalize();  // Normaliza el vector (lo pone a m�dulo=1)
  void prodV(PV3d* a,PV3d* b);  // Establece las coordenadas del vector seg�n el resultado de a x b
  PV3d* prodVect(PV3d* w);  // Realiza el producto vectorial del vector actual con el vector w y lo devuelve
  double module();  // Devuelve el m�dulo del vector actual
  double alpha(PV3d* w);  // Devuelve el �ngulo que forma el vector actual con el vector w (en grados)
  void dibuja(GLdouble tam,GLfloat R,GLfloat G,GLfloat B);  // Dibuja el punto con tama�o y color especificado
  void dibuja();
 };

#endif