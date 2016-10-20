#ifndef CamaraH
#define CamaraH
#include "PV3d.h"

const int ORTO=1;
const int PERS=2;
const int OBLI=3;

class Camara
 {
 private:
  // Atributos de proyecci�n
  int tipo;  // Tipo de proyecci�n
  GLfloat L,R,B,T,N,F;  // L�mites de la proyecci�n: Left, Right, Bottom, Top, Near, Far
  GLfloat angulo;  // �ngulo de la perspectiva (de granangular a zoom)
  GLfloat ratio;  // Proporci�n del frustum (el mismo para plano lejano y cercano)
  float x,y,z;  // Valores del vector obl�cuo de la perspectiva obl�cua
  // Atributos de la c�mara
  PV3d* eye;
  PV3d* look;
  PV3d* up;
  PV3d* u;
  PV3d* v;
  PV3d* n;
  // M�todos privados
  void initCoordCam();  // Inicializa 'u', 'v' y 'n' a los valores por defecto (identidad)
  void setCoordCam();  // Ajusta los valores de 'u', 'v' y 'n' acorde a los de 'eye', 'look' y 'up'
  void initProyeccion();  // Inicializa los valores de proyecci�n por defecto
  void setOrtogonal();  // Establece una proyecci�n ortogonal
  void setPerspectiva();  // Establece una proyecci�n perspectiva
  void setOblicua();  // Establece una proyecci�n obl�cua

 public:
  // Constructoras y destructora
  Camara();
  Camara(PV3d* eye,PV3d* look,PV3d* up);
  ~Camara();
  // M�todos p�blicos
  void setView();  // Posiciona la c�mara en OpenGL mediante gluLookAt()
  void setView(PV3d* eye,PV3d* look,PV3d* up);  // Posiciona la c�mara en OpenGL con nuevos valores mediante gluLookAt() y llama a setModelViewMatrix()
  void setModelViewMatrix();  // Carga la matriz de modelado-vista de forma manual
  void setTipoP(int tipo);  // Cambia la variable 'tipo' para saber cambiar la proyecci�n con setProyeccion()
  void setProyeccion();  // Ejecuta la proyecci�n seg�n la variable 'tipo'
  void setLimits(double xLeft,double xRight,double yBot,double yTop,double N,double F);  // Establece los l�mites de la proyecci�n
  void setVO(float x,float y,float z);  // Establece el vector obl�cuo para la proyecci�n perspectiva obl�cua
  void setParamPers(double a,double p);  // Establece el �ngulo y el ratio para la proyecci�n perspectiva
  // M�todos p�blicos para mover la c�mara
  void roll(double a);  // Rota la c�mara respecto al eje 'n'
  void pitch(double a);  // Rota la c�mara respecto al eje 'u'
  void yaw(double a);  // Rota la c�mara respecto al eje 'v'
  void desplazamiento(double x,double y,double z);  // Desplaza el 'eye' de la c�mara
 };

#endif