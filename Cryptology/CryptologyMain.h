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

        wxButton* embedImageButton;

    private:
        enum
        {
            idPanel = 1000,
            idMenuQuit,
            idMenuEmbedImage,
            idMenuEmbedImage2,
            idMenuDecrypt,
            idSubmitbutton

        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnFirstEncryptMethod(wxCommandEvent& event);
        void OnSecondEncryptMethod(wxCommandEvent& event);
        void OnDecryptMethod(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // CRYPTOLOGYMAIN_H
