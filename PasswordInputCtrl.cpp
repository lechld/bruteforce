//
// Created by Dominik Lechl on 23.01.25.
//

#include "PasswordInputCtrl.h"

wxDEFINE_EVENT(EVT_PASSWORD_CORRECT, wxCommandEvent);

PasswordInputCtrl::PasswordInputCtrl(wxWindow *parent, const wxString &targetPassword, wxWindowID id,
                                     const wxPoint &pos, const wxSize &size, long style)
    : wxRichTextCtrl(parent, id, "", pos, size, style | wxTE_NO_VSCROLL), targetPassword(targetPassword) {
    SetVirtualSize(wxSize(400, -1));
    ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_NEVER);

    Bind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);
    Bind(wxEVT_CHAR, &PasswordInputCtrl::OnChar, this);
}

void PasswordInputCtrl::SetTargetPassword(const wxString &password) {
    targetPassword = password;
}

const wxString &PasswordInputCtrl::GetTargetPassword() const {
    return targetPassword;
}

void PasswordInputCtrl::OnTextChange(wxCommandEvent &event) {
    HighlightInput();
    event.Skip();
}

void PasswordInputCtrl::HighlightInput() {
    wxString userInput = GetValue();

    if (userInput.IsEmpty()) {
        return;
    }

    Freeze(); // skip drawing for now
    Unbind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);
    Clear();

    bool isCorrectPassword = true;
    for (size_t i = 0; i < userInput.Length(); ++i) {
        wxString currentChar = userInput.Mid(i, 1);

        wxTextAttr style;
        if (i < targetPassword.Length() && currentChar == targetPassword.Mid(i, 1)) {
            style.SetTextColour(*wxBLACK);
            style.SetBackgroundColour(*wxGREEN);
        } else {
            style.SetTextColour(*wxWHITE);
            style.SetBackgroundColour(*wxRED);
            isCorrectPassword = false;
        }

        BeginStyle(style);
        WriteText(currentChar);
        EndStyle();
    }

    Thaw(); // now draw that shit
    Bind(wxEVT_TEXT, &PasswordInputCtrl::OnTextChange, this);

    if (isCorrectPassword && userInput.Length() == targetPassword.Length()) {
        wxCommandEvent event(EVT_PASSWORD_CORRECT);
        event.SetEventObject(this);
        ProcessWindowEvent(event);
    }
}

void PasswordInputCtrl::OnChar(wxKeyEvent &event) {
    if (event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER) {
        return;
    }
    event.Skip();
}
