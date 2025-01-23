//
// Created by Dominik Lechl on 23.01.25.
//

#include "MainFrame.h"
#include "MainMenuPanel.h"
#include "GamePanel.h"
#include "HighscorePanel.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Bruteforce", wxDefaultPosition, wxSize(600, 400)) {
    auto* sizer = new wxBoxSizer(wxVERTICAL);

    mainMenu = new MainMenuPanel(this, this);
    gamePanel = new GamePanel(this, this);
    highscorePanel = new HighscorePanel(this, this);

    sizer->Add(mainMenu, 1, wxEXPAND);
    sizer->Add(gamePanel, 1, wxEXPAND);
    sizer->Add(highscorePanel, 1, wxEXPAND);

    SetSizer(sizer);

    ShowMenu();
}

void MainFrame::ShowMenu() {
    HidePanels();
    mainMenu->Show();
    Layout();
}

void MainFrame::ShowGame() {
    HidePanels();
    gamePanel->Show();
    Layout();
}

void MainFrame::ShowHighscore() {
    HidePanels();
    highscorePanel->Show();
    Layout();
}

void MainFrame::HidePanels() {
    mainMenu->Hide();
    gamePanel->Hide();
    highscorePanel->Hide();
}