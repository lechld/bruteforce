//
// Created by Dominik Lechl on 23.01.25.
//

#include "PasswordInputCtrl.h"

PasswordInputCtrl::PasswordInputCtrl(wxWindow* parent, const wxString& targetPassword, wxWindowID id,
                                     const wxPoint& pos, const wxSize& size, long style)
    : wxRichTextCtrl(parent, id, "", pos, size, style | wxTE_NO_VSCROLL), targetPassword(targetPassword) {

    SetVirtualSize(wxSize(400, -1));
    ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_NEVER);

    Bind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);
}

void PasswordInputCtrl::SetTargetPassword(const wxString& password) {
    targetPassword = password;
}

const wxString& PasswordInputCtrl::GetTargetPassword() const {
    return targetPassword;
}

void PasswordInputCtrl::OnTextChange(wxCommandEvent& event) {
    HighlightInput();
    event.Skip();
}

void PasswordInputCtrl::HighlightInput() {
    wxString userInput = GetValue();

    Freeze(); // don't draw before we are finished
    Unbind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);
    Clear();

    for (size_t i = 0; i < userInput.Length(); ++i) {
        wxString currentChar = userInput.Mid(i, 1);

        wxTextAttr style;
        if (i < targetPassword.Length() && currentChar == targetPassword.Mid(i, 1)) {
            style.SetTextColour(*wxBLACK);
            style.SetBackgroundColour(*wxGREEN);
        } else {
            style.SetTextColour(*wxWHITE);
            style.SetBackgroundColour(*wxRED);
        }

        BeginStyle(style);
        WriteText(currentChar);
        EndStyle();
    }

    Thaw(); // draw that shit
    Bind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);
}

