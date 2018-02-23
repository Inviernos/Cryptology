/***************************************************************
 * Name:      CryptologyMain.cpp
 * Purpose:   Code for Application Frame
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

#include "CryptologyMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(CryptologyFrame, wxFrame)
    EVT_CLOSE(CryptologyFrame::OnClose)
    EVT_MENU(idMenuQuit, CryptologyFrame::OnQuit)
    EVT_MENU(idMenuEmbedImage, CryptologyFrame::OnFirstEncryptMethod)
    EVT_MENU(idMenuEmbedImage2, CryptologyFrame::OnSecondEncryptMethod)
    EVT_MENU(idMenuDecrypt, CryptologyFrame::OnDecryptMethod)
    EVT_BUTTON(idSubmitbutton,CryptologyFrame::OnFirstEncryptMethod)
END_EVENT_TABLE()


CryptologyFrame::CryptologyFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    wxPanel* panel = new wxPanel(this, idPanel);

    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();

   //create file menu
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    //create encrypt menu
    wxMenu* encryptMenu = new wxMenu(_T(""));
    encryptMenu->Append(idMenuEmbedImage, _("&Embed Image to Image"), _("Show info about this application"));
    encryptMenu->Append(idMenuEmbedImage2, _("&Embed audio to image"), _("Show info about this application"));
    mbar->Append(encryptMenu, _("&Encrypt"));

    //create decrypt menu
    wxMenu* decryptMenu = new wxMenu(_T(""));
    decryptMenu->Append(idMenuDecrypt, _("&Decrypt Image from Image"), _("Show info about this application"));
    mbar->Append(decryptMenu, _("&Decrypt"));

    SetMenuBar(mbar);

    //set up buttons
    embedImageButton = new wxButton(panel,idSubmitbutton, _T("Encrypt"), wxPoint(50,50),wxSize(50,50));
    embedImageButton->Show(false);

}


CryptologyFrame::~CryptologyFrame()
{
}

void CryptologyFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void CryptologyFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

//the user clicked on first sub menu of Encrypt "Embed image to image"
void CryptologyFrame::OnFirstEncryptMethod(wxCommandEvent &event)
{
    wxString msg = "I finally made another menu";
    wxMessageBox(msg, _("Welcome to Heaven"));
    embedImageButton->Show(true);

}

//the user clicked on second sub menu of Encrypt "Embed audio to image"
void CryptologyFrame::OnSecondEncryptMethod(wxCommandEvent &event)
{
    wxString msg = "I finally made another menu";
    wxMessageBox(msg, _("Welcome to..."));
}

//the user clicked on first sub menu of Decrypt "Decrypt Image"
void CryptologyFrame::OnDecryptMethod(wxCommandEvent &event)
{
    wxString msg = "I finally made another menu";
    wxMessageBox(msg, _("Welcome to..."));
}
