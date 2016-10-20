#pragma hdrstop
#include "Sofa.h"
#pragma package(smart_init)

Sofa::Sofa()//:ObjetoCompuesto3D()
 {
 // Respaldo
 Tablero* respaldo=new Tablero(7,2,2,7,2.5,0.7);
 respaldo->setColor(0.8,0.8,0.0);
 respaldo->getTAfin()->traslada(0,0.2,0);
 objetos->push_back(respaldo);
 // Asiento
 Tablero* asiento=new Tablero(2,2,2,7,0.7,2.5);
 asiento->setColor(0.8,0.8,0.0);
 asiento->getTAfin()->traslada(0,0.2,0);
 objetos->push_back(asiento);
 // pata1
 Cilindro* pata1=new Cilindro(0.2,0.2,0.2,8,8);
 pata1->setColor(0.3,0.2,0.1);
 pata1->getTAfin()->traslada(0.3,0,0.3);
 pata1->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata1);
 // pata2
 Cilindro* pata2=new Cilindro(0.2,0.2,0.2,8,8);
 pata2->setColor(0.3,0.2,0.1);
 pata2->getTAfin()->traslada(6.7,0,0.3);
 pata2->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata2);
 // pata3
 Cilindro* pata3=new Cilindro(0.2,0.2,0.2,8,8);
 pata3->setColor(0.3,0.2,0.1);
 pata3->getTAfin()->traslada(0.3,0,2.3);
 pata3->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata3);
 // pata4
 Cilindro* pata4=new Cilindro(0.2,0.2,0.2,8,8);
 pata4->setColor(0.3,0.2,0.1);
 pata4->getTAfin()->traslada(6.7,0,2.3);
 pata4->getTAfin()->rota(-90,1,0,0);
 objetos->push_back(pata4);
 // reposabrazos1
 Cilindro* reposabrazos1=new Cilindro(0.3,0.3,2.5,8,8);
 reposabrazos1->setColor(0.3,0.2,0.1);
 reposabrazos1->getTAfin()->traslada(0,1.2,0);
 objetos->push_back(reposabrazos1);
 // reposabrazos2
 Cilindro* reposabrazos2=new Cilindro(0.3,0.3,2.5,8,8);
 reposabrazos2->setColor(0.3,0.2,0.1);
 reposabrazos2->getTAfin()->traslada(7,1.2,0);
 objetos->push_back(reposabrazos2);
 }
