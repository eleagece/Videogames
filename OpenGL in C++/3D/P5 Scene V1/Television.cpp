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
 Tablero* tft=new Tablero(8,4,2,8,4.5,0.3);
 tft->setColor(0.4,0.4,0.4);
 tft->getTAfin()->traslada(0.1,0.1,0);
 objetos->push_back(tft);
 }

void Television::setTV()
 {
 if (apagada)
  {
  objetos->back()->setColor(1,1,1);
  }
 else
  {
  objetos->back()->setColor(0.4,0.4,0.4);
  }
 apagada=!apagada;
 }
