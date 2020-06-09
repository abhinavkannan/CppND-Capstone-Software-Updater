
#include <iostream>
#include <wx/activityindicator.h>
#include <wx/aboutdlg.h>
#include <wx/gauge.h>

#include "SoftwareUpdaterGui.h"

const int windowWidth = 600;
const int windowHeight = 600;

IMPLEMENT_APP(SoftwareUpdaterApp);

wxBEGIN_EVENT_TABLE(SoftwareUpdaterMainFrame, wxFrame)
  EVT_MENU(SOFTWARE_UPDATER_MAIN_FRAME_EXIT, SoftwareUpdaterMainFrame::OnExit)
  EVT_MENU(SOFTWARE_UPDATER_MAIN_FRAME_ABOUT, SoftwareUpdaterMainFrame::OnAbout)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(LoginPanel, wxPanel)
  EVT_TEXT_ENTER(LOGIN_PANEL_USERNAME, LoginPanel::OnEnter)
  EVT_BUTTON(LOGIN_PANEL_OK_BUTTON, LoginPanel::OnButtonClicked)
  EVT_BUTTON(LOGIN_PANEL_QUIT_BUTTON, LoginPanel::OnExit)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(SoftwareViewPanel, wxPanel)
  EVT_LIST_ITEM_SELECTED(SOFTWARE_VIEW_PANEL_AVAIL_LIST, SoftwareViewPanel::OnListCtrlItemClick)
  EVT_LIST_ITEM_SELECTED(SOFTWARE_VIEW_PANEL_INSTALLED_LIST, SoftwareViewPanel::OnListCtrlItemClick)
  EVT_NOTEBOOK_PAGE_CHANGED(SOFTWARE_VIEW_PANEL_NOTEBOOK, SoftwareViewPanel::OnSoftwareViewPageChanged)
wxEND_EVENT_TABLE()

void LoginPanel::OnEnter(wxCommandEvent &event)
{
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
  _usernameTextCtrl = new wxTextCtrl(this, LOGIN_PANEL_USERNAME,
	wxEmptyString, wxDefaultPosition, wxDefaultSize,
	wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);

  // Combine the label and edit box into a Sizer
  _usernameSizer = new wxBoxSizer(wxHORIZONTAL);
  _usernameSizer->Add(_usernameLabelText, 0, wxFIXED_MINSIZE | wxALL, 0);
  _usernameSizer->AddSpacer(10);
  _usernameSizer->Add(_usernameTextCtrl, 1, wxFIXED_MINSIZE | wxALL, 0);

  // OK button
  _usernameOkButton = new wxButton(this, LOGIN_PANEL_OK_BUTTON, "OK",
	wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
  
  // Cancel button
  _usernameQuitButton = new wxButton(this, LOGIN_PANEL_QUIT_BUTTON, "Quit",
	wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);

  _buttonSizer = new wxBoxSizer(wxHORIZONTAL);
  _buttonSizer->Add(_usernameOkButton, 0, wxFIXED_MINSIZE | wxALL, 0);
  _buttonSizer->AddSpacer(10);
  _buttonSizer->Add(_usernameQuitButton, 0, wxFIXED_MINSIZE | wxALL, 0);

  _loginPanelSizer = new wxBoxSizer(wxVERTICAL);
  _loginPanelSizer->Add(_usernameSizer, 0, wxEXPAND | wxALL, 0);
  _loginPanelSizer->AddSpacer(10);
  _loginPanelSizer->Add(_buttonSizer, 0, wxEXPAND | wxALL, 0);
  SetSizer(_loginPanelSizer);
}

LoginPanel::~LoginPanel()
{
  delete _usernameOkButton;
  delete _usernameQuitButton;
  delete _usernameLabelText;
  delete _usernameTextCtrl;
}

SoftwareViewPanel::SoftwareViewPanel(wxWindow *parent, std::shared_ptr<SoftwareUpdater> softwareUpdater)
  : wxPanel(parent, SOFTWARE_VIEW_MAIN_PANEL, wxDefaultPosition, wxSize(200, 200), 0, wxPanelNameStr)
{
  _softwareUpdater = softwareUpdater;
  std::vector<Software> availList;
  std::vector<Software> installedList;
  long itemIndex = -1;

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
	wxMessageDialog *errDial = new wxMessageDialog(NULL, std::string("SoftwareUpdater reference invalid!"),
	  std::string(e.what()), wxOK);
	errDial->ShowModal();

	this->GetParent()->Close();
  }

  _notebook = (wxNotebook*)NULL;
  _availListCtrl = (wxListCtrl*)NULL;
  _installedListCtrl = (wxListCtrl*)NULL;
  _notebookSizer = (wxBoxSizer*)NULL;

  _notebook = new wxNotebook(this, SOFTWARE_VIEW_PANEL_NOTEBOOK);

  _availListCtrl = new wxListCtrl(_notebook, SOFTWARE_VIEW_PANEL_AVAIL_LIST,
	wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
  _installedListCtrl = new wxListCtrl(_notebook, SOFTWARE_VIEW_PANEL_INSTALLED_LIST,
	wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

  // Name column
  wxListItem column;
  column.SetText(SOFTWARE_VIEW_PANEL_LIST_COL_NAME);
  column.SetWidth(200);
  _availListCtrl->InsertColumn(COLUMN_0, column);
  _installedListCtrl->InsertColumn(COLUMN_0, column);

  // Version column
  column.SetText(SOFTWARE_VIEW_PANEL_LIST_COL_VERSION);
  _availListCtrl->InsertColumn(COLUMN_1, column);
  _installedListCtrl->InsertColumn(COLUMN_1, column);

  // Date column
  column.SetText(SOFTWARE_VIEW_PANEL_LIST_COL_DATE);
  _availListCtrl->InsertColumn(COLUMN_2, column);
  _installedListCtrl->InsertColumn(COLUMN_2, column);

  for (std::size_t i = 0; i < availList.size(); i++)
  {
	// With wxListCtrl if we need to install data per column the first
	// insert needs to be via InsertItem to get the index and subsequently
	// we can use SetItem with the previously obtained index to insert
	// the remaining items
	itemIndex = _availListCtrl->InsertItem(COLUMN_0, availList[i].GetName());
	_availListCtrl->SetItem(itemIndex, COLUMN_1, availList[i].GetVersion());
	_availListCtrl->SetItem(itemIndex, COLUMN_2, availList[i].GetDate());
  }

  for (std::size_t i = 0; i < installedList.size(); i++)
  {
	itemIndex = _installedListCtrl->InsertItem(COLUMN_0, availList[i].GetName());
	_installedListCtrl->SetItem(itemIndex, COLUMN_1, installedList[i].GetVersion());
	_installedListCtrl->SetItem(itemIndex, COLUMN_2, installedList[i].GetDate());
  }

  _notebook->AddPage(_availListCtrl, SOFTWARE_VIEW_PANEL_AVAIL_LIST_TAG);
  _notebook->AddPage(_installedListCtrl, SOFTWARE_VIEW_PANEL_INSTALLED_LIST_TAG);

  _notebookSizer = new wxBoxSizer(wxHORIZONTAL);
  _notebookSizer->Add(_notebook, 0, wxEXPAND | wxALL, 0);
  SetSizer(_notebookSizer);
}

SoftwareViewPanel::~SoftwareViewPanel()
{
  delete _availListCtrl;
  delete _installedListCtrl;
  delete _notebook;
}

void SoftwareViewPanel::OnListCtrlItemClick(wxListEvent &event)
{
  // Get the ID of the control structure to distinguish between the two list controls
  wxListCtrl *listCtrl = wxDynamicCast(event.GetEventObject(), wxListCtrl);
  wxNotebook *notebook = wxDynamicCast(listCtrl->GetParent(), wxNotebook);
  long listItemIndex = event.GetIndex();
  long windowId = listCtrl->GetId();
  wxGauge gauge(this, wxID_ANY, 100, wxPoint(200, 200), wxSize(100, 20));

  switch (windowId)
  {
  case SOFTWARE_VIEW_PANEL_AVAIL_LIST:
	if (!_softwareUpdater.expired())
	{
	  gauge.SetValue(0);
	  gauge.Show(true);

	  auto installSwRes = std::async(std::launch::deferred, &SoftwareUpdater::InstallSofware,
		_softwareUpdater.lock(), listItemIndex);
	  installSwRes.wait();
	  
	  // Simulate software installation via a gauge
	  for (int i = 25; i <= 100; i += 25)
	  {
		gauge.SetValue(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	  }
	  gauge.Show(false);
	  
	  listCtrl->DeleteItem(listItemIndex);
	}
	break;

  case SOFTWARE_VIEW_PANEL_INSTALLED_LIST:
	if (!_softwareUpdater.expired())
	{
	  gauge.SetValue(0);
	  gauge.Show(true);

	  auto removeSwRes = std::async(std::launch::deferred, &SoftwareUpdater::RemoveSoftware,
		_softwareUpdater.lock(), listItemIndex);
	  removeSwRes.wait();
	  
	  for (int i = 25; i <= 100; i += 25)
	  {
		gauge.SetValue(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	  }
	  gauge.Show(false);
	  
	  listCtrl->DeleteItem(listItemIndex);
	}

	break;

  default:
	break;
  }
}

void SoftwareViewPanel::OnSoftwareViewPageChanged(wxBookCtrlEvent& event)
{
  int notebookPage = event.GetSelection();
  long itemIndex = -1;

  switch (notebookPage)
  {
  case 0:
	{
	  if (!_softwareUpdater.expired())
	  {
		auto availList = _softwareUpdater.lock()->GetAvailSwList();
		_availListCtrl->DeleteAllItems();

		for (std::size_t i = 0; i < availList.size(); i++)
		{
		  itemIndex = _availListCtrl->InsertItem(COLUMN_0, availList[i].GetName());
		  _availListCtrl->SetItem(itemIndex, COLUMN_1, availList[i].GetVersion());
		  _availListCtrl->SetItem(itemIndex, COLUMN_2, availList[i].GetDate());
		}
	  }
	}

	break;

  case 1:
	{
	  if (!_softwareUpdater.expired())
	  {
		auto installedList = _softwareUpdater.lock()->GetInstalledSwList();
		_installedListCtrl->DeleteAllItems();

		for (std::size_t i = 0; i < installedList.size(); i++)
		{
		  itemIndex = _installedListCtrl->InsertItem(COLUMN_0, installedList[i].GetName());
		  _installedListCtrl->SetItem(itemIndex, COLUMN_1, installedList[i].GetVersion());
		  _installedListCtrl->SetItem(itemIndex, COLUMN_2, installedList[i].GetDate());
		}
	  }
	}
	break;

  default:
	break;
  }

  _notebook->Layout();
}

SoftwareUpdaterMainFrame::SoftwareUpdaterMainFrame(const wxString &title)
  : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(windowWidth, windowHeight))
{
  _softwareUpdater = std::make_shared<SoftwareUpdater>();

  _menuBar = (wxMenuBar*)NULL;
  _menu = (wxMenu*)NULL;

  _menu = new wxMenu;
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

void SoftwareUpdaterMainFrame::OnExit(wxCommandEvent &event)
{
  Close(true);
}

void SoftwareUpdaterMainFrame::OnAbout(wxCommandEvent &event)
{
  wxAboutDialogInfo aboutInfo;
  aboutInfo.SetName("Software Updater");
  aboutInfo.SetVersion(SOFTWARE_UPDATER_VERSION_STRING);
  aboutInfo.SetDescription(_("CppND-Final-Project"));
  aboutInfo.SetCopyright("(C) 2020");
  wxAboutBox(aboutInfo);
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