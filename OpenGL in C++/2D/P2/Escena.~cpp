#include <vcl.h>
#pragma hdrstop
#include "Escena.h"
#include <math>

//****************************************************************************//
// Constructores, destructor
//****************************************************************************//
Escena::Escena()
 {
 // Atributos new
 listaDibujosLineas=new Lista<DibujoLineas>();
 listaHipotrocoides=new Lista<Hipotrocoide>();
 pSI=new PuntoVector();
 pID=new PuntoVector();
 // Atributos normales
 xRight=200.0; xLeft=-xRight; yTop=xRight; yBot=-yTop;
 recortando=false;
 }

Escena::~Escena()
 {
 // Atributos new
 delete listaDibujosLineas;
 delete listaHipotrocoides;
 delete pSI;
 delete pID;
 }

//****************************************************************************//
// Getters
//****************************************************************************//
float Escena::DamexLeft()
 {
 return xLeft;
 }

float Escena::DamexRight()
 {
 return xRight;
 }

float Escena::DameyTop()
 {
 return yTop;
 }

float Escena::DameyBot()
 {
 return yBot;
 }

//****************************************************************************//
// Setters
//****************************************************************************//
void Escena::PonpSI(float x, float y)
 {
 pSI->ponX(x);
 pSI->ponY(y);
 }

void Escena::PonpID(float x, float y)
 {
 pID->ponX(x);
 pID->ponY(y);
 }

void Escena::PonRecortando(bool b)
 {
 recortando=b;
 }

//****************************************************************************//
// Métodos privados
//****************************************************************************//
void Escena::ZoomPrivado(float zoom, float& deltaX, float& deltaY)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Auxiliar de: "void Zoom(float)"
 // -Recibe "zoom" y según él, devuelve "deltaX" y "deltaY" que indican cuánto
 //  se aumentará o reducirá el área visible de la escena
 ///////////////////////////////////////////////////////////////////////////////
 if (zoom>1)
  {
  // disminución en las X y en las Y para reducir el área visible de la escena y
  //  ver dibujo más grande
  deltaX=((xRight-xLeft)*zoom)-(xRight-xLeft);
  deltaY=((yTop-yBot)*zoom)-(yTop-yBot);
  }
 else if (zoom<1)
  {
  // aumento en las X y en las Y para aumentar el área visible de la escena y
  //  ver dibujo más pequeño
  deltaX=(xRight-xLeft)-((xRight-xLeft)*zoom);
  deltaY=(yTop-yBot)-((yTop-yBot)*zoom);
  }
 else  // zoom==1
  {
  deltaX=0;
  deltaY=0;
  }
 }

void Escena::PintaRecorte()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Auxiliar de: "void Dibuja()"
 // -Crea un lápiz "l" desde el punto pSI (el cual se actualiza en cada
 //  FormMouseDown(...) con la opción de recorte seleccionada) y pinta un cua-
 //  drado hasta pID (el cual se actualiza cada FormMouseMove(...)) hasta el
 //  FormMouseUp(...) siguiente, en el cual, se destruye el lápiz "l".
 ///////////////////////////////////////////////////////////////////////////////
 PuntoVector* pvAux=new PuntoVector(pSI);
 Lapiz* l=new Lapiz(pvAux,0.0);  // lapiz con punto inicial pSI y ángulo de 0º
 l->Mover(pID->dameX()-pSI->dameX(),true);  // Mover(distancia,pintar)
 l->Girar(90.0);
 l->Mover(pID->dameY()-pSI->dameY(),true);
 l->Girar(90.0);
 l->Mover(pID->dameX()-pSI->dameX(),true);
 l->Girar(90.0);
 l->Mover(pID->dameY()-pSI->dameY(),true);
 delete pvAux;
 delete l;
 }

