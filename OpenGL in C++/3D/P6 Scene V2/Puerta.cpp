#pragma hdrstop
#include "Puerta.h"
#pragma package(smart_init)

Puerta::Puerta()
 {
 abierta=false;
 // puerta
 Tablero* puerta=new Tablero(2,4,2,0.2,4,2,"puerta.bmp",0,0,1,1,0,0,false);
 puerta->setColor(0.8,0.8,0);
 objetos->push_back(puerta);
 // pomo1
 Esfera* pomo1=new Esfera(0.1,5,5);
 pomo1->setColor(0.3,0.2,0.1);
 pomo1->getTAfin()->traslada(0.3,1.5,1.8);
 objetos->push_back(pomo1);
 // pomo2
 Esfera* pomo2=new Esfera(0.1,5,5);
 pomo2->setColor(0.3,0.2,0.1);
 pomo2->getTAfin()->traslada(-0.1,1.5,1.8);
 objetos->push_back(pomo2);
 }

void Puerta::setPuerta()
 {
 if (abierta)
  {
  m->rota(90,0,1,0);
  }
 else
  {
  m->rota(-90,0,1,0);
  }
 abierta=!abierta;
 }
