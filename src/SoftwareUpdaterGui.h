#ifndef SOFTWARE_UPDATER_GUI_H_
#define SOFTWARE_UPDATER_GUI_H_

#include <wx/wx.h>

class SoftwareUpdaterFrame;

class LoginPanel : public wxPanel
{
public:
  LoginPanel(wxWindow *parent);

  void OnEnter(wxCommandEvent &event);
  void OnButtonClicked(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  wxString GetUsername() { return _usernameString; }

private:
  wxStaticText *_usernameLabelText;
  wxTextCtrl   *_usernameTextCtrl;
  wxButton     *_usernameOkButton;
  wxButton     *_usernameQuitButton;
  wxString     _usernameString;
};

class SoftwareUpdaterPanel : public wxPanel
{
public:

private:

};

// Main UI wxWidget frame
class SoftwareUpdaterFrame : public wxFrame
{
public:
  SoftwareUpdaterFrame(const wxString &title);
  void UpdateTitle(wxString &text);

private:
  LoginPanel *_panel;
};

class SoftwareUpdaterApp : public wxApp
{
public:
  virtual bool OnInit();

private:
  SoftwareUpdaterFrame *_softwareUpdaterFrame;
};

#endif /* SOFTWARE_UPDATER_GUI_H_ */