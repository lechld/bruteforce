//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef MAINMENUPANEL_H
#define MAINMENUPANEL_H

#include <wx/wx.h>

class MainFrame;

class MainMenuPanel : public wxPanel {
public:
    MainMenuPanel(wxWindow *parent, MainFrame *mainFrame);

private:
    MainFrame *mainFrame;
    wxTextCtrl *nameField;

    void OnStartGame(wxCommandEvent &event);

    void OnHighscores(wxCommandEvent &event);
};

#endif //MAINMENUPANEL_H
