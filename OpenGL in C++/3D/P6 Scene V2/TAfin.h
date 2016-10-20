#ifndef TAfinH
#define TAfinH
#include <vcl.h>
#include <gl\gl.h>
#include <gl\glu.h>

class TAfin
 {
 private:
  // Atributos
  GLfloat m[16];
  // M�todos privados
  void postMultiplica(GLfloat mm[]);  // m = m * mm

 public:
  // Constructora: inicializa m como la identidad;
  TAfin();
  // M�todos p�blicos
  void reset();  // Carga la identidad en la matriz
  void ejecutaTAfin();  // Ejecuta la transformaci�n af�n posmultiplicando la matriz m por la que se pasa por par�metro mm
  void traslada(float x,float y,float z);  // Almacena en m la transformaci�n af�n traslaci�n
  void escala(float x,float y,float z);  // Almacena en m la transformaci�n af�n escalaci�n
  void rota(float a,float x,float y,float z);  // Almacena en m la transformaci�n af�n rotaci�n
 };

#endif