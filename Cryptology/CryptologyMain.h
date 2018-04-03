/***************************************************************
 * Name:      CryptologyMain.h
 * Purpose:   Defines Application Frame
 * Author:    Anthony Golubski-Allen, Ibrahim Sardar ()
 * Created:   2018-02-22
 * Copyright: Anthony Golubski-Allen, Ibrahim Sardar ()
 * License:
 **************************************************************/

#ifndef CRYPTOLOGYMAIN_H
#define CRYPTOLOGYMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "CryptologyApp.h"

class CryptologyFrame: public wxFrame
{
    public:
        CryptologyFrame(wxFrame *frame, const wxString& title);
        ~CryptologyFrame();



    private:
        char state;
        wxButton* loadButton;
        wxButton* loadButton2;
        wxButton* loadButton3;
        wxButton* encryptButton;
        wxButton* decryptButton;
        wxTextCtrl* txtFile;
        wxTextCtrl* txtFile2;
        wxTextCtrl* txtMessage;
        wxTextCtrl* txtDecode;
        wxStaticText* label1;
        wxStaticText* label2;
        wxStaticText* label3;
        wxStaticText* label4;
        wxStaticText* label5;
        wxStaticText* label6;
        wxStaticText* label7;
        wxFileDialog* OpenDialog;
        wxFileDialog* OpenDialog2;


        enum
        {
            idPanel = 1000,
            idMenuQuit,
            idMenuEmbedImage,
            idMenuEmbedImage2,
            idMenuEmbedImage3,
            idMenuDecrypt,
            idLoadButton,
            idLoadButton2,
            idLoadButton3,
            idEncryptButton,
            idDecryptButton,
            idTxtBox,
            idTxtBox2,
            idTxtBox3,
            idTxtBox4,
            idLabel,
            idLabel2,
            idLabel3,
            idLabel4,
            idLabel5,
            idLabel6,
            idLabel7

        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnImageEncodeMenu(wxCommandEvent& event);
        void OnTextEncodeMenu(wxCommandEvent& event);
        void OnFileEncodeMenu(wxCommandEvent& event);
        void OnDecodeMenu(wxCommandEvent& event);
        void LoadImage(wxCommandEvent& event);
        void ChangeState();
        DECLARE_EVENT_TABLE()
};


#endif // CRYPTOLOGYMAIN_H
