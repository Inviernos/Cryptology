/***************************************************************
 * Name:      CryptologyApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Anthony Golubski-Allen, Ibrahim Sardar ()
 * Created:   2018-02-22
 * Copyright: Anthony Golubski-Allen, Ibrahim Sardar ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "CryptologyApp.h"
#include "CryptologyMain.h"

IMPLEMENT_APP(CryptologyApp);

bool CryptologyApp::OnInit()
{
    CryptologyFrame* frame = new CryptologyFrame(0L, _("Steganography"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
