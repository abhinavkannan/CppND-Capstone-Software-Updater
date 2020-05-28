
#include <iostream>
#include "SoftwareUpdaterGui.h"

const int windowWidth = 600;
const int windowHeight = 600;

enum SoftwareUpdaterWidgetIDs
{
  USERNAME_TEXT_CTRL_ID = 1,
  USERNAME_OK_BUTTON_ID,
  USERNAME_QUIT_BUTTON_ID
};

IMPLEMENT_APP(SoftwareUpdaterApp);

void LoginPanel::OnEnter(wxCommandEvent &event)
{
  std::cout << __func__ << "(): " << std::endl;

  // Retrieve the text from the text box
  _usernameString = _usernameTextCtrl->GetLineText(0);
}

void LoginPanel::OnButtonClicked(wxCommandEvent &event)
{
  std::cout << __func__ << "(): " << std::endl;

  // Retrieve the text from the text box
  _usernameString = _usernameTextCtrl->GetLineText(0);
}

void LoginPanel::OnExit(wxCommandEvent &event)
{
  if (wxMessageBox( wxT("Are you sure to quit ?"), wxT("Confirm Quit"), wxICON_QUESTION | wxYES_NO ) == wxYES)
  {
	Destroy();
  }  
}

LoginPanel::LoginPanel(wxWindow *parent)
  : wxPanel(parent, wxID_ANY, wxPoint(150, 150), wxSize(200, 200), 0, wxPanelNameStr)
{
  // Create username panel components
  _usernameLabelText = new wxStaticText(this, wxID_ANY, "Enter Username",
	                                    wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE | wxBORDER_NONE);
  
  // Edit box to allow user to enter their username
  _usernameTextCtrl = new wxTextCtrl(this, SoftwareUpdaterWidgetIDs::USERNAME_TEXT_CTRL_ID, wxEmptyString,
	                                 wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
  Connect(SoftwareUpdaterWidgetIDs::USERNAME_TEXT_CTRL_ID, wxEVT_TEXT_ENTER, wxCommandEventHandler(LoginPanel::OnEnter));

  // Combine the label and edit box into a Sizer
  wxBoxSizer *boxSizerUsernameTextInput = new wxBoxSizer(wxHORIZONTAL);
  boxSizerUsernameTextInput->Add(_usernameLabelText, 0, wxFIXED_MINSIZE | wxALL, 0);
  boxSizerUsernameTextInput->AddSpacer(10);
  boxSizerUsernameTextInput->Add(_usernameTextCtrl, 1, wxFIXED_MINSIZE | wxALL, 0);

  // OK button
  _usernameOkButton = new wxButton(this, SoftwareUpdaterWidgetIDs::USERNAME_OK_BUTTON_ID, "OK",
	                               wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  Connect(SoftwareUpdaterWidgetIDs::USERNAME_OK_BUTTON_ID, wxEVT_BUTTON, wxCommandEventHandler(LoginPanel::OnButtonClicked));
  
  // Cancel button
  _usernameQuitButton = new wxButton(this, SoftwareUpdaterWidgetIDs::USERNAME_QUIT_BUTTON_ID, "Quit",
	                                   wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  Connect(SoftwareUpdaterWidgetIDs::USERNAME_QUIT_BUTTON_ID, wxEVT_BUTTON, wxCommandEventHandler(LoginPanel::OnExit));

  wxBoxSizer *boxSizerButtons = new wxBoxSizer(wxHORIZONTAL);
  boxSizerButtons->Add(_usernameOkButton, 0, wxFIXED_MINSIZE | wxALL, 0);
  boxSizerButtons->AddSpacer(10);
  boxSizerButtons->Add(_usernameQuitButton, 0, wxFIXED_MINSIZE | wxALL, 0);

  wxBoxSizer *boxSizerAll = new wxBoxSizer(wxVERTICAL);
  boxSizerAll->Add(boxSizerUsernameTextInput, 0, wxEXPAND | wxALL, 0);
  boxSizerAll->AddSpacer(10);
  boxSizerAll->Add(boxSizerButtons, 0, wxEXPAND | wxALL, 0);
  SetSizer(boxSizerAll);
}

SoftwareUpdaterFrame::SoftwareUpdaterFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(windowWidth, windowHeight))
{
  // Show username panel
  _panel = new LoginPanel(this);

  // Show next panel
}

void SoftwareUpdaterFrame::UpdateTitle(wxString &text)
{
  SetTitle(text);
}

bool SoftwareUpdaterApp::OnInit()
{
  _softwareUpdaterFrame = new SoftwareUpdaterFrame("Software Updater");
  _softwareUpdaterFrame->Show(true);
  return true;
}