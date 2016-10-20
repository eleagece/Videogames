#pragma hdrstop
#include "Tablero.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
Tablero::Tablero(int nx, int ny, int nz, float longx, float longy, float longz)
 {
 this->nx=nx; this->ny=ny; this->nz=nz;
 this->longx=longx; this->longy=longy; this->longz=longz;
 this->genTablero();
 }

void Tablero::genTablero()
 {
 // A�ADIR A 'tv' PUNTOS DE 'PLANO XY LEJANO'
 PV3d* p;  // Puntos que se ir�n a�adiendo a tv
 float long_nx=longx/nx;  // Longitud de la cara nx
 float long_ny=longy/ny;  // Longitud de la cara ny
 float acum_long_nx=0;  // Acumulaci�n de la longitud en x (seg�n por el punto que estemos metiendo)
 float acum_long_ny=0;  // Acumulaci�n de la longitud en y (seg�n por el punto que estemos metiendo)
 for (int j=0; j<=ny; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nx; i++)  // Recorre todos los puntos en x
   {
   p=new PV3d(acum_long_nx,acum_long_ny,0,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nx)
    acum_long_nx=0;
   else
    acum_long_nx=acum_long_nx+long_nx;
   }
  if (j==ny)
   acum_long_ny=0;
  else
   acum_long_ny=acum_long_ny+long_ny;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO XY LEJANO'
 Cara* c;  // Caras que se ir�n a�adiendo a tc (son cuatro VNormal que es un par v�rtice,normal)
 PV3d* n;  // Normales que se ir�n a�adiendo a tn
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nx; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nx+j);  // V�rtice inferior izquierdo
   c->addV(i+j*nx+j+nx+1);  // V�rtice superior izquierdo
   c->addV(i+j*nx+j+nx+2);  // V�rtice superior derecho
   c->addV(i+j*nx+j+1);  // V�rtice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // A�ADIR A 'tv' PUNTOS DE 'PLANO XY CERCANO'
 int despl=tv->size();  // Para saber por qu� v�rtice vamos metiendo
 for (int j=0; j<=ny; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nx; i++)  // Recorre todos los puntos en x
   {
   p=new PV3d(acum_long_nx,acum_long_ny,longz,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nx)
    acum_long_nx=0;
   else
    acum_long_nx=acum_long_nx+long_nx;
   }
  if (j==ny)
   acum_long_ny=0;
  else
   acum_long_ny=acum_long_ny+long_ny;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO XY CERCANO'
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nx; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nx+j+despl);  // V�rtice inferior izquierdo
   c->addV(i+j*nx+j+1+despl);  // V�rtice inferior derecho
   c->addV(i+j*nx+j+nx+2+despl);  // V�rtice superior derecho
   c->addV(i+j*nx+j+nx+1+despl);  // V�rtice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // A�ADIR A 'tv' PUNTOS DE 'PLANO ZY IZQUIERDA'
 despl=tv->size();  // Para saber por qu� v�rtice vamos metiendo
 float long_nz=longz/nz;  // Longitud de la cara nz
 float acum_long_nz=0;  // Acumulaci�n de la longitud en z (seg�n por el punto que estemos metiendo)
 for (int j=0; j<=ny; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nz; i++)  // Recorre todos los puntos en z
   {
   p=new PV3d(0,acum_long_ny,acum_long_nz,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nz)
    acum_long_nz=0;
   else
    acum_long_nz=acum_long_nz+long_nz;
   }
  if (j==ny)
   acum_long_ny=0;
  else
   acum_long_ny=acum_long_ny+long_ny;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO ZY IZQUIERDA'
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // V�rtice inferior izquierdo
   c->addV(i+j*nz+j+1+despl);  // V�rtice inferior derecho
   c->addV(i+j*nz+j+nz+2+despl);  // V�rtice superior derecho
   c->addV(i+j*nz+j+nz+1+despl);  // V�rtice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // A�ADIR A 'tv' PUNTOS DE 'PLANO ZY DERECHA'
 despl=tv->size();  // Para saber por qu� v�rtice vamos metiendo
 for (int j=0; j<=ny; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nz; i++)  // Recorre todos los puntos en z
   {
   p=new PV3d(longx,acum_long_ny,acum_long_nz,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nz)
    acum_long_nz=0;
   else
    acum_long_nz=acum_long_nz+long_nz;
   }
  if (j==ny)
   acum_long_ny=0;
  else
   acum_long_ny=acum_long_ny+long_ny;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO ZY DERECHA'
 //Cara* c;  // Caras que se ir�n a�adiendo a tc (son cuatro VNormal que es un par v�rtice,normal)
 //PV3d* n;  // Normales que se ir�n a�adiendo a tn
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // V�rtice inferior izquierdo
   c->addV(i+j*nz+j+nz+1+despl);  // V�rtice superior izquierdo
   c->addV(i+j*nz+j+nz+2+despl);  // V�rtice superior derecho
   c->addV(i+j*nz+j+1+despl);  // V�rtice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // A�ADIR A 'tv' PUNTOS DE 'PLANO ZX ABAJO'
 despl=tv->size();  // Para saber por qu� v�rtice vamos metiendo
 for (int j=0; j<=nx; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nz; i++)  // Recorre todos los puntos en z
   {
   p=new PV3d(acum_long_nx,0,acum_long_nz,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nz)
    acum_long_nz=0;
   else
    acum_long_nz=acum_long_nz+long_nz;
   }
  if (j==nx)
   acum_long_nx=0;
  else
   acum_long_nx=acum_long_nx+long_nx;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO ZX ABAJO'
 for (int j=0; j<nx; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // V�rtice inferior izquierdo
   c->addV(i+j*nz+j+nz+1+despl);  // V�rtice superior izquierdo
   c->addV(i+j*nz+j+nz+2+despl);  // V�rtice superior derecho
   c->addV(i+j*nz+j+1+despl);  // V�rtice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // A�ADIR A 'tv' PUNTOS DE 'PLANO ZX ARRIBA'
 despl=tv->size();  // Para saber por qu� v�rtice vamos metiendo
 for (int j=0; j<=nx; j++)  // Recorre todos los puntos en y
  {
  for (int i=0; i<=nz; i++)  // Recorre todos los puntos en z
   {
   p=new PV3d(acum_long_nx,longy,acum_long_nz,1);
   tv->push_back(p);  // Introduce el punto en en tv
   if (i==nz)
    acum_long_nz=0;
   else
    acum_long_nz=acum_long_nz+long_nz;
   }
  if (j==nx)
   acum_long_nx=0;
  else
   acum_long_nx=acum_long_nx+long_nx;
  }
 // A�ADIR A 'tc' CARAS DE 'PLANO ZX ARRIBA'
 for (int j=0; j<nx; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // V�rtice inferior izquierdo
   c->addV(i+j*nz+j+1+despl);  // V�rtice inferior derecho
   c->addV(i+j*nz+j+nz+2+despl);  // V�rtice superior derecho
   c->addV(i+j*nz+j+nz+1+despl);  // V�rtice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el �ndice de la normal de todos los v�rtices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 }
