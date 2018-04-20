/***************************************************************
 * Name:      CryptologyMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Anthony Golubski-Allen, Ibrahim Sardar, Yousef Alsaadi()
 * Created:   2018-02-22
 * Copyright: Anthony Golubski-Allen, Ibrahim Sardar, Yousef ()
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


/**
    Note: the function "_()" takes in a string and handles Unicode characters for localization properly
**/
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
    EVT_BUTTON(idLoadButton3,CryptologyFrame::LoadImage)
    EVT_BUTTON(idEncryptButton,CryptologyFrame::LeastSignificantBit)
    EVT_BUTTON(idDecryptButton,CryptologyFrame::LeastSignificantBit)
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
    label1 = new wxStaticText(panel,idLabel, "Write Text To Hide",wxPoint(30,20));
    label1->Show(false);

    label2 = new wxStaticText(panel,idLabel2, "Load Cover Image",wxPoint(30,80));
    label2->Show(false);

    label3 = new wxStaticText(panel,idLabel3, "Load Image To Hide",wxPoint(30,20));
    label3->Show(false);

    label4 = new wxStaticText(panel,idLabel4, "Load Cover Image",wxPoint(30,80));
    label4->Show(false);


    label5 = new wxStaticText(panel,idLabel5, "Load File To Hide",wxPoint(30,20));
    label5->Show(false);

    label6 = new wxStaticText(panel,idLabel6, "Load Cover Image",wxPoint(30,80));
    label6->Show(false);

    label7 = new wxStaticText(panel,idLabel7, "Load Image To Decode",wxPoint(30,30));
    label7->Show(false);

    //set up dialogs
    OpenDialog = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
                                "Images files (*.bmp;)|*.bmp;",wxFD_OPEN, wxDefaultPosition);

    OpenDialog2 = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString,
                                "",wxFD_OPEN, wxDefaultPosition);

    SaveDialog = new wxFileDialog(this, _("Save file"), "", "",
                       "Images files (*.bmp;)|*.bmp;", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);



}


CryptologyFrame::~CryptologyFrame()
{
}

void CryptologyFrame::TextToBinary(string s)
{
  string s1;
	string arr;
	int toint;

	for(unsigned int i=0;i<s.size();i++)
	{
     bitset<8>(r);
		 r=bitset<8>(s.c_str()[i]);
		 s1=r.to_string();

		 for(unsigned int j=0;j<s1.length();j++)
		 {
		 	 arr=s1[j];
		 	 stringstream geek(arr);
       geek>>toint;
       a.push_back(toint);
		 }
   }
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
        //user selects a bitmap file and hits ok
        if(OpenDialog->ShowModal() == wxID_OK)
        {
            txtDecode->SetValue(OpenDialog->GetPath());

        }
    }

}

//Use least significant bit algorithm to hide objects into images
void CryptologyFrame::LeastSignificantBit(wxCommandEvent &event)
{
   if(state == 'A')
   {
      if(txtMessage->IsEmpty() && txtFile2->IsEmpty())
      {
         wxMessageBox("Need Cover Image and Secret Message","Message");
      }
      else if(txtMessage->IsEmpty())
      {
          wxMessageBox("Need a secret message to start the embedding process", "Message");
      }
      else if(txtFile2->IsEmpty())
      {
          wxMessageBox("Need Cover Image to hide secret message","Message");
      }
      else
      {
         EncodeTexttoImage();
      }
   }
   else if(state == 'B')
   {
      if(txtFile->IsEmpty() && txtFile2->IsEmpty())
      {
          wxMessageBox("Need Cover Image and Hidden Image to Encrypt","Message");
      }
      else if(txtFile2->IsEmpty())
      {
          wxMessageBox("Need Cover Image to Encrypt","Message");
      }
      else if(txtFile->IsEmpty())
      {
          wxMessageBox("Need Hidden Image to Encrypt","Message");
      }
      else
      {
         EncodeImagetoImage();
      }

   }
   else if(state == 'C')
   {
       //Ibrahim's file encrypt
      if(txtFile->IsEmpty() && txtFile2->IsEmpty())
      {
          wxMessageBox("Need Cover Image and File to Encrypt","Message");
      }
      else if(txtFile2->IsEmpty())
      {
          wxMessageBox("Need Cover Image to Encrypt","Message");
      }
      else if(txtFile->IsEmpty())
      {
          wxMessageBox("Need File to Encrypt","Message");
      }
      else
      {
         EncodeFiletoImage();
      }
   }
   else
   {
       if(txtDecode->IsEmpty())
       {
           wxMessageBox("Need an image to decrypt","Message");
       }
       else
       {
           DecodeImage();
       }
   }

}

