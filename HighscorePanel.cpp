//
// Created by Dominik Lechl on 23.01.25.
//

#include "HighscorePanel.h"

#include "MainFrame.h"
#include <wx/statline.h> // Needed for wxStaticLine

#include "HighscoreManager.h"
#include "RankEntryPanel.h"

HighscorePanel::HighscorePanel(wxWindow *parent, MainFrame *mainFrame)
    : wxPanel(parent), mainFrame(mainFrame) {
    auto *mainSizer = new wxBoxSizer(wxVERTICAL);

    auto *headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto *backButton = new wxButton(this, wxID_ANY, "←", wxDefaultPosition, wxSize(50, 30));
    backButton->Bind(wxEVT_BUTTON, &HighscorePanel::OnBackToMenu, this);
    headerSizer->Add(backButton, 0, wxALIGN_LEFT | wxTOP | wxLEFT, 10);

    auto *title = new wxStaticText(this, wxID_ANY, "Highscores", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    headerSizer->Add(title, 1, wxALIGN_CENTER | wxALIGN_CENTER_HORIZONTAL | wxTOP | wxLEFT, 10);

    auto *spacer = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));
    headerSizer->Add(spacer, 0, wxTOP | wxLEFT, 10);

    mainSizer->Add(headerSizer, 0, wxEXPAND | wxALL, 10);

    auto *divider = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2), wxLI_HORIZONTAL);
    mainSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    scrollableWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    scrollableWindow->SetScrollRate(5, 5);

    RenderHighscoreItems();

    mainSizer->Add(scrollableWindow, 1, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);

    // TODO: This feels like a nasty workaround to avoid state issues.
    Bind(wxEVT_SHOW, &HighscorePanel::OnShow, this);
}

void HighscorePanel::OnBackToMenu(wxCommandEvent &) {
    mainFrame->ShowMenu();
}

void HighscorePanel::OnShow(wxShowEvent &event) {
    if (event.IsShown()) {
        scrollableWindow->Scroll(0, 0);
        RenderHighscoreItems();
    }
    event.Skip();
}

void HighscorePanel::RenderHighscoreItems() {
    if (scrollableWindow->GetSizer()) {
        scrollableWindow->GetSizer()->Clear(true);
    }

    auto *scrollableSizer = new wxBoxSizer(wxVERTICAL);

    auto highscoreManager = HighscoreManager::GetInstance();
    const auto highscores = highscoreManager.GetHighscores();

    for (int i = 0; i < highscores.size(); i++) {
        auto rank = wxString::Format("#%d", i + 1);
        auto name = wxString::FromUTF8(highscores[i].name);
        auto score = wxString::Format("%d pts", highscores[i].score);

        auto *rankEntry = new RankEntryPanel(scrollableWindow, rank, name, score);

        scrollableSizer->Add(rankEntry, 0, wxEXPAND | wxALL, 10);
    }

    scrollableWindow->SetSizer(scrollableSizer);
    Layout();
}
