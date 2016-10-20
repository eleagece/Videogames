#pragma hdrstop
#include "TAfin.h"
#pragma package(smart_init)

//****************************************************************************//
//*** Constructoras y destructora ********************************************//
//****************************************************************************//
TAfin::TAfin()
 {
 //---- Constructora por defecto ---------------------------------------------//
 //-- Llama a reset()                                                       --//
 //---------------------------------------------------------------------------//
 reset();
 }

//****************************************************************************//
//*** Métodos privados *******************************************************//
//****************************************************************************//
void TAfin::postMultiplica(GLfloat mm[])
 {
 //---- postMultiplica(...) --------------------------------------------------//
 //-- m = m * mm : aplica a la matriz 'm' que define un marco de coordena-  --//
 //-- das la transformación afín 'mm' devolviendo el resultado de nuevo en  --//
 //-- 'm'. Ahora 'm' es un nuevo marco de coordenadas tras la aplicación de --//
 //-- la transformación afín 'mm'                                           --//
 //---------------------------------------------------------------------------//
 glPushMatrix();
  glLoadMatrixf(m);  // Carga la matriz m sobre la que queremos hacer la transformación
  glMultMatrixf(mm);  // La postmultiplica por la matriz mm
  glGetFloatv(GL_MODELVIEW_MATRIX,m);  // Sacamos el resultado de nuevo en m
 glPopMatrix();
 }

//****************************************************************************//
//*** Métodos públicos *******************************************************//
//****************************************************************************//
void TAfin::reset()
 {
 //---- reset() --------------------------------------------------------------//
 //-- Carga la matriz identidad                                             --//
 //---------------------------------------------------------------------------//
 m[0]=1.0;  m[1]=0.0;  m[2]=0.0;  m[3]=0.0;
 m[4]=0.0;  m[5]=1.0;  m[6]=0.0;  m[7]=0.0;
 m[8]=0.0;  m[9]=0.0;  m[10]=1.0; m[11]=0.0;
 m[12]=0.0; m[13]=0.0; m[14]=0.0; m[15]=1.0;
 }

void TAfin::ejecutaTAfin()
 {
 //---- ejecutaTAfin() -------------------------------------------------------//
 //-- Multiplica la matriz de la cima por m de la transformación afín para  --//
 //-- que el objeto salga correctamente posicionado en la escena            --//
 //---------------------------------------------------------------------------//
 glMultMatrixf(m);
 }

void TAfin::traslada(float x, float y, float z)
 {
 //---- traslada() -----------------------------------------------------------//
 //-- Obtiene en 'mm' la matriz de transformación afín sobre el origen de   --//
 //-- x,y,z. Luego la postmultiplica por 'm' y el resultado lo guarda en    --//
 //-- 'm' para tener el marco de coordenadas actualizdo según la traslación --//
 //---------------------------------------------------------------------------//
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
  glLoadIdentity();
  glTranslatef(x,y,z);  // Se aplica traslación sobre el origen sobre x,y,z
  GLfloat mm[16];
  glGetFloatv(GL_MODELVIEW_MATRIX,mm);  // Se obtiene 'mm'
 glPopMatrix();
 postMultiplica(mm);  // Se hace m = m * mm para obtener el marco de coordenadas nuevo
 }

void TAfin::escala(float x, float y, float z)
 {
 //---- escala() -------------------------------------------------------------//
 //-- Obtiene en 'mm' la matriz de transformación afín sobre el origen de   --//
 //-- x,y,z. Luego la postmultiplica por 'm' y el resultado lo guarda en    --//
 //-- 'm' para tener el marco de coordenadas actualizdo según la escalación --//
 //---------------------------------------------------------------------------//
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
  glLoadIdentity();
  glScalef(x,y,z);  // Se aplica escalación sobre el origen sobre x,y,z
  GLfloat mm[16];
  glGetFloatv(GL_MODELVIEW_MATRIX,mm);  // Se obtiene 'mm'
 glPopMatrix();
 postMultiplica(mm);  // Se hace m = m * mm para obtener el marco de coordenadas nuevo
 }

void TAfin::rota(float a, float x, float y, float z)
 {
 //---- rota() ---------------------------------------------------------------//
 //-- Obtiene en 'mm' la matriz de transformación afín sobre el origen de a,--//
 //-- x,y,z. Luego la postmultiplica por 'm' y el resultado lo guarda en    --//
 //-- 'm' para tener el marco de coordenadas actualizdo según la escalación --//
 //---------------------------------------------------------------------------//
 glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
  glLoadIdentity();
  glRotatef(a,x,y,z);  // Se aplica rotación sobre el origen sobre x,y,z con ángulo a
  GLfloat mm[16];
  glGetFloatv(GL_MODELVIEW_MATRIX,mm);  // Se obtiene 'mm'
 glPopMatrix();
 postMultiplica(mm);  // Se hace m = m * mm para obtener el marco de coordenadas nuevo
 }

