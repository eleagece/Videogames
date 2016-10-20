#pragma hdrstop
#include "Estanteria.h"
#pragma package(smart_init)

Estanteria::Estanteria()//:ObjetoCompuesto3D()
 {
 // base
 Tablero* base=new Tablero(6,2,2,6,0.2,1);
 base->setColor(0.8,0.8,0.0);
 objetos->push_back(base);
 // libro de pie 1
 Tablero* libro1=new Tablero(2,2,2,0.2,1.2,0.8);
 libro1->setColor(0.3,0.2,0.1);
 libro1->getTAfin()->traslada(1,0.2,0);
 objetos->push_back(libro1);
 // libro de pie 2
 Tablero* libro2=new Tablero(2,2,2,0.2,1.0,0.9);
 libro2->setColor(0.3,0.2,0.1);
 libro2->getTAfin()->traslada(1.5,0.2,0);
 objetos->push_back(libro2);
 // libro tumbado
 Tablero* libro3=new Tablero(2,2,2,1.2,0.3,0.8);
 libro3->setColor(0.3,0.2,0.1);
 libro3->getTAfin()->traslada(3,0.2,0);
 objetos->push_back(libro3);
 }
