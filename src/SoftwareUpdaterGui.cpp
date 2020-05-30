
#include <iostream>
#include "SoftwareUpdaterGui.h"

const int windowWidth = 600;
const int windowHeight = 600;

IMPLEMENT_APP(SoftwareUpdaterApp);

void LoginPanel::OnEnter(wxCommandEvent &event)
{
  std::cout << __func__ << "(): " << std::endl;

  // Retrieve the text from the text box
  _usernameString = _usernameTextCtrl->GetLineText(0);

  SoftwareUpdaterMainFrame *parent = wxDynamicCast(this->GetParent(), SoftwareUpdaterMainFrame);
  if (parent)
  {
	parent->LoadSoftwareView(_usernameString);
  }
}

void LoginPanel::OnButtonClicked(wxCommandEvent &event)
{
  std::cout << __func__ << "(): " << std::endl;

  // Retrieve the text from the text box
  _usernameString = _usernameTextCtrl->GetLineText(0);

  SoftwareUpdaterMainFrame *parent = wxDynamicCast(this->GetParent(), SoftwareUpdaterMainFrame);
  if (parent)
  {
	parent->LoadSoftwareView(_usernameString);
  }
}

void LoginPanel::OnExit(wxCommandEvent &event)
{
  if (wxMessageBox( wxT("Are you sure to quit ?"), wxT("Confirm Quit"), wxICON_QUESTION | wxYES_NO ) == wxYES)
  {
	SoftwareUpdaterMainFrame *parent = wxDynamicCast(this->GetParent(), SoftwareUpdaterMainFrame);
	if (parent)
	{
	  parent->Close(true);
	}
  }  
}

LoginPanel::LoginPanel(wxWindow *parent)
  : wxPanel(parent, LOGIN_PANEL_USERNAME, wxDefaultPosition, wxSize(200, 200), 0, wxPanelNameStr)
{
  // Create username panel components
  _usernameLabelText = new wxStaticText(this, wxID_ANY, "Enter Username",
	                                    wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE | wxBORDER_NONE);
  
  // Edit box to allow user to enter their username
  _usernameTextCtrl = new wxTextCtrl(this, LOGIN_PANEL_USERNAME, wxEmptyString,
	                                 wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
  Connect(LOGIN_PANEL_USERNAME, wxEVT_TEXT_ENTER, wxCommandEventHandler(LoginPanel::OnEnter));

  // Combine the label and edit box into a Sizer
  wxBoxSizer *boxSizerUsernameTextInput = new wxBoxSizer(wxHORIZONTAL);
  boxSizerUsernameTextInput->Add(_usernameLabelText, 0, wxFIXED_MINSIZE | wxALL, 0);
  boxSizerUsernameTextInput->AddSpacer(10);
  boxSizerUsernameTextInput->Add(_usernameTextCtrl, 1, wxFIXED_MINSIZE | wxALL, 0);

  // OK button
  _usernameOkButton = new wxButton(this, LOGIN_PANEL_OK_BUTTON, "OK",
	                               wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  Connect(LOGIN_PANEL_OK_BUTTON, wxEVT_BUTTON, wxCommandEventHandler(LoginPanel::OnButtonClicked));
  
  // Cancel button
  _usernameQuitButton = new wxButton(this, LOGIN_PANEL_QUIT_BUTTON, "Quit",
	                                   wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  Connect(LOGIN_PANEL_QUIT_BUTTON, wxEVT_BUTTON, wxCommandEventHandler(LoginPanel::OnExit));

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

SoftwareViewPanel::SoftwareViewPanel(wxWindow *parent, std::shared_ptr<SoftwareUpdater> softwareUpdater)
  : wxPanel(parent, SOFTWARE_VIEW_MAIN_PANEL, wxDefaultPosition, wxSize(200, 200), 0, wxPanelNameStr)
{
  _softwareUpdater = softwareUpdater;
  std::vector<Software> availList;
  std::vector<Software> installedList;

  try
  {
	if (!_softwareUpdater.expired())
	{
	  _softwareUpdater.lock()->InitSwList();
	  availList = _softwareUpdater.lock()->GetAvailSwList();
	  installedList = _softwareUpdater.lock()->GetInstalledSwList();
	}
  }
  catch (const std::system_error& e)
  {
	wxMessageDialog *dial = new wxMessageDialog(NULL, std::string(e.what()), std::string(e.code().message()), wxOK);
	dial->ShowModal();
  }
  catch (const std::bad_weak_ptr& e)
  {
	wxMessageDialog *errDial = new wxMessageDialog(NULL, std::string("SoftwareUpdater reference invalid!"), std::string(e.what()), wxOK);
	errDial->ShowModal();

	this->GetParent()->Close();
  }

  _notebook = (wxNotebook*)NULL;

  _notebook = new wxNotebook(this, SOFTWARE_VIEW_PANEL_NOTEBOOK);

  wxListCtrl *availListCtrl = new wxListCtrl(_notebook, SOFTWARE_VIEW_PANEL_AVAIL_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
  wxListCtrl *installedListCtrl = new wxListCtrl(_notebook, SOFTWARE_VIEW_PANEL_INSTALLED_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

  // First column
  wxListItem col0;
  col0.SetId(0);
  col0.SetText(wxT("Name"));
  col0.SetWidth(200);
  availListCtrl->InsertColumn(0, col0);
  installedListCtrl->InsertColumn(0, col0);

  // Second column
  wxListItem col1;
  col1.SetId(1);
  col1.SetText(wxT("Version"));
  col1.SetWidth(200);
  availListCtrl->InsertColumn(1, col1);
  installedListCtrl->InsertColumn(1, col1);

  // Third column
  wxListItem col2;
  col2.SetId(2);
  col2.SetText(wxT("Date"));
  col2.SetWidth(200);
  availListCtrl->InsertColumn(2, col2);
  installedListCtrl->InsertColumn(2, col2);

  for (std::size_t i = 0; i < availList.size(); i++)
  {
	long itemIndex = availListCtrl->InsertItem(0, availList[i].GetName());
	availListCtrl->SetItem(itemIndex, 1, availList[i].GetVersion());
	availListCtrl->SetItem(itemIndex, 2, availList[i].GetDate());
  }

  for (std::size_t i = 0; i < installedList.size(); i++)
  {
	installedListCtrl->SetItem(i, 0, installedList[i].GetName());
	installedListCtrl->SetItem(i, 1, installedList[i].GetVersion());
	installedListCtrl->SetItem(i, 2, installedList[i].GetDate());
  }

  _notebook->AddPage(availListCtrl, wxT("Available Softwares"));
  _notebook->AddPage(installedListCtrl, wxT("Installed Softwares"));

  wxBoxSizer *notebookSizer = new wxBoxSizer(wxHORIZONTAL);
  notebookSizer->Add(_notebook, 0, wxEXPAND | wxALL, 0);
  SetSizer(notebookSizer);
}

SoftwareUpdaterMainFrame::SoftwareUpdaterMainFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(windowWidth, windowHeight))
{
  _softwareUpdater = std::make_shared<SoftwareUpdater>();

  _menuBar = (wxMenuBar*)NULL;
  _menu = (wxMenu*)NULL;

  _menu = new wxMenu;
  _menu->Append(SOFTWARE_UPDATER_MAIN_FRAME_EXIT, wxT("&Refresh"));
  _menu->Append(SOFTWARE_UPDATER_MAIN_FRAME_ABOUT, wxT("&About"));
  _menu->AppendSeparator();
  _menu->Append(SOFTWARE_UPDATER_MAIN_FRAME_EXIT, wxT("&Exit"));

  _menuBar = new wxMenuBar;
  _menuBar->Append(_menu, wxT("&File"));
  SetMenuBar(_menuBar);

  _sizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(_sizer);

  // Show login panel
  _loginPanel = new LoginPanel(this);
  _sizer->Add(_loginPanel, 1, wxGROW);
}

void SoftwareUpdaterMainFrame::LoadSoftwareView(wxString &newTitle)
{
  _sizer->Detach(0);
  _loginPanel->Hide();
  
  // Update title
  SetTitle(this->GetTitle() + " ( " + newTitle + " )");

  // Load software view panel
  _softwareViewPanel = new SoftwareViewPanel(this, _softwareUpdater);
  _sizer->Prepend(_softwareViewPanel, 1, wxGROW);
  _sizer->Layout();

  _loginPanel->Destroy();
}

SoftwareUpdaterMainFrame::~SoftwareUpdaterMainFrame()
{

}

bool SoftwareUpdaterApp::OnInit()
{
  _softwareFrame = new SoftwareUpdaterMainFrame("Software Updater");
  _softwareFrame->Show(true);

  return true;
}