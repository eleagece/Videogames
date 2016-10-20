#pragma hdrstop
#include "Television.h"
#pragma package(smart_init)

Television::Television()
 {
 apagada=true;
 // Carcasa de la tv
 Tablero* tv=new Tablero(8,4,2,8.2,4.7,0.2);
 tv->setColor(0.1,0.1,0.1);
 objetos->push_back(tv);
 // Pantalla
 tft=new Tablero(8,4,2,8,4.5,0.3,"standby.bmp",0,1,0,0,0,0,false);
 tft->setColor(1,1,1);
 tft->getTAfin()->traslada(0.1,0.1,0);
 objetos->push_back(tft);
 }

void Television::setTV()
 {
 if (apagada)
  {
  tft->setTextura("abyss.bmp");
  }
 else
  {
  tft->setTextura("standby.bmp");
  }
 apagada=!apagada;
 }