void CryptologyFrame::EncodeTexttoImage()
{

  isRightSize = false;
  change_bits_per_pixel = 3;
  total_bits_per_pixel = 8;
  bit_index = 0;
  start_hiding_pixel_data = false;
  unsigned char new_pixel_color[] = {0,0,0};
  counter =0;
  bool once = false;
  total_bit_size = "";

  //get message
  wxString message = txtMessage->GetValue();

  //get cover image
  CImg<unsigned char> image(txtFile2->GetValue());

  width = image.width();
  height = image.height();

  //find total amount of pixels from each picture
  cover_image_max_pixels = height * width;

  //find max amount of characters to hide in cover image
  max_letters_to_hide = floor((cover_image_max_pixels*change_bits_per_pixel)/total_bits_per_pixel) - 6;


  //the message is too large
  if(message.length() > max_letters_to_hide)
  {
    char buffer[20];
    string maxed = itoa(max_letters_to_hide,buffer,10);
    wxMessageBox("You can only hide up to" + maxed + " characters.","Error");
  }
  else
  {
    //find binary value of cover_image width and height
    total_bits_cover_image_width = (bitset<11>)width;
    total_bits_cover_image_height = (bitset<11>)height;
    letter = (bitset<8>)'x';
    charSize = (bitset<16>)message.length();

    total_bit_size = "01";
    total_bit_size += total_bits_cover_image_width.to_string();
    total_bit_size += letter.to_string();
    total_bit_size += total_bits_cover_image_height.to_string();
    total_bit_size += charSize.to_string();

    //put it into vector
    for(unsigned int i = 0; i < total_bit_size.length();i++)
    {
       if(total_bit_size[i] == '1')
       {
          a.push_back(1);
       }
       else
       {
         a.push_back(0);
       }

    }
    //convert message to binary
    TextToBinary(message.ToStdString());

    //go through the pixel data
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            if (counter<a.size()-1)
            {
                for(int c=0;c<3;c++)
                {

                    color_value=(int)(image(x,y,0,c));
                    b=(bitset<8>)color_value;

                    if(!once)
                    {
                       b[1] = a[counter];
                       b[0] = a[counter+1];

                       counter+=2;
                       once = true;
                       red = b;
                    }
                    else
                    {
                      if(c==0)
                      {
                          b[0]=a[counter];
                          red=b;
                          counter ++;

                      }
                      if(c==1)
                      {
                          b[0]=a[counter];
                          green =b;
                          counter++;

                      }
                      if(c==2)
                      {
                          b[0]=a[counter];
                          blue = b;
                          counter ++;
                      }
                    }


                  }//inner loop

                  cout<<endl;
                  color_value = (int)red.to_ulong();
                  new_pixel_color[0] = (unsigned char)color_value;

                  color_value = (int)green.to_ulong();
                  new_pixel_color[1] = (unsigned char)color_value;

                  color_value = (int)blue.to_ulong();
                  new_pixel_color[2] = (unsigned char)color_value;
                  image.draw_point(x,y,new_pixel_color);

              }// if statement

        } //middle loop

    }//end of outer loop

     //user needs to save first
    if(SaveDialog->ShowModal() == wxID_OK)
    {
       image.save(SaveDialog->GetPath());
       wxMessageBox("Stego Image Is Ready", "Message");
    }

    txtMessage->Clear();
    txtFile2->Clear();
  }


}

