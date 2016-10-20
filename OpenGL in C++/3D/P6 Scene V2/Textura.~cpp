#include <vcl.h>
#pragma hdrstop
#include "Textura.h"
#pragma package(smart_init)

Textura::Textura()
 {
 pixmap=NULL;
 nCols=0;
 nRows=0;
 }

Textura::Textura(const string& arch)
 {
 pixmap=NULL;
 nCols=0;
 nRows=0;
 cargaBMP(arch);  // Carga la textura desde archivo
 }

Textura::~Textura()
 {
 delete[] pixmap;
 }

GLuint Textura::getCols()
 {
 return nCols;
 }

GLuint Textura::getRows()
 {
 return nRows;
 }

colorRGBA* Textura::getBMP()
 {
 return pixmap;  // Devuelve las 256x256 posiciones que representan la textura con su color
 }

bool Textura::cargaBMP(const string& arch)
 {
 Graphics::TBitmap* AuxBMP=new Graphics::TBitmap();
 AuxBMP->LoadFromFile(arch.c_str());
 if (AuxBMP->Empty)  // Si no se ha cargado el .bmp correctamente...
  {
  delete AuxBMP;
  return false;
  }
 else  // Si sí se ha cargado correctamente...
  {
  recoloca(AuxBMP);
  delete AuxBMP;
  return true;
  }
 }

void Textura::recoloca(Graphics::TBitmap* AuxBMP)
 {
 delete pixmap;
 pixmap=new colorRGBA[AuxBMP->Width*AuxBMP->Height];  // pixmap de tamaño textura (256x256 en las que uso)
 nCols=AuxBMP->Width;
 nRows=AuxBMP->Height;
 int count;
 unsigned int i, j;
 for (i=0; i<nRows; i++)  // Se recorren las 256x256 posiciones del AuxBMP para rellenar las 256x256 posiciones del pixmap
  {                       // con coloresRGB
  for (j=0; j<nCols; j++)
   {
   count=i*nCols + j;
   pixmap[count][0]=GetRValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
   pixmap[count][1]=GetGValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
   pixmap[count][2]=GetBValue(AuxBMP->Canvas->Pixels[j][nRows-i-1]);
   }
  }
 }


