#ifndef TableroH
#define TableroH
#include "Malla.h"
#include "Textura.h"

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
  bool textura;  // Indica si el tablero tiene o no textura
  Textura* bitmap;  // La textura del tablero
  bool divisiones;  // Indica si la textura ocupa toda la cara o se replica
  bool XYLej, XYCer;  // Booleanos que indican qué cara del tablero lleva textura
  bool ZYIzq, ZYDer;
  bool ZXAba, ZXArr;
  // Métodos privados
  void genTablero();

 public:
  // Constructoras y destructora
  Tablero(int nx,int ny,int nz,float longx,float longy,float longz);
  Tablero(int nx,int ny,int nz,float longx,float longy,float longz,string path,
          bool XYLej,bool XYCer,bool ZYIzq,bool ZYDer,bool ZXAba,bool ZXArr,bool divisiones);
  ~Tablero();
  // Métodos públicos
  void dibuja();
  void dibujaConTextura();
  void setTextura(string path);
 };

#endif
