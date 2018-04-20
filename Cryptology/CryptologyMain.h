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
#include "CImg.h"
#include <iostream>
#include <bitset>
#include <math.h>
#include <string>
#include <sstream>
#include<vector>


using namespace std;
using namespace cimg_library;

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
        wxFileDialog* SaveDialog;

        //variables for image to image
        int cover_image_max_pixels;
        int hide_image_max_pixels;
        int max_pixels_to_hide;
        unsigned int max_letters_to_hide;
        int color_value;
        bitset<11> total_bits_image_width;
        bitset<11> total_bits_image_height;
        bitset<11> total_bits_cover_image_width;
        bitset<11> total_bits_cover_image_height;
        bitset<2> codes;
        bool isRightSize;
        int change_bits_per_pixel;
        int total_bits_per_pixel;
        int current_x;
        int current_y;
        int current_channel;
        int bit_index;
        string color;
        string total_bit_size;
        bitset<8> letter;
        bitset<8> red;
        bitset<8> green;
        bitset<8> blue;
        bitset<8> cover_color;
        bool start_hiding_pixel_data;
        int hidden_image_width;
        int hidden_image_height;
        int stego_image_height;
        int stego_image_width;
        bool start_finding_pixel_data;
        bool keepGoing;
        bitset<2> bit_data;
        bitset<16> charSize;

        //Yousef
        bitset<8> b;
        vector<int> a;
        int width;
        int height;
        unsigned int counter;


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
        void LeastSignificantBit(wxCommandEvent&event);
        void EncodeImagetoImage();
        void EncodeTexttoImage();
        void EncodeFiletoImage();
        void DecodeImage();
        void ChangeState();
        void TextToBinary(string s);
        DECLARE_EVENT_TABLE()
};


#endif // CRYPTOLOGYMAIN_H