//****************************************************************************//
// Métodos públicos que modifican el área visible de la escena
//****************************************************************************//
void Escena::Resize(GLfloat RatioViewPort)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recibe "RatioViewPort" (que es el ratio del puerto de vista) tras haber
 //  cambiado el tamaño de la ventana (puerto de vista). Según "RatioViewPort",
 //  se modifica el área visible de la escena tocando los valores "xLeft",
 //  "xRight","yTop","yBot" para que no haya deformaciones
 ///////////////////////////////////////////////////////////////////////////////
 // Establecimiento de "ÁREA VISIBLE DE LA ESCENA" (volumen de vista)
 GLfloat RatioVolVista=xRight/yTop;  // Ratio del volumen de vista
 float centroXOld,centroYOld;
 centroXOld=(xRight+xLeft)/2;  // Se obtienen las posiciones del centro antiguo. En nuestro sistema de coordenadas será 0,0
 centroYOld=(yTop+yBot)/2;  // antes y después del resize, aunque se hace genérico para otros sistemas de coordenadas posibles.
 float nuevoAncho,nuevoAlto;
 if (RatioVolVista>=RatioViewPort)  // Hemos disminuido el ancho o hemos aumentado el alto del puerto de vista
  {                                 // lo que implica calcular un nuevo alto
  nuevoAlto=(xRight-xLeft)/RatioViewPort;  // Nuevo alto
  yTop=(nuevoAlto/2)+centroYOld;  // nuevo yTop, yBot
  yBot=centroYOld-(nuevoAlto/2);
  }
 else  // Hemos disminuido el alto o hemos aumentado el ancho del puerto de vista
  {    // lo que implica calcular un nuevo ancho
  nuevoAncho=(yTop-yBot)*RatioViewPort;  // Nuevo ancho
  xRight=(nuevoAncho/2)+centroXOld;  // Nuevos límites
  xLeft=centroXOld-(nuevoAncho/2);
  }
 // Restablecimiento del área visible de la escena
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(xLeft,xRight,yBot,yTop);
 // ¿¿¿¿¿¿¿¿¿¿¿ESTO QUÉ HACE???????????
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 }

void Escena::Zoom(float zoom)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recibe "zoom", según el cual modifica "xLeft","xRight","yTop","yBot" para
 //  que se vea más o menos del área visible de la escena
 ///////////////////////////////////////////////////////////////////////////////
 float deltaX,deltaY;
 ZoomPrivado(zoom,deltaX,deltaY);
 if (zoom>1)
  {
  // Aplica disminución a los valores que definen el área visible de la escena
  //  para verla más grande
  xRight=xRight-deltaX;
  xLeft=xLeft+deltaX;
  yTop=yTop-deltaY;
  yBot=yBot+deltaY;
  }
 if (zoom<1)
  {
  // Aplica aumento a los valores que definen el área visible de la escena
  //  para verla más pequeña
  xRight=xRight+deltaX;
  xLeft=xLeft-deltaX;
  yTop=yTop+deltaY;
  yBot=yBot-deltaY;
  }
 // Restablecimiento del área visible de la escena
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(xLeft,xRight,yBot,yTop);
 }

void Escena::Trasladar(int dir)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recibe "dir", según el cual modifica "xLeft","xRight","yTop","yBot" para
 //  que se traslade la escena 10 píxeles en la dirección que dir indique
 ///////////////////////////////////////////////////////////////////////////////
 float desplazamiento=10;
 switch (dir)
  {
  case 1:  // derecha
   xLeft=xLeft+desplazamiento;
   xRight=xRight+desplazamiento;
   break;
  case 2:  // abajo
   yTop=yTop-desplazamiento;
   yBot=yBot-desplazamiento;
   break;
  case 3:  // izquierda
   xLeft=xLeft-desplazamiento;
   xRight=xRight-desplazamiento;
   break;
  case 4:  // arriba
   yTop=yTop+desplazamiento;
   yBot=yBot+desplazamiento;
   break;
  }
 // Restablecimiento del área visible de la escena
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(xLeft,xRight,yBot,yTop);
 }

//****************************************************************************//
// Métodos públicos que dibujan dibujos de líneas e hipotrocoides
//****************************************************************************//
void Escena::Dibuja()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recorre "listaDibujosLineas" y "listaHipotrocoides" para pintar sus con-
 //  tenidos, los primeros en blanco, los segundos en amarillo. También pinta
 //  el cuadrado de crop en blanco si es necesario
 ///////////////////////////////////////////////////////////////////////////////
 listaDibujosLineas->inicia();
 listaHipotrocoides->inicia();
 for (int i=0; i<listaDibujosLineas->getLongitud(); i++)
  {
  listaDibujosLineas->getActual()->Dibuja();
  listaDibujosLineas->avanza();
  }
 for (int i=0; i<listaHipotrocoides->getLongitud(); i++)
  {
  listaHipotrocoides->getActual()->Dibuja();
  listaHipotrocoides->avanza();
  }
 if (recortando)
  PintaRecorte();
 }

void Escena::DibujaDibLineasSel()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recorre los segmentos de "dibLineasSel" y los pinta de color rojo
 ///////////////////////////////////////////////////////////////////////////////
 dibLineasSel->DibujaSelec();
 }

void Escena::DibujaHipotrocoSel()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Recorre los segmentos de "hipotrocoSel" y los pinta de color rojo
 ///////////////////////////////////////////////////////////////////////////////
 hipotrocoSel->DibujaSelec();
 }

//****************************************************************************//
// Métodos públicos que modifican los dibujos de líneas e hipotrocoides
//****************************************************************************//
void Escena::InsertarSegmento(float oX, float oY, float xAVE, float yAVE, bool primerSegmento)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Auxiliar de: "void InsertarEspiral(...)"
 //               "void InsertarPoligono(...)"
 // -Crea "dibLineasAux" con un segmento y lo inserta en la lista
 //  "listaDibujosLineas". Cada nuevo segmento que se crea se añade a
 //  "dibLineasAux", con lo cual, obviamente se actualiza "listaDibujosLineas"
 // -El segmento "seg" y el dibujo de líneas "dibLineasAux" se eliminarán al
 //  hacer el delete de "listaDibujosLineas" o al eliminar el elemento
 //  "dibLineasAux" al seleccionarlo en la pantalla con un clic
 ///////////////////////////////////////////////////////////////////////////////
 Segmento* seg=new Segmento(oX,oY,xAVE,yAVE);
 if (primerSegmento)
  {
  // crea un nuevo dibujo de líneas auxiliar para el dibujo de líneas que esta-
  // mos creando.
  dibLineasAux=new DibujoLineas();
  dibLineasAux->PonSegmento(seg);  // se mete primer "seg" en "dibLineasAux"
  listaDibujosLineas->inserta(dibLineasAux);  // se inserta "dibLineasAux"
  }                                           // en "listaDibujosLineas"
 else
  {
  dibLineasAux->PonSegmento(seg);  // se meten siguientes "seg" en "dibLineasAux"
  }                                // con lo cual se actualiza "dibLineasAux"
 }                                 // en "listaDibujosLineas"

void Escena::InsertarEspiral(float oX, float oY, int numIteraciones, float longLado, float incremento, int anguloGiro)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Introduce una espiral en "dibLineasAux". Cada segmento viene determinado
 //  por "longLado+incremento" para su longitud, por "anguloGiro" para ver
 //  hacia donde apunta y por "numIteraciones" para saber el número de segmen-
 //  tos que componen "dibLineasAux". Además se añade este "dibLineasAux" a
 //  "listaDibujoLineas"
 ///////////////////////////////////////////////////////////////////////////////
 int longitudLado=longLado;  // guarda "longLado"+"incremento"
 PuntoVector* origen=new PuntoVector(oX,oY);  // punto de origen "origen"
 Lapiz* l=new Lapiz(origen,0.0);  // usamos el punto de origen para crear "l"
 for (int i=0; i<numIteraciones; i++)
  {
  float oriX=l->DamePos()->dameX();  // obtenemos posiciones de origen
  float oriY=l->DamePos()->dameY();
  if (i==0)  // movemos el lapiz sin pintar desde "oriX"-"oriY" a "destX"-"destY"
   l->Mover(longitudLado,false);
  else
   {
   longitudLado=longitudLado+incremento;
   l->Mover(longitudLado,false);
   }
  float destX=l->DamePos()->dameX();  // obtenemos posiciones de destino
  float destY=l->DamePos()->dameY();
  InsertarSegmento(oriX,oriY,destX,destY,(i==0));
  l->Girar(anguloGiro);
  }
 delete origen;  // se elimina el punto "origen" porque el lápiz "l" no lo hace
 delete l;  // se elimina el lápiz "l"
 }
 
void Escena::InsertarPoligono(float oX, float oY, int numLados, float longLado)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Introduce un polígono regular en "dibLineasAux". Cada segmento viene de-
 //  terminado por "longLado" para su longitud y por "numLados" para saber el
 //  número de segmentos que componen "dibLineasAux". Además se añade este
 //  "dibLineasAux" a "listaDibujoLineas". Los ángulos "alphaRad", "bethaRad"
 //  y "gammaRad" sirven para ir calculando el ángulo de giro de los segmentos
 ///////////////////////////////////////////////////////////////////////////////
 float alphaRad=(2.0*M_PI)/(float)numLados;
 float bethaRad=(M_PI-alphaRad)/2.0;
 float gammaRad=M_PI-bethaRad;
 float gamma=gammaRad*(180.0/M_PI);
 float alpha=alphaRad*(180.0/M_PI);
 float radio=(longLado/2.0)/cos(bethaRad);
 PuntoVector* origen=new PuntoVector(oX+radio,oY);  // punto de origen "origen"
 Lapiz* l=new Lapiz(origen,gamma);  // usamos el punto de origen para crear "l"
 for (int i=0; i<numLados; i++)
  {
  float oriX=l->DamePos()->dameX();  // obtenemos posiciones de origen
  float oriY=l->DamePos()->dameY();
  l->Mover(longLado,false);  // movemos el lapiz sin pintar desde "oriX"-"oriY" a "destX"-"destY"
  float destX=l->DamePos()->dameX();  // obtenemos posiciones de destino
  float destY=l->DamePos()->dameY();
  InsertarSegmento(oriX,oriY,destX,destY,(i==0));
  l->Girar(alpha);
  }
 delete origen;  // se elimina el punto "origen" porque el lápiz "l" no lo hace
 delete l;  // se elimina el lápiz "l"
 }

void Escena::InsertarHipotrocoide(float oX, float oY, float a, float b, float c, float n)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -Inserta un hipotrocoide "hip" en "listaHipotrocoides"
 // -El hipotrocoide "hip" se eliminará al hacer el delete de
 //  "listaHipotrocoides"
 ///////////////////////////////////////////////////////////////////////////////
 Hipotrocoide* hip=new Hipotrocoide(oX,oY,a,b,c,n);
 listaHipotrocoides->inserta(hip);
 }

void Escena::Recorta()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 PuntoVector* R1=new PuntoVector(min(pSI->dameX(),pID->dameX()),max(pSI->dameY(),pID->dameY()));
 PuntoVector* R2=new PuntoVector(max(pSI->dameX(),pID->dameX()),min(pSI->dameY(),pID->dameY()));
 listaDibujosLineas->inicia();  // Para tener apuntando el primer dibujo de lineas
 listaHipotrocoides->inicia();
 for (int i=0; i<listaDibujosLineas->getLongitud(); i++)
  {
  listaDibujosLineas->getActual()->Recorta(R1,R2);
  listaDibujosLineas->avanza();
  }
 for (int i=0; i<listaHipotrocoides->getLongitud(); i++)
  {
  listaHipotrocoides->getActual()->Recorta(R1,R2);
  listaHipotrocoides->avanza();
  }
 delete R1;
 delete R2;
 }

bool Escena::BuscarHipotrocoide(float x, float y)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 int i=0;
 bool encontrado=false;
 listaHipotrocoides->inicia();
 while (i<listaHipotrocoides->getLongitud() && !encontrado)
  {
  encontrado=listaHipotrocoides->getActual()->SelecHipotrocoide(x,y);
  if (!encontrado)
   {
   i++;
   listaHipotrocoides->avanza();
   }
  }
 if (encontrado)
  {
  hipotrocoSel=listaHipotrocoides->getActual();
  }
 return encontrado;
 }

