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
    EVT_BUTTON(idLoadButton,CryptologyFrame::LoadImage)
END_EVENT_TABLE()


CryptologyFrame::CryptologyFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    //add a panel to the background
    wxPanel* panel = new wxPanel(this, idPanel);

    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();

   //create file menu
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    //create encrypt menu
    wxMenu* encryptMenu = new wxMenu(_T(""));
    encryptMenu->Append(idMenuEmbedImage, _("&Image to Image"), _("Show info about this application"));
    encryptMenu->Append(idMenuEmbedImage2, _("&Audio to Image"), _("Show info about this application"));
    mbar->Append(encryptMenu, _("&Encode"));

    //create decrypt menu
    wxMenu* decryptMenu = new wxMenu(_T(""));
    decryptMenu->Append(idMenuDecrypt, _("&Image from Image"), _("Show info about this application"));
    mbar->Append(decryptMenu, _("&Decode"));

    SetMenuBar(mbar);

    //set up buttons
    loadImageButton = new wxButton(panel,idLoadButton, _T("Load"), wxPoint(260,50),wxSize(75,25));
    loadImageButton->Show(false);

    loadImageButton2 = new wxButton(panel,idLoadButton2, _T("Load"), wxPoint(260,110),wxSize(75,25));
    loadImageButton2->Show(false);

    //set up textboxes
    txtImageFile = new wxTextCtrl(panel,idTxtBox,_T(""), wxPoint(50,50),wxSize(200,25));
    txtImageFile->Show(false);
    txtImageFile->SetEditable(false);

    txtImageFile2 = new wxTextCtrl(panel,idTxtBox2,_T(""), wxPoint(50,110),wxSize(200,25));
    txtImageFile2->Show(false);
    txtImageFile2->SetEditable(false);


    //set up labels
    label1 = new wxStaticText(panel,idLabel,_T("Load Image To Hide"),wxPoint(50,30));
    label1->Show(false);

    label2 = new wxStaticText(panel,idLabel2,_T("Load Cover Image"),wxPoint(50,90));
    label2->Show(false);

    //set up dialogs
    OpenDialog = new wxFileDialog(this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
                                "Images files (*.bmp;)|*.bmp;",wxFD_OPEN, wxDefaultPosition);
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
    loadImageButton->Show(true);
    loadImageButton2->Show(true);
    txtImageFile->Show(true);
    txtImageFile2->Show(true);
    label1->Show(true);
    label2->Show(true);

}

//the user clicked on second sub menu of Encrypt "Embed audio to image"
void CryptologyFrame::OnSecondEncryptMethod(wxCommandEvent &event)
{
    wxString msg = "I finally made another menu";
    wxMessageBox(msg, _("Welcome to..."));
}

//the user clicked on first sub menu of decrypt "Decrypt Image"
void CryptologyFrame::OnDecryptMethod(wxCommandEvent &event)
{
    wxString msg = "I finally made another menu";
    wxMessageBox(msg, _("Welcome to..."));
}

//the user clicked on load button
void CryptologyFrame::LoadImage(wxCommandEvent &event)
{
    //user selects a bitmap file and hits ok
    if(OpenDialog->ShowModal() == wxID_OK)
    {

        txtImageFile->SetValue( OpenDialog->GetPath());
        wxMessageBox("Hello", _("Welcome to AMERICA"));
    }

    //clean up dialog
    OpenDialog->Destroy();
}
