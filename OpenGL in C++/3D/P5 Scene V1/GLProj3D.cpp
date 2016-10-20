//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GLProj3D.res");
USEFORM("GLSkel3D.cpp", GLForm3D);
USEUNIT("Cara.cpp");
USEUNIT("Copa.cpp");
USEUNIT("Malla.cpp");
USEUNIT("PV3d.cpp");
USEUNIT("VNormal.cpp");
USEUNIT("Camara.cpp");
USE("GLProj3D.todo", ToDo);
USEUNIT("Tablero.cpp");
USEUNIT("Color.cpp");
USEUNIT("Objeto3D.cpp");
USEUNIT("TAfin.cpp");
USEUNIT("HabitacionV.cpp");
USEUNIT("ObjetoCompuesto3D.cpp");
USEUNIT("Escena.cpp");
USEUNIT("HabitacionL.cpp");
USEUNIT("Television.cpp");
USEUNIT("Puerta.cpp");
USEUNIT("ObjetoCuadrico.cpp");
USEUNIT("Esfera.cpp");
USEUNIT("Mesa.cpp");
USEUNIT("Muebles.cpp");
USEUNIT("Silla.cpp");
USEUNIT("Cilindro.cpp");
USEUNIT("Disco.cpp");
USEUNIT("Sofa.cpp");
USEUNIT("Estanteria.cpp");
USEUNIT("Hipotrocoide3D.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm3D), &GLForm3D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
