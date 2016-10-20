//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("PuntoV.cpp");
USEUNIT("Pelota.cpp");
USEUNIT("Escena.cpp");
USEUNIT("Obstaculo.cpp");
USEUNIT("Lapiz.cpp");
USEUNIT("Convexo.cpp");
USEUNIT("Corteza.cpp");
USEUNIT("Segmento.cpp");
USEUNIT("Circulo.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
