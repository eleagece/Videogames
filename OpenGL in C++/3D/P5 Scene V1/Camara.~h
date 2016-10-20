#ifndef CamaraH
#define CamaraH
#include "PV3d.h"

const int ORTO=1;
const int PERS=2;
const int OBLI=3;

class Camara
 {
 private:
  // Atributos de proyección
  int tipo;  // Tipo de proyección
  GLfloat L,R,B,T,N,F;  // Límites de la proyección: Left, Right, Bottom, Top, Near, Far
  GLfloat angulo;  // Ángulo de la perspectiva (de granangular a zoom)
  GLfloat ratio;  // Proporción del frustum (el mismo para plano lejano y cercano)
  float x,y,z;  // Valores del vector oblícuo de la perspectiva oblícua
  // Atributos de la cámara
  PV3d* eye;
  PV3d* look;
  PV3d* up;
  PV3d* u;
  PV3d* v;
  PV3d* n;
  // Métodos privados
  void initCoordCam();  // Inicializa 'u', 'v' y 'n' a los valores por defecto (identidad)
  void setCoordCam();  // Ajusta los valores de 'u', 'v' y 'n' acorde a los de 'eye', 'look' y 'up'
  void initProyeccion();  // Inicializa los valores de proyección por defecto
  void setOrtogonal();  // Establece una proyección ortogonal
  void setPerspectiva();  // Establece una proyección perspectiva
  void setOblicua();  // Establece una proyección oblícua

 public:
  // Constructoras y destructora
  Camara();
  Camara(PV3d* eye,PV3d* look,PV3d* up);
  ~Camara();
  // Métodos públicos
  void setView();  // Posiciona la cámara en OpenGL mediante gluLookAt()
  void setView(PV3d* eye,PV3d* look,PV3d* up);  // Posiciona la cámara en OpenGL con nuevos valores mediante gluLookAt() y llama a setModelViewMatrix()
  void setModelViewMatrix();  // Carga la matriz de modelado-vista de forma manual
  void setTipoP(int tipo);  // Cambia la variable 'tipo' para saber cambiar la proyección con setProyeccion()
  void setProyeccion();  // Ejecuta la proyección según la variable 'tipo'
  void setLimits(double xLeft,double xRight,double yBot,double yTop,double N,double F);  // Establece los límites de la proyección
  void setVO(float x,float y,float z);  // Establece el vector oblícuo para la proyección perspectiva oblícua
  void setParamPers(double a,double p);  // Establece el ángulo y el ratio para la proyección perspectiva
  // Métodos públicos para mover la cámara
  void roll(double a);  // Rota la cámara respecto al eje 'n'
  void pitch(double a);  // Rota la cámara respecto al eje 'u'
  void yaw(double a);  // Rota la cámara respecto al eje 'v'
  void desplazamiento(double x,double y,double z);  // Desplaza el 'eye' de la cámara
 };

#endif