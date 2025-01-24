//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainMenuPanel;
class GamePanel;
class HighscorePanel;

class MainFrame : public wxFrame {
public:
    MainFrame();

    ~MainFrame();

    void ShowMenu();

    void ShowGame(const std::string &playerName);

    void ShowHighscore();

private:
    MainMenuPanel *mainMenu;
    GamePanel *gamePanel;
    HighscorePanel *highscorePanel;

    void HidePanels();
};

#endif //MAINFRAME_H
