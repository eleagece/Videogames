#ifndef TexturaH
#define TexturaH
#include <gl\gl.h>
#include <gl\glu.h>
#include <string>
using namespace std;

typedef GLubyte colorRGBA[3];

class Textura
 {
 private:
  GLuint nCols;  // Columnas de la textura
  GLuint nRows;  // Filas de la textura
  colorRGBA* pixmap;  // Array de colores de cada p�xel de la textura

  void recoloca(Graphics::TBitmap* AuxBMP);

 public:
  Textura();
  Textura(const string& arch);
  ~Textura();
  GLuint getCols();
  GLuint getRows();
  colorRGBA* getBMP();
  bool cargaBMP(const string& arch);
 };

 #endif

