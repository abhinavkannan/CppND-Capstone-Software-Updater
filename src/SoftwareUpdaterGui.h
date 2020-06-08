#ifndef SOFTWARE_UPDATER_GUI_H_
#define SOFTWARE_UPDATER_GUI_H_

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/log.h>
#include "SoftwareUpdater.h"

class SoftwareUpdaterMainFrame;

constexpr auto SOFTWARE_UPDATER_VERSION_STRING = "1.0";

enum
{
  SOFTWARE_UPDATER_MAIN_FRAME_EXIT = wxID_EXIT,
  SOFTWARE_UPDATER_MAIN_FRAME_REFRESH = 10,
  SOFTWARE_UPDATER_MAIN_FRAME_ABOUT = 20,
  LOGIN_MAIN_PANEL = 30,
  LOGIN_PANEL_USERNAME = 40,
  LOGIN_PANEL_OK_BUTTON = 50,
  LOGIN_PANEL_QUIT_BUTTON = 60,
  SOFTWARE_VIEW_MAIN_PANEL = 70,
  SOFTWARE_VIEW_PANEL_NOTEBOOK = 80,
  SOFTWARE_VIEW_PANEL_AVAIL_LIST = 90,
  SOFTWARE_VIEW_PANEL_INSTALLED_LIST = 100
};

constexpr auto SOFTWARE_VIEW_PANEL_AVAIL_LIST_TAG = "Available Software";
constexpr auto SOFTWARE_VIEW_PANEL_INSTALLED_LIST_TAG = "Installed Software";
constexpr auto SOFTWARE_VIEW_PANEL_LIST_COL_NAME = "Name";
constexpr auto SOFTWARE_VIEW_PANEL_LIST_COL_VERSION = "Version";
constexpr auto SOFTWARE_VIEW_PANEL_LIST_COL_DATE = "Date";

enum
{
  COLUMN_0,
  COLUMN_1,
  COLUMN_2
};

class LoginPanel : public wxPanel
{
public:
  LoginPanel(wxWindow *parent);
  ~LoginPanel();

  void OnEnter(wxCommandEvent &event);
  void OnButtonClicked(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  wxString GetUsername() { return _usernameString; }

private:
  wxStaticText *_usernameLabelText;
  wxTextCtrl   *_usernameTextCtrl;
  wxBoxSizer   *_usernameSizer;
  wxButton     *_usernameOkButton;
  wxButton     *_usernameQuitButton;
  wxBoxSizer   *_buttonSizer;
  wxBoxSizer   *_loginPanelSizer;
  wxString     _usernameString;

  wxDECLARE_EVENT_TABLE();
};

class SoftwareViewPanel : public wxPanel
{
public:
  SoftwareViewPanel(wxWindow *parent, std::shared_ptr<SoftwareUpdater> softwareUpdater);
  ~SoftwareViewPanel();

  // Event handler for list box item click
  void OnListCtrlItemClick(wxListEvent &event);
  void OnSoftwareViewPageChanged(wxBookCtrlEvent& event);

private:
  wxNotebook *_notebook;
  wxListCtrl *_availListCtrl;
  wxListCtrl *_installedListCtrl;
  wxBoxSizer *_notebookSizer;

  std::weak_ptr<SoftwareUpdater> _softwareUpdater;

  wxDECLARE_EVENT_TABLE();
};

// Main UI wxWidget frame
class SoftwareUpdaterMainFrame : public wxFrame
{
public:
  SoftwareUpdaterMainFrame(const wxString &title);
  ~SoftwareUpdaterMainFrame();

  void LoadSoftwareView(wxString &newTitle);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnRefresh(wxCommandEvent &event);

private:
  wxMenuBar         *_menuBar;
  wxMenu            *_menu;
  wxBoxSizer        *_sizer;
  LoginPanel        *_loginPanel;
  SoftwareViewPanel *_softwareViewPanel;

  std::shared_ptr<SoftwareUpdater> _softwareUpdater;

  wxDECLARE_EVENT_TABLE();
};

class SoftwareUpdaterApp : public wxApp
{
public:
  virtual bool OnInit();

private:
  SoftwareUpdaterMainFrame *_softwareFrame;  
};

#endif /* SOFTWARE_UPDATER_GUI_H_ */