#pragma hdrstop
#include "copa.h"
#pragma package(smart_init)

Copa::Copa(int np, int nq, float h)//:Malla()
 {
 // Crear malla de la base
 this->addCirculo(np,RBASE,0);
 this->addCirculo(np,RPIE,ABASE*h);
 this->genMallaCil4(np);
 // Crear malla del pie
 this->addCirculo(np,RCAZO,(APIE+ABASE)*h);
 this->genMallaCil4(np);
 // Crear malla del cazo
 double inc=(ACAZO*h)/(double)nq;
 double r=0;
 double y=0;
 for (int i=0; i<nq; i++)  // N�mero de divisiones del cazo
  {
  y+=inc;
  r=sqrt(double(y));
  this->addCirculo(np,r,((APIE+ABASE)*h)+y);
  this->genMallaCil4(np);
  }
 }