//Use least significant bit algorithm to hide encode images into images
void CryptologyFrame::EncodeImagetoImage()
{
    isRightSize = false;
    change_bits_per_pixel = 6;
    total_bits_per_pixel = 24;
    current_x = 0;
    current_y = 0;
    current_channel = 0;
    bit_index = 0;
    start_hiding_pixel_data = false;
    unsigned char new_pixel_color[] = {0,0,0};
    bool once = false;
    total_bit_size = "";

        //get image to hide
    CImg<unsigned char> hide_image(txtFile->GetValue());

    //get cover image
    CImg<unsigned char> cover_image(txtFile2->GetValue());

    //find total amount of pixels from each picture
    cover_image_max_pixels = cover_image.height() * cover_image.width();
    hide_image_max_pixels = hide_image.height() * hide_image.width();

    //find max amount of pixels to hide in cover image
    max_pixels_to_hide = floor((cover_image_max_pixels*change_bits_per_pixel)/total_bits_per_pixel);

    //1 pixel of data will be used for size and other data.
    max_pixels_to_hide = max_pixels_to_hide-3;

    //make sure that image is small enough
    while(!isRightSize)
    {
      //do not have enough pixels to hide image
      if(hide_image_max_pixels > max_pixels_to_hide)
      {
        if(!once)
        {
            wxMessageBox("Cover image is too small. Resizing hidden image to fit", "Message");
            once = true;
        }

        hide_image.resize_halfXY();
        hide_image_max_pixels = hide_image.height() * hide_image.width();
      }
      else
      {
        isRightSize = true;
      }
    }

    //find binary value of hide_image width and height
    total_bits_image_width = (bitset<11>)hide_image.width();
    total_bits_image_height = (bitset<11>)hide_image.height();

    //find binary value of cover_image width and height
    total_bits_cover_image_width = (bitset<11>)cover_image.width();
    total_bits_cover_image_height = (bitset<11>)cover_image.height();

    letter = (bitset<8>)'x';

    total_bit_size = "10";
    total_bit_size += total_bits_cover_image_width.to_string();
    total_bit_size += letter.to_string();
    total_bit_size += total_bits_cover_image_height.to_string();
    total_bit_size += total_bits_image_width.to_string();
    total_bit_size += total_bits_image_height.to_string();

    //get current red value of image to hide
    bitset<8> colors((int)hide_image(current_x,current_y,0,current_channel));
    color = colors.to_string();

    current_channel++;

    //go through the pixel data of the cover image
    for(int y = 0;y < cover_image.height();y++)
    {
      for(int x = 0;x<cover_image.width();x++)
      {
        for(int c = 0; c< 3; c++)
        {
          //get color value
          color_value = (int)cover_image(x,y,0,c);

          //get binary value of color
          cover_color = (bitset<8>)color_value;

          //hide size data first
          if(!start_hiding_pixel_data)
          {
                if(bit_index < 54)
                {
                    if(total_bit_size[bit_index] == '1')
                    {
                        cover_color[1] = 1;
                    }
                    else
                    {
                        cover_color[1] = 0;
                    }

                    if(total_bit_size[bit_index+1] == '1')
                    {
                        cover_color[0] = 1;
                    }
                    else
                    {
                        cover_color[0] = 0;
                    }
                }

                bit_index+=2;

                //the color red
                if(c == 0)
                {
                    red = cover_color;
                }
                else if(c == 1)
                {
                    green = cover_color;
                }
                else
                {
                    blue = cover_color;
                }

                //this is the last bit of size data
                if(bit_index == 72)
                {
                    bit_index=0;
                    start_hiding_pixel_data = true;
                }
            }
            else
            {
                //change the two least significant bits of color
                if(color[bit_index] == '1')
                {
                    cover_color[1] = 1;
                }
                else
                {
                    cover_color[1] = 0;
                }

                if(color[bit_index+1] == '1')
                {
                    cover_color[0] = 1;
                }
                else
                {
                    cover_color[0] = 0;
                }

                //the color red
                if(c == 0)
                {
                    red = cover_color;
                }
                else if(c == 1)
                {
                    green = cover_color;
                }
                else
                {
                    blue = cover_color;
                }


                bit_index += 2;

                //need to go to next channel of hidden image
                if(bit_index == 8)
                {
                    //reset current channel
                    if(current_channel == 3)
                    {
                        current_channel = 0;

                        //go to next pixel
                        current_x++;

                        //go to next row of pixels
                        if(current_x>hide_image.width()-1)
                        {
                            current_x=0;
                            current_y++;
                        }
                    }

                    //there are no more pixels to hide
                    if(current_y > hide_image.height()-1)
                    {
                        break;
                    }

                    color_value = (int)hide_image(current_x,current_y,0,current_channel);
                    colors = (bitset<8>)color_value;

                    color = colors.to_string();

                    current_channel++;
                    bit_index = 0;
                }
            }


        }

        //get the values of the new colors
        color_value = (int)red.to_ulong();
        new_pixel_color[0] = (unsigned char)color_value;

        color_value = (int)green.to_ulong();
        new_pixel_color[1] = (unsigned char)color_value;

        color_value = (int)blue.to_ulong();
        new_pixel_color[2] = (unsigned char)color_value;

        //change pixel of color_image
        cover_image.draw_point(x,y,new_pixel_color);

        //no more pixels to hide
        if(current_y > hide_image.height()-1)
        {
            break;
        }

    }

    //no more pixels to hide
    if(current_y > hide_image.height()-1)
    {
        break;
    }

  }

   //user needs to save first
  if(SaveDialog->ShowModal() == wxID_OK)
  {
     cover_image.save(SaveDialog->GetPath());
     wxMessageBox("Stego Image Is Ready", "Message");
  }

  txtFile->Clear();
  txtFile2->Clear();

}

