//
// Created by Dominik Lechl on 23.01.25.
//

#include "GamePanel.h"
#include "MainFrame.h"
#include <wx/statline.h>

const int GAME_DURATION_SECONDS = 300;

GamePanel::GamePanel(wxWindow* parent, MainFrame* mainFrame)
    : wxPanel(parent), mainFrame(mainFrame), remainingTime(GAME_DURATION_SECONDS) {
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);

    auto* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* backButton = new wxButton(this, wxID_ANY, "←", wxDefaultPosition, wxSize(50, 30));
    backButton->Bind(wxEVT_BUTTON, &GamePanel::OnBackToMenu, this);
    headerSizer->Add(backButton, 0, wxALIGN_LEFT | wxTOP | wxLEFT, 10);

    auto* titleSizer = new wxBoxSizer(wxVERTICAL);
    auto* title = new wxStaticText(this, wxID_ANY, "Level 1", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    titleSizer->Add(title, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    headerSizer->Add(titleSizer, 1, wxALIGN_CENTER_VERTICAL);

    auto* timerSizer = new wxBoxSizer(wxVERTICAL);
    timerLabel = new wxStaticText(this, wxID_ANY, "05:00", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    timerLabel->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    timerSizer->Add(timerLabel, 0, wxALIGN_RIGHT | wxTOP | wxRIGHT, 10);

    headerSizer->Add(timerSizer, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

    mainSizer->Add(headerSizer, 0, wxEXPAND | wxALL, 10);

    auto* divider = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2), wxLI_HORIZONTAL);
    mainSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    SetSizer(mainSizer);

    Bind(wxEVT_SHOW, &GamePanel::OnShow, this);
    timer.Bind(wxEVT_TIMER, &GamePanel::OnTimer, this);

    UpdateTimerLabel();
}


void GamePanel::OnBackToMenu(wxCommandEvent& event) {
    if (int response = wxMessageBox("Are you sure you want to go back to the menu? Progress will be lost.", "Confirm", wxYES_NO | wxICON_QUESTION, this); response == wxYES) {
        mainFrame->ShowMenu();
    }
}

void GamePanel::OnTimer(wxTimerEvent& event) {
    if (remainingTime > 0) {
        remainingTime--;
        UpdateTimerLabel();
    } else {
        timer.Stop();
        wxMessageBox("Time's up!", "Notification", wxOK | wxICON_INFORMATION, this);
    }
}

void GamePanel::UpdateTimerLabel() {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    timerLabel->SetLabel(wxString::Format("%02d:%02d", minutes, seconds));
}

void GamePanel::OnShow(wxShowEvent& event) {
    if (event.IsShown()) {
        remainingTime = GAME_DURATION_SECONDS;
        UpdateTimerLabel();
        timer.Start(1000);
    } else {
        timer.Stop();
    }
}