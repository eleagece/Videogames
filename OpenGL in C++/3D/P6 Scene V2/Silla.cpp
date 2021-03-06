#pragma hdrstop
#include "Silla.h"
#pragma package(smart_init)

Silla::Silla()//:ObjetoCompuesto3D()
 {
 // Respaldo
 Tablero* respaldo=new Tablero(2,2,2,0.2,2,1.5);
 respaldo->setColor(0.8,0.8,0.0);
 respaldo->getTAfin()->traslada(0,1,0);
 objetos->push_back(respaldo);
 // Asiento
 Tablero* asiento=new Tablero(2,2,2,1.5,0.2,1.5);
 asiento->setColor(0.8,0.8,0.0);
 asiento->getTAfin()->traslada(0,1,0);
 objetos->push_back(asiento);
 // pata1
 Cilindro* pata1=new Cilindro(0.1,0.1,1,8,8);
 pata1->setColor(0.3,0.2,0.1);
 pata1->getTAfin()->traslada(0.15,0,0.15);
 pata1->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata1);
 // pata2
 Cilindro* pata2=new Cilindro(0.1,0.1,1,8,8);
 pata2->setColor(0.3,0.2,0.1);
 pata2->getTAfin()->traslada(0.15,0,1.25);
 pata2->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata2);
 // pata3
 Cilindro* pata3=new Cilindro(0.1,0.1,1,8,8);
 pata3->setColor(0.3,0.2,0.1);
 pata3->getTAfin()->traslada(1.25,0,1.25);
 pata3->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata3);
 // pata4
 Cilindro* pata4=new Cilindro(0.1,0.1,1,8,8);
 pata4->setColor(0.3,0.2,0.1);
 pata4->getTAfin()->traslada(1.25,0,0.15);
 pata4->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata4);
 }
