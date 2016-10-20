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
 textura=false;
 divisiones=false;
 XYLej=false; XYCer=false; ZYIzq=false; ZYDer=false; ZXAba=false; ZXArr=false;
 }

Tablero::Tablero(int nx, int ny, int nz, float longx, float longy, float longz, string path,
                 bool XYLej, bool XYCer, bool ZYIzq, bool ZYDer, bool ZXAba, bool ZXArr, bool divisiones)
 {
 this->nx=nx; this->ny=ny; this->nz=nz;
 this->longx=longx; this->longy=longy; this->longz=longz;
 this->genTablero();
 textura=true;
 this->divisiones=divisiones;
 bitmap=new Textura(path);
 this->XYLej=XYLej; this->XYCer=XYCer;
 this->ZYIzq=ZYIzq; this->ZYDer=ZYDer;
 this->ZXAba=ZXAba; this->ZXArr=ZXArr;
 }

Tablero::~Tablero()
 {
 if (textura)
  {
  delete bitmap;
  }
 }

//****************************************************************************//
//*** Métodos privados *******************************************************//
//****************************************************************************//
void Tablero::genTablero()
 {
 // AÑADIR A 'tv' PUNTOS DE 'PLANO XY LEJANO'
 PV3d* p;  // Puntos que se irán añadiendo a tv
 float long_nx=longx/nx;  // Longitud de la cara nx
 float long_ny=longy/ny;  // Longitud de la cara ny
 float acum_long_nx=0;  // Acumulación de la longitud en x (según por el punto que estemos metiendo)
 float acum_long_ny=0;  // Acumulación de la longitud en y (según por el punto que estemos metiendo)
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
 // AÑADIR A 'tc' CARAS DE 'PLANO XY LEJANO'
 Cara* c;  // Caras que se irán añadiendo a tc (son cuatro VNormal que es un par vértice,normal)
 PV3d* n;  // Normales que se irán añadiendo a tn
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nx; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nx+j);  // Vértice inferior izquierdo
   c->addV(i+j*nx+j+nx+1);  // Vértice superior izquierdo
   c->addV(i+j*nx+j+nx+2);  // Vértice superior derecho
   c->addV(i+j*nx+j+1);  // Vértice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // AÑADIR A 'tv' PUNTOS DE 'PLANO XY CERCANO'
 int despl=tv->size();  // Para saber por qué vértice vamos metiendo
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
 // AÑADIR A 'tc' CARAS DE 'PLANO XY CERCANO'
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nx; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nx+j+despl);  // Vértice inferior izquierdo
   c->addV(i+j*nx+j+1+despl);  // Vértice inferior derecho
   c->addV(i+j*nx+j+nx+2+despl);  // Vértice superior derecho
   c->addV(i+j*nx+j+nx+1+despl);  // Vértice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // AÑADIR A 'tv' PUNTOS DE 'PLANO ZY IZQUIERDA'
 despl=tv->size();  // Para saber por qué vértice vamos metiendo
 float long_nz=longz/nz;  // Longitud de la cara nz
 float acum_long_nz=0;  // Acumulación de la longitud en z (según por el punto que estemos metiendo)
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
 // AÑADIR A 'tc' CARAS DE 'PLANO ZY IZQUIERDA'
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // Vértice inferior izquierdo
   c->addV(i+j*nz+j+1+despl);  // Vértice inferior derecho
   c->addV(i+j*nz+j+nz+2+despl);  // Vértice superior derecho
   c->addV(i+j*nz+j+nz+1+despl);  // Vértice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // AÑADIR A 'tv' PUNTOS DE 'PLANO ZY DERECHA'
 despl=tv->size();  // Para saber por qué vértice vamos metiendo
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
 // AÑADIR A 'tc' CARAS DE 'PLANO ZY DERECHA'
 //Cara* c;  // Caras que se irán añadiendo a tc (son cuatro VNormal que es un par vértice,normal)
 //PV3d* n;  // Normales que se irán añadiendo a tn
 for (int j=0; j<ny; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // Vértice inferior izquierdo
   c->addV(i+j*nz+j+nz+1+despl);  // Vértice superior izquierdo
   c->addV(i+j*nz+j+nz+2+despl);  // Vértice superior derecho
   c->addV(i+j*nz+j+1+despl);  // Vértice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // AÑADIR A 'tv' PUNTOS DE 'PLANO ZX ABAJO'
 despl=tv->size();  // Para saber por qué vértice vamos metiendo
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
 // AÑADIR A 'tc' CARAS DE 'PLANO ZX ABAJO'
 for (int j=0; j<nx; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // Vértice inferior izquierdo
   c->addV(i+j*nz+j+nz+1+despl);  // Vértice superior izquierdo
   c->addV(i+j*nz+j+nz+2+despl);  // Vértice superior derecho
   c->addV(i+j*nz+j+1+despl);  // Vértice inferior derecho
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 // AÑADIR A 'tv' PUNTOS DE 'PLANO ZX ARRIBA'
 despl=tv->size();  // Para saber por qué vértice vamos metiendo
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
 // AÑADIR A 'tc' CARAS DE 'PLANO ZX ARRIBA'
 for (int j=0; j<nx; j++)  // Recorre todas las caras en y
  {
  for (int i=0; i<nz; i++)  // Recorre todas las caras en x
   {
   c=new Cara();
   c->addV(i+j*nz+j+despl);  // Vértice inferior izquierdo
   c->addV(i+j*nz+j+1+despl);  // Vértice inferior derecho
   c->addV(i+j*nz+j+nz+2+despl);  // Vértice superior derecho
   c->addV(i+j*nz+j+nz+1+despl);  // Vértice superior izquierdo
   n=normalNewell(c); tn->push_back(n);  // Introduce la normal de la cara en tn
   c->setN(tn->size()-1);  // Actualiza el índice de la normal de todos los vértices de la cara
   tc->push_back(c);  // Introduce la cara en tc
   }
  }
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
void Tablero::dibuja()
 {
 if (!textura)  // Si es un tablero sin textura se dibuja como si fuese una malla
  {
  this->Malla::dibuja();
  }
 else  // Si es un tablero con textura se dibuja con textura
  {
  dibujaConTextura();
  }
 }

void Tablero::dibujaConTextura()
 {
 glPushMatrix();
  m->ejecutaTAfin();
  glColor4f(color->getR(),color->getG(),color->getB(),1.0);  // Color del tablero
  VNormal* aux;  // VNormal auxiliar para sacar los valores de los vértices con los que se va a pintar el tablero
  Cara* cara;
  GLfloat x=0.0; GLfloat y=0.0; GLfloat z=0.0;
  for (unsigned int i=0; i<tc->size(); i++)  // Dibuja todas las caras de la malla
   {
   cara=tc->at(i);  // Se obtiene la cara correspondiente a cada vuelta
   int n=cara->getPos(0)->getN();  // Se obtiene el índice de la normal en el vector 'tn' correspondiente a esta cara
   int v;  // Para obtener los índices de los vértices en el vector 'tv' correspondientes a esta cara
   glBegin(GL_QUADS);  // Dibuja un polígono de cuatro lados
    PV3d* normal=tn->at(n);  // Se obtiene la normal de la cara
    glNormal3d(normal->getX(),normal->getY(),normal->getZ());  // Se pasa a glNormal3d para dibujar bien la cara
    // vértice 0
    aux=cara->getPos(0);  // VNormal de la posición 0 de la cara
    v=aux->getV();  // Se saca el índice del vértice
    x=tv->at(v)->getX();  // Se sacan los valores de las componentes del vértice
    y=tv->at(v)->getY();
    z=tv->at(v)->getZ();
    glVertex3d(x,y,z);  // Se pinta el vértice
    // vértice 1
    aux = cara->getPos(1);
    v=aux->getV();
    x=tv->at(v)->getX();
    y=tv->at(v)->getY();
    z=tv->at(v)->getZ();
    glVertex3d(x,y,z);
    // vértice 2
    aux = cara->getPos(2);
    v=aux->getV();
    x=tv->at(v)->getX();
    y=tv->at(v)->getY();
    z=tv->at(v)->getZ();
    glVertex3d(x,y,z);
    // vértice 3
    aux = cara->getPos(3);
    v=aux->getV();
    x=tv->at(v)->getX();
    y=tv->at(v)->getY();
    z=tv->at(v)->getZ();
    glVertex3d(x,y,z);
   glEnd();
   }
  glEnable(GL_TEXTURE_2D);  // Dibuja la textura de la cara correspondiente
  // Define la textura en OpenGL:
  // GL_TEXTURE_2D - Textura bidimensional
  // 0 - Nivel de detalle de la textura (0 si sólo hay una)
  // 3 - Número de componentes de color (3 correspondientes a RGB)
  // bitmap->getCols() - Ancho de la textura (potencia de 2)
  // bitmap->getRows() - Alto de la textura (potencia de 2)
  // 0 - Anchura del borde
  // GL_RGB - Formato de la información del píxel
  // GL_UNSIGNED_BYTE - tipo de datos de cada píxel
  // bitmap->getBMP() - puntero al array donde se almacenan los píxeles de la textura
  glTexImage2D(GL_TEXTURE_2D,0,3,bitmap->getCols(),bitmap->getRows(),0,GL_RGB,GL_UNSIGNED_BYTE,bitmap->getBMP());
  if (XYLej)
   {
   glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);
    glTexCoord2i(0,0);  // Esquina inferior izquierda
    glVertex3f(longx,0,-0.003);
    glTexCoord2i(1,0);  // Esquina inferior derecha
    glVertex3f(0,0,-0.003);
    glTexCoord2i(1,1);  // Esquina superior derecha
    glVertex3f(0,longy,-0.003);
    glTexCoord2i(0,1);  // Esquina superior izquierda
    glVertex3f(longx,longy,-0.003);
   glEnd();
   }
  if (XYCer)
   {
   glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2i(0,0);  // Esquina inferior izquierda
    glVertex3f(0,0,longz+0.003);
    glTexCoord2i(1,0);  // Esquina inferior derecha
    glVertex3f(longx,0,longz+0.003);
    glTexCoord2i(1,1);  // Esquina superior derecha
    glVertex3f(longx,longy,longz+0.003);
    glTexCoord2i(0,1);  // Esquina superior izquierda
    glVertex3f(0,longy,longz+0.003);
   glEnd();
   }
  if (ZYIzq)
   {
   glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2i(0,0);  // Esquina inferior izquierda
    glVertex3f(-0.003,0,0);
    glTexCoord2i(1,0);  // Esquina inferior derecha
    glVertex3f(-0.003,0,longz);
    glTexCoord2i(1,1);  // Esquina superior derecha
    glVertex3f(-0.003,longy,longz);
    glTexCoord2i(0,1);  // Esquina superior izquierda
    glVertex3f(-0.003,longy,0);
   glEnd();
   }
  if (ZYDer)
   {
   glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2i(0,0);  // Esquina inferior izquierda
    glVertex3f(longx+0.003,0,longz);
    glTexCoord2i(1,0);  // Esquina inferior derecha
    glVertex3f(longx+0.003,0,0);
    glTexCoord2i(1,1);  // Esquina superior derecha
    glVertex3f(longx+0.003,longy,0);
    glTexCoord2i(0,1);  // Esquina superior izquierda
    glVertex3f(longx+0.003,longy,longz);
   glEnd();
   }
  if (ZXArr)
   {
   //glBegin(GL_POLYGON);
    if (divisiones)
     {
     for (int i=0; i<nx; i++)
      {
      for (int j=0; j<nz; j++)
       {
       glBegin(GL_POLYGON);
        glNormal3d(0,1,0);
        glTexCoord2i(0,0);
        glVertex3d((longx/nx)*(i+1),longy+0.003,(longz/nz)*j);
        glTexCoord2i(1,0);
        glVertex3d((longx/nx)*(i+1),longy+0.003,(longz/nz)*(j+1));
        glTexCoord2i(1,1);
        glVertex3d((longx/nx)*i,longy+0.003,(longz/nz)*(j+1));
        glTexCoord2i(0,1);
        glVertex3d((longx/nx)*i,longy+0.003,(longz/nz)*j);
       glEnd();
       }
      } /*
     glNormal3f(0,1,0);
     glTexCoord2i(0,0);  // Esquina inferior izquierda
     glVertex3f(0,longy+0.003,longz);
     glTexCoord2i(nx,0);  // Esquina inferior derecha
     glVertex3f(longx,longy+0.003,longz);
     glTexCoord2i(nx,nz);  // Esquina superior derecha
     glVertex3f(longx,longy+0.003,0);
     glTexCoord2i(0,nz);  // Esquina superior izquierda
     glVertex3f(0,longy+0.003,0); */
     }
    else
     {
     glNormal3f(0,1,0);
     glTexCoord2i(0,0);  // Esquina inferior izquierda
     glVertex3f(0,longy+0.003,longz);
     glTexCoord2i(1,0);  // Esquina inferior derecha
     glVertex3f(longx,longy+0.003,longz);
     glTexCoord2i(1,1);  // Esquina superior derecha
     glVertex3f(longx,longy+0.003,0);
     glTexCoord2i(0,1);  // Esquina superior izquierda
     glVertex3f(0,longy+0.003,0);
     }
   //glEnd();
   }
  if (ZXAba)
   {
   glBegin(GL_POLYGON);
    if (divisiones)
     {
     glNormal3f(0,1,0);
     glTexCoord2i(0,0);  // Esquina inferior izquierda
     glVertex3f(longx,-0.003,longz);
     glTexCoord2i(nz,0);  // Esquina inferior derecha
     glVertex3f(0,-0.003,longz);
     glTexCoord2i(nz,nx);  // Esquina superior derecha
     glVertex3f(0,-0.003,0);
     glTexCoord2i(0,nx);  // Esquina superior izquierda
     glVertex3f(longx,-0.003,0);
     }
    else
     {
     glNormal3f(0,1,0);
     glTexCoord2i(0,0);  // Esquina inferior izquierda
     glVertex3f(longx,-0.003,longz);
     glTexCoord2i(1,0);  // Esquina inferior derecha
     glVertex3f(0,-0.003,longz);
     glTexCoord2i(1,1);  // Esquina superior derecha
     glVertex3f(0,-0.003,0);
     glTexCoord2i(0,1);  // Esquina superior izquierda
     glVertex3f(longx,-0.003,0);
     }
   glEnd();
   }
  glDisable(GL_TEXTURE_2D);
 glPopMatrix();
 }

void Tablero::setTextura(string path)
 {
 textura=true;
 delete bitmap;
 bitmap=new Textura(path);
 }                           
