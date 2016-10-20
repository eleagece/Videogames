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
  // Métodos privados
  void postMultiplica(GLfloat mm[]);  // m = m * mm

 public:
  // Constructora: inicializa m como la identidad;
  TAfin();
  // Métodos públicos
  void reset();  // Carga la identidad en la matriz
  void ejecutaTAfin();  // Ejecuta la transformación afín posmultiplicando la matriz m por la que se pasa por parámetro mm
  void traslada(float x,float y,float z);  // Almacena en m la transformación afín traslación
  void escala(float x,float y,float z);  // Almacena en m la transformación afín escalación
  void rota(float a,float x,float y,float z);  // Almacena en m la transformación afín rotación
 };

#endif