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
    EVT_MENU(idMenuEmbedImage, CryptologyFrame::OnTextEncodeMenu)
    EVT_MENU(idMenuEmbedImage2, CryptologyFrame::OnImageEncodeMenu)
    EVT_MENU(idMenuEmbedImage3, CryptologyFrame::OnFileEncodeMenu)
    EVT_MENU(idMenuDecrypt, CryptologyFrame::OnDecodeMenu)
    EVT_BUTTON(idLoadButton,CryptologyFrame::LoadImage)
    EVT_BUTTON(idLoadButton2,CryptologyFrame::LoadImage)
END_EVENT_TABLE()


CryptologyFrame::CryptologyFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    //add a panel to the background
    wxPanel* panel = new wxPanel(this, idPanel);

    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();

   //create file menu
    wxMenu* fileMenu = new wxMenu("");
    fileMenu->Append(idMenuQuit, "&Quit\tAlt-F4", "Quit the application");
    mbar->Append(fileMenu, "&File");

    //create encrypt menu
    wxMenu* encryptMenu = new wxMenu("");
    encryptMenu->Append(idMenuEmbedImage, "&Text to Image", "Show info about this application");
    encryptMenu->Append(idMenuEmbedImage2, "&Image to Image", "Show info about this application");
    encryptMenu->Append(idMenuEmbedImage3, "&File to Image", "Show info about this application");
    mbar->Append(encryptMenu, "&Encode");

    //create decrypt menu
    wxMenu* decryptMenu = new wxMenu("");
    decryptMenu->Append(idMenuDecrypt, "&Decode Image", "Show info about this application");
    mbar->Append(decryptMenu, "&Decode");

    SetMenuBar(mbar);

    //set up buttons
    loadButton = new wxButton(panel,idLoadButton, "Load", wxPoint(240,40),wxSize(75,25));
    loadButton->Show(false);

    loadButton2 = new wxButton(panel,idLoadButton2, "Load", wxPoint(240,100),wxSize(75,25));
    loadButton2->Show(false);

    loadButton3 = new wxButton(panel,idLoadButton3, "Load", wxPoint(30,90),wxSize(325,25));
    loadButton3->Show(false);

    encryptButton = new wxButton(panel,idEncryptButton, "Encrypt", wxPoint(300,150),wxSize(75,25));
    encryptButton->Show(false);

    decryptButton = new wxButton(panel,idDecryptButton, "Decrypt", wxPoint(30,130),wxSize(325,25));
    decryptButton->Show(false);

    //set up textboxes
    txtFile = new wxTextCtrl(panel,idTxtBox, "", wxPoint(30,40),wxSize(200,25));
    txtFile->Show(false);
    txtFile->SetEditable(false);

    txtFile2 = new wxTextCtrl(panel,idTxtBox2, "", wxPoint(30,100),wxSize(200,25));
    txtFile2->Show(false);
    txtFile2->SetEditable(false);

    txtMessage = new wxTextCtrl(panel,idTxtBox3, "", wxPoint(30,40),wxSize(285,25));
    txtMessage->Show(false);

    txtDecode = new wxTextCtrl(panel,idTxtBox4, "", wxPoint(30,50),wxSize(325,25));
    txtDecode->Show(false);
    txtDecode->SetEditable(false);

    //set up labels
    label1 = new wxStaticText(panel,idLabel3, "Write Text To Hide",wxPoint(30,20));
    label1->Show(false);

    label2 = new wxStaticText(panel,idLabel4, "Load Cover Image",wxPoint(30,80));
    label2->Show(false);

    label3 = new wxStaticText(panel,idLabel, "Load Image To Hide",wxPoint(30,20));
    label3->Show(false);

    label4 = new wxStaticText(panel,idLabel2, "Load Cover Image",wxPoint(30,80));
    label4->Show(false);


    label5 = new wxStaticText(panel,idLabel5, "Load File To Hide",wxPoint(30,20));
    label5->Show(false);

    label6 = new wxStaticText(panel,idLabel6, "Load Cover Image",wxPoint(30,80));
    label6->Show(false);

    label7 = new wxStaticText(panel,idLabel6, "Load Image To Decode",wxPoint(30,30));
    label7->Show(false);

    //set up dialogs
    OpenDialog = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
                                "Images files (*.bmp;)|*.bmp;",wxFD_OPEN, wxDefaultPosition);

    OpenDialog2 = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
                                "",wxFD_OPEN, wxDefaultPosition);
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

//the user clicked on first sub menu of Encode "Embed audio to image"
void CryptologyFrame::OnTextEncodeMenu(wxCommandEvent &event)
{
    state = 'A';
    ChangeState();
}

//the user clicked on second sub menu of Encrypt "Embed image to image"
void CryptologyFrame::OnImageEncodeMenu(wxCommandEvent &event)
{
    state = 'B';
    ChangeState();
}

//the user clicked on third sub menu of Encode "Embed audio to image"
void CryptologyFrame::OnFileEncodeMenu(wxCommandEvent &event)
{
    state = 'C';
    ChangeState();
}

//the user clicked on first sub menu of decode "Decrypt Image"
void CryptologyFrame::OnDecodeMenu(wxCommandEvent &event)
{
    state = 'D';
    ChangeState();
}

//the user loads image into textbox
void CryptologyFrame::LoadImage(wxCommandEvent &event)
{
    if(state == 'A')
    {
        //user selects a bitmap file and hits ok
        if(OpenDialog->ShowModal() == wxID_OK)
        {
            txtFile2->SetValue(OpenDialog->GetPath());
        }
    }
    else if(state == 'B')
    {
        //user selects a bitmap file and hits ok
        if(OpenDialog->ShowModal() == wxID_OK)
        {
            //user pressed the 1st load button in image to image menu
            if(event.GetId() == idLoadButton)
            {
                txtFile->SetValue( OpenDialog->GetPath());
            }

            //user pressed the 2nd load button in image to image menu
            if(event.GetId() == idLoadButton2)
            {
                txtFile2->SetValue(OpenDialog->GetPath());
            }
        }
    }
    else if(state == 'C')
    {
         //user pressed the 1st load button in image to image menu
        if(event.GetId() == idLoadButton)
        {
            //user selects a file and hits ok
            if(OpenDialog2->ShowModal() == wxID_OK)
            {
                txtFile->SetValue(OpenDialog2->GetPath());
            }
        }

        //user pressed the 2nd load button in image to image menu
        if(event.GetId() == idLoadButton2)
        {
            //user selects a bitmap file and hits ok
            if(OpenDialog->ShowModal() == wxID_OK)
            {
                txtFile2->SetValue(OpenDialog->GetPath());
            }
        }



    }
    else
    {

    }

}

    //the user clicked on first sub menu of decrypt "Decrypt Image"
void CryptologyFrame::ChangeState()
{
    if(state == 'A')
    {
        txtFile2->Clear();
        txtMessage->Clear();
        txtFile->Show(false);
        txtFile2->Show(true);
        txtMessage->Show(true);
        txtDecode->Show(false);
        label1->Show(true);
        label2->Show(true);
        label3->Show(false);
        label4->Show(false);
        label5->Show(false);
        label6->Show(false);
        label7->Show(false);
        encryptButton->Show(true);
        loadButton->Show(false);
        loadButton2->Show(true);
        txtDecode->Show(false);
        loadButton3->Show(false);
        decryptButton->Show(false);
    }
    else if(state == 'B')
    {
        txtFile->Clear();
        txtFile2->Clear();
        loadButton->Show(true);
        loadButton2->Show(true);
        txtFile->Show(true);
        txtFile2->Show(true);
        txtMessage->Show(false);
        encryptButton->Show(true);
        label1->Show(false);
        label2->Show(false);
        label3->Show(true);
        label4->Show(true);
        label5->Show(false);
        label6->Show(false);
        label7->Show(false);
        txtDecode->Show(false);
        loadButton3->Show(false);
        decryptButton->Show(false);
    }
    else if(state == 'C')
    {
        txtFile->Clear();
        txtFile2->Clear();
        loadButton->Show(true);
        loadButton2->Show(true);
        txtFile->Show(true);
        txtMessage->Show(false);
        txtFile2->Show(true);
        label1->Show(false);
        label2->Show(false);
        label3->Show(false);
        label4->Show(false);
        label5->Show(true);
        label6->Show(true);
        label7->Show(false);
        encryptButton->Show(true);
        txtDecode->Show(false);
        loadButton3->Show(false);
        decryptButton->Show(false);
    }
    else
    {
        txtDecode->Clear();
        txtDecode->Show(true);
        loadButton3->Show(true);
        label1->Show(false);
        label2->Show(false);
        label3->Show(false);
        label4->Show(false);
        label5->Show(false);
        label6->Show(false);
        label7->Show(true);
        loadButton->Show(false);
        loadButton2->Show(false);
        encryptButton->Show(false);
        decryptButton->Show(true);
        txtFile->Show(false);
        txtFile2->Show(false);
        txtMessage->Show(false);
    }
}
