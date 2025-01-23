//
// Created by Dominik Lechl on 23.01.25.
//

#include "MainMenuPanel.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/statline.h>

MainMenuPanel::MainMenuPanel(wxWindow* parent, MainFrame* mainFrame)
    : wxPanel(parent), mainFrame(mainFrame) {
    auto* vbox = new wxBoxSizer(wxVERTICAL);

    auto* title = new wxStaticText(this, wxID_ANY, "Bruteforce", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

    auto divider = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    vbox->Add(divider, 0, wxEXPAND | wxALL, 20);

    auto* nameField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
    nameField->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    nameField->SetHint("Enter your name");
    vbox->Add(nameField, 0, wxALIGN_CENTER | wxTOP, 20);

    auto* startGameButton = new wxButton(this, wxID_ANY, "Start Game");
    startGameButton->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    startGameButton->SetMinSize(wxSize(150, 40));
    startGameButton->Enable(false);
    vbox->Add(startGameButton, 0, wxALIGN_CENTER | wxTOP, 20);

    auto* highscoreButton = new wxButton(this, wxID_ANY, "Highscores");
    highscoreButton->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    highscoreButton->SetMinSize(wxSize(150, 40));

    vbox->Add(highscoreButton, 0, wxALIGN_CENTER | wxTOP, 10);

    nameField->Bind(wxEVT_TEXT, [startGameButton](wxCommandEvent& event) {
        startGameButton->Enable(!event.GetString().IsEmpty());
    });

    startGameButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnStartGame, this);
    highscoreButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnHighscores, this);

    SetSizer(vbox);
}

void MainMenuPanel::OnStartGame(wxCommandEvent&) {
    mainFrame->ShowGame();
}

void MainMenuPanel::OnHighscores(wxCommandEvent&) {
    mainFrame->ShowHighscore();
}
