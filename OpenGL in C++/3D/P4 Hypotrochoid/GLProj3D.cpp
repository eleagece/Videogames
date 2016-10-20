//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GLProj3D.res");
USEFORM("GLSkel3D.cpp", GLForm3D);
USEUNIT("VNormal.cpp");
USEUNIT("Cara.cpp");
USEUNIT("Malla.cpp");
USEUNIT("PV3d.cpp");
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