bool Escena::BuscarDibujoLineas(float x, float y)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 int i=0;
 bool encontrado=false;
 listaDibujosLineas->inicia();
 while (i<listaDibujosLineas->getLongitud() && !encontrado)
  {
  encontrado=listaDibujosLineas->getActual()->SelecDibujoLineas(x,y);
  if (!encontrado)
   {
   i++;
   listaDibujosLineas->avanza();
   }
  }
 if (encontrado)
  {
  dibLineasSel=listaDibujosLineas->getActual();
  }
 return encontrado;
 }

void Escena::CambiaPrecHipotrocoSel(bool precision)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 hipotrocoSel->Precisa(precision);
 }

void Escena::GiraHipotrocoSel()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 hipotrocoSel->Gira();
 }

//****************************************************************************//
// Métodos públicos que buscan dibujos de líneas e hipotrocoides en sus listas
//****************************************************************************//
void Escena::BorraDibLineasSel()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 bool encontrado=false;
 int i=0;
 while (i<listaDibujosLineas->getLongitud() && !encontrado)
  {
  if (i==0)
   listaDibujosLineas->inicia();
  if (listaDibujosLineas->getActual()==dibLineasSel)  // Hemos dado con el puntero a actualizar
   {
   encontrado=true;
   listaDibujosLineas->eliminaActual();
   }
  else
   {
   listaDibujosLineas->avanza();
   i++;
   }
  }
 }

void Escena::BorraHipotrocoSel()
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 bool encontrado=false;
 int i=0;
 while (i<listaHipotrocoides->getLongitud() && !encontrado)
  {
  if (i==0)
   listaHipotrocoides->inicia();
  if (listaHipotrocoides->getActual()==hipotrocoSel)  // Hemos dado con el puntero a actualizar
   {
   encontrado=true;
   listaHipotrocoides->eliminaActual();
   }
  else
   {
   listaHipotrocoides->avanza();
   i++;
   }
  }
 }

//****************************************************************************//
// Métodos que cargan y salvan dibujos de líneas e hipotrocoides
//****************************************************************************//
void Escena::salvaBin(ofstream& f)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 f.write((char*)&xRight,sizeof(float));
 f.write((char*)&xLeft,sizeof(float));
 f.write((char*)&yTop,sizeof(float));
 f.write((char*)&yBot,sizeof(float));
 int longD=listaDibujosLineas->getLongitud();
 int longH=listaHipotrocoides->getLongitud();
 f.write((char*)&longD,sizeof(float));
 f.write((char*)&longH,sizeof(float));
 listaDibujosLineas->inicia();
 listaHipotrocoides->inicia();
 for (int i=0; i<longD; i++)
  {
  listaDibujosLineas->getActual()->salvaDibLineas(f);
  listaDibujosLineas->avanza();
  }
 for (int i=0; i<longH; i++)
  {
  listaHipotrocoides->getActual()->salvaHipotrocoide(f);
  listaHipotrocoides->avanza();
  }
 }

void Escena::cargaBin(float ratio, ifstream& f)
 {
 ///////////////////////////////////////////////////////////////////////////////
 // -
 ///////////////////////////////////////////////////////////////////////////////
 delete listaDibujosLineas;
 delete listaHipotrocoides;
 listaDibujosLineas=new Lista<DibujoLineas>();
 listaHipotrocoides=new Lista<Hipotrocoide>();
 f.read((char*)&xRight,sizeof(float));
 f.read((char*)&xLeft,sizeof(float));
 f.read((char*)&yTop,sizeof(float));
 f.read((char*)&yBot,sizeof(float));
 int longD;
 int longH;
 f.read((char*)&longD,sizeof(float));
 f.read((char*)&longH,sizeof(float));
 for (int i=0; i<longD; i++)
  {
  DibujoLineas* aux=new DibujoLineas();
  aux->cargaDibLineas(f);
  listaDibujosLineas->inserta(aux);
  }
 for (int i=0; i<longH; i++)
  {
  Hipotrocoide* aux=new Hipotrocoide();
  aux->cargaHipotrocoide(f);
  listaHipotrocoides->inserta(aux);
  }
 Resize(ratio);
 /*glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(xLeft,xRight,yBot,yTop);*/
 }
#pragma package(smart_init)



