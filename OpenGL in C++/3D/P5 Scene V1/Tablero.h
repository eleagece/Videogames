#ifndef TableroH
#define TableroH
#include "Malla.h"

class Tablero: public Malla  // Clase hija que hereda de Malla
 {
 private:
  // Atributos
  int nx;  // Divisiones de eje x
  int ny;  // Divisiones de eje y
  int nz;  // Divisiones de eje z
  float longx;  // Longitud del eje x
  float longy;  // Longitud del eje y
  float longz;  // Longitud del eje z
  // Métodos privados
  void genTablero();

 public:
  // Constructoras y destructora
  //Tablero(int nx,int ny,int nz);
  Tablero(int nx,int ny,int nz,float longx,float longy,float longz);
 };

#endif
