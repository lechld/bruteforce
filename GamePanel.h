//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "MainFrame.h"
#include <wx/wx.h>
#include "PasswordGenerator.h"
#include "PasswordInputCtrl.h"

class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow *parent, MainFrame *mainFrame);

    void SetPlayerName(const std::string &playerName) {
        this->playerName = playerName;
    }

private:
    MainFrame *mainFrame;
    PasswordInputCtrl *passwordInput;
    wxStaticText *hintText;

    wxStaticText *pointsLabel;

    wxStaticText *timerLabel;
    wxTimer timer;

    int remainingTime;
    int currentLevel;
    int currentPoints;
    std::string playerName;

    void OnBackToMenu(wxCommandEvent &event);

    void OnTimer(wxTimerEvent &event);

    void UpdateTimerLabel();

    void OnShow(wxShowEvent &event);

    void OnPasswordCorrect(wxCommandEvent &event);

    void NextLevel();
};
#endif //GAMEPANEL_H
