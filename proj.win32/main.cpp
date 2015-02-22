#include "main.h"

#ifdef XX_EXE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TESTS HERE ====================================

    xx::QuickMenu * qm = xx::xxQM::create ();
    xx::xxXML xmlDoc = xx::xxXML ("menu.xml");

    qm->setContent (xmlDoc);    

    // ===============================================

    return 0;
}

#endif // XX_EXE