//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef HIGHSCOREPANEL_H
#define HIGHSCOREPANEL_H

#include "MainFrame.h"
#include <wx/wx.h>

class HighscorePanel : public wxPanel {
public:
    HighscorePanel(wxWindow *parent, MainFrame *mainFrame);

private:
    MainFrame *mainFrame;
    wxScrolledWindow *scrollableWindow;

    void OnBackToMenu(wxCommandEvent &event);

    void OnShow(wxShowEvent &event);

    void RenderHighscoreItems();
};
#endif //HIGHSCOREPANEL_H