void CryptologyFrame::EncodeFiletoImage()
{

}

void CryptologyFrame::DecodeImage()
{
  current_x = 0;
  current_y = 0;
  current_channel = 0;
  color = "";
  codes.set(0,false);
  codes.set(1,false);
  bit_index=0;
  start_finding_pixel_data = false;
  keepGoing = true;
  unsigned char new_pixel_color[] = {0,0,0};
  bool isFinished = false;
  bool once = false;
  total_bit_size = "";
  string message = "";
  string bitMessage = "";
  total_bit_size = "";
  bitset<1> b;

  //open the image
  CImg<unsigned char> stego_image(txtDecode->GetValue());

  //make new image
  CImg<unsigned char> new_image(800,800,1,3,0);

  //go through the pixel data of the stego image
  for(int y = 0;y < stego_image.height();y++)
  {
      for(int x = 0;x<stego_image.width();x++)
      {


            for(int c = 0; c< 3; c++)
            {
                //get color value
                color_value = (int)stego_image(x,y,0,c);

                //get binary value of color
                cover_color = (bitset<8>)color_value;


                //hide size data first
                if(!start_finding_pixel_data)
                {

                    if(!once)
                    {
                      //get first 2 bits of color
                      bit_data[1] = cover_color[1];
                      bit_data[0] = cover_color[0];

                      total_bit_size += bit_data.to_string();

                      bit_index+=2;
                      once = true;
                    }



                    //text to image code
                    if(codes.to_string() == "01")
                    {
                        b[0] = cover_color[0];

                        total_bit_size += b.to_string();

                        bit_index++;

                        if(bit_index == 48)
                        {
                            //find total size of cover image
                           total_bits_cover_image_width = (bitset<11>)total_bit_size.substr(2,13);
                           stego_image_width = (int)total_bits_cover_image_width.to_ulong();

                           //get letter in middle of size
                           letter = (bitset<8>)total_bit_size.substr(13,21);
                           int val = (int)letter.to_ulong();
                           char l = (char)val;

                           total_bits_cover_image_height = (bitset<11>)total_bit_size.substr(21,32);
                           stego_image_height = (int)total_bits_cover_image_height.to_ulong();

                           //this image is not been encoded
                           if(stego_image_width != stego_image.width() || stego_image_height != stego_image.height() || l != 'x')
                           {
                              keepGoing = false;
                              wxMessageBox("There is no decoded image","Message");
                              break;
                           }

                            charSize = (bitset<16>)total_bit_size.substr(32,48);
                            counter = (unsigned int)charSize.to_ulong();
                            start_finding_pixel_data = true;
                            bit_index = 0;

                        }

                    }
                    else if(codes.to_string() == "10") //image to image code
                    {
                        //get first 2 bits of color
                        bit_data[1] = cover_color[1];
                        bit_data[0] = cover_color[0];

                        total_bit_size += bit_data.to_string();

                        bit_index+=2;

                        //image to image requires 24 more bits
                        if(bit_index == 72)
                        {
                            //find total size of cover image
                            total_bits_cover_image_width = (bitset<11>)total_bit_size.substr(2,13);
                            stego_image_width = (int)total_bits_cover_image_width.to_ulong();

                            //get letter in middle of size
                            letter = (bitset<8>)total_bit_size.substr(13,21);
                            int val = (int)letter.to_ulong();
                            char l = (char)val;

                            total_bits_cover_image_height = (bitset<11>)total_bit_size.substr(21,32);
                            stego_image_height = (int)total_bits_cover_image_height.to_ulong();

                            //this image is not been encoded
                            if(stego_image_width != stego_image.width() || stego_image_height != stego_image.height() || l != 'x')
                            {
                               keepGoing = false;
                               wxMessageBox("There is no decoded image","Message");
                               break;
                            }

                            total_bits_image_width = (bitset<11>)total_bit_size.substr(32,43);
                            hidden_image_width = (int)total_bits_image_width.to_ulong();

                            total_bits_image_height = (bitset<11>)total_bit_size.substr(43,54);
                            hidden_image_height = (int)total_bits_image_height.to_ulong();


                            new_image.resize(hidden_image_width,hidden_image_height);
                            start_finding_pixel_data = true;
                            bit_index = 0;
                        }
                    }
                    else if(codes.to_string() == "11")  //file to image code
                    {
                        if(bit_index == 32)
                        {
                            //find total size of cover image
                           total_bits_cover_image_width = (bitset<11>)total_bit_size.substr(2,13);
                           stego_image_width = (int)total_bits_cover_image_width.to_ulong();

                           //get letter in middle of size
                           letter = (bitset<8>)total_bit_size.substr(13,21);
                           int val = (int)letter.to_ulong();
                           char l = (char)val;

                           total_bits_cover_image_height = (bitset<11>)total_bit_size.substr(21,32);
                           stego_image_height = (int)total_bits_cover_image_height.to_ulong();

                           //this image is not been encoded
                           if(stego_image_width != stego_image.width() || stego_image_height != stego_image.height() || l != 'x')
                           {
                              keepGoing = false;
                              wxMessageBox("There is no decoded image","Message");
                              break;
                           }

                        }
                    }
                    else //have not received the number code yet
                    {
                        codes = (bitset<2>)total_bit_size;

                    }
                }
                else
                {
                    if(codes.to_string() == "01")
                    {
                        b[0] = cover_color[0];

                        bitMessage += b.to_string();

                        bit_index++;

                        if(bit_index == 8)
                        {

                           //take 8 bits into a character
                          letter = (bitset<8>)bitMessage;

                          //add character to message
                          message += (char)letter.to_ulong();

                          bit_index = 0;
                          bitMessage = "";
                          counter--;
                        }


                        if(counter == 0)
                        {
                            keepGoing = false;
                            isFinished = true;
                            break;
                        }
                    }

                    if(codes.to_string() == "10")
                    {
                        //get first 2 bits of color
                        bit_data[1] = cover_color[1];
                        bit_data[0] = cover_color[0];

                        color += bit_data.to_string();

                        bit_index+=2;

                        if(bit_index == 8)
                        {
                            if(current_channel == 0)
                            {
                                red = (bitset<8>)color;
                            }
                            else if(current_channel == 1)
                            {
                                green = (bitset<8>)color;
                            }
                            else
                            {
                                blue = (bitset<8>)color;
                            }

                            current_channel++;

                            bit_index = 0;
                            color = "";
                        }

                        if(current_channel == 3)
                        {
                            current_channel = 0;

                            //get the values of the new colors
                            color_value = (int)red.to_ulong();
                            new_pixel_color[0] = (unsigned char)color_value;

                            color_value = (int)green.to_ulong();
                            new_pixel_color[1] = (unsigned char)color_value;

                            color_value = (int)blue.to_ulong();
                            new_pixel_color[2] = (unsigned char)color_value;

                            //draw the pixel
                            new_image.draw_point(current_x,current_y, new_pixel_color);

                            current_x++;

                            //go to next row of pixels
                            if(current_x>hidden_image_width-1)
                            {
                                current_x=0;
                                current_y++;
                            }

                            if(current_y>hidden_image_height-1)
                            {
                                 keepGoing = false;
                                 isFinished = true;
                                 break;
                            }

                        }

                    }

                    if(codes.to_string() == "11")
                    {

                    }
                }

                //does not match
                if(codes.to_string() == "00")
                {
                   wxMessageBox("WHY!!!");
                   keepGoing = false;
                   break;
                }
            }

            //its done
            if(!keepGoing)
            {
                break;
            }

      }

    //this image is not decoded
    if(!keepGoing)
    {
        break;
    }


  }

  if(isFinished)
  {
      //user needs to save
      if(SaveDialog->ShowModal() == wxID_OK)
      {

        if(codes.to_string() == "01")
        {
           unsigned char colors[] = {255,255,255};

           new_image.draw_text(0,0,message.c_str(),colors,0,1,23);
           new_image.save(SaveDialog->GetPath());
           wxMessageBox("Text has been decoded", "Message");


        }
        else
        {
          new_image.save(SaveDialog->GetPath());
          wxMessageBox("Image has been decoded", "Message");
        }


      }
  }

  new_image.display();
  txtDecode->Clear();
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
