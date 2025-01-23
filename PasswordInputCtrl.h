//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef PASSWORDINPUTCTRL_H
#define PASSWORDINPUTCTRL_H

#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>

wxDECLARE_EVENT(EVT_PASSWORD_CORRECT, wxCommandEvent);

class PasswordInputCtrl : public wxRichTextCtrl {
public:
    PasswordInputCtrl(wxWindow* parent, const wxString& targetPassword, wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                      long style = 0);

    void SetTargetPassword(const wxString& password);

    const wxString& GetTargetPassword() const;

private:
    wxString targetPassword;

    void OnTextChange(wxCommandEvent& event);
    void HighlightInput();
    void OnChar(wxKeyEvent& event);
};

#endif //PASSWORDINPUTCTRL_H
