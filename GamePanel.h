//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "MainFrame.h"
#include <wx/wx.h>

class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow* parent, MainFrame* mainFrame);

private:
    MainFrame* mainFrame;

    wxStaticText* timerLabel;
    wxTimer timer;
    int remainingTime;

    void OnBackToMenu(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void UpdateTimerLabel();
    void OnShow(wxShowEvent& event);

};
#endif //GAMEPANEL_H
