#include <wx/wx.h>
#include <wx/statline.h>

class MainMenuPanel;
class GamePanel;
class HighscorePanel;

class MainFrame : public wxFrame {
public:
    MainFrame();

    void ShowMenu();
    void ShowGame();
    void ShowHighscore();

private:
    MainMenuPanel* mainMenu;
    GamePanel* gamePanel;
    HighscorePanel* highscorePanel;

    void HidePanels();
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

// Main Menu Panel
class MainMenuPanel : public wxPanel {
public:
    MainMenuPanel(wxWindow* parent, MainFrame* mainFrame)
        : wxPanel(parent), mainFrame(mainFrame) {

        auto* vbox = new wxBoxSizer(wxVERTICAL);

        auto* title = new wxStaticText(this, wxID_ANY, "Bruteforce", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        vbox->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

        auto divider = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
        vbox->Add(divider, 0, wxEXPAND | wxALL, 20);

        auto* nameField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
        nameField->SetHint("Enter name");
        vbox->Add(nameField, 0, wxALIGN_CENTER | wxTOP, 20);

        auto* startGameButton = new wxButton(this, wxID_ANY, "Start Game");
        startGameButton->Enable(false); // Disable until a name is entered
        vbox->Add(startGameButton, 0, wxALIGN_CENTER | wxTOP, 10);

        auto* highscoreButton = new wxButton(this, wxID_ANY, "Highscores");
        vbox->Add(highscoreButton, 0, wxALIGN_CENTER | wxTOP, 10);

        nameField->Bind(wxEVT_TEXT, [startGameButton](wxCommandEvent& event) {
            startGameButton->Enable(!event.GetString().IsEmpty());
        });

        startGameButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnStartGame, this);
        highscoreButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnHighscores, this);

        SetSizer(vbox);
    }

private:
    MainFrame* mainFrame;
    wxTextCtrl* nameInput;

    void OnStartGame(wxCommandEvent& event) {
        mainFrame->ShowGame();
    }

    void OnHighscores(wxCommandEvent& event) {
        mainFrame-> ShowHighscore();
    }
};

// Game Panel
class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow* parent, MainFrame* mainFrame)
        : wxPanel(parent), mainFrame(mainFrame) {
        auto* vbox = new wxBoxSizer(wxVERTICAL);

        auto* backButton = new wxButton(this, wxID_ANY, "Back to Menu");
        vbox->Add(backButton, 0, wxALL, 10);

        SetSizer(vbox);

        backButton->Bind(wxEVT_BUTTON, &GamePanel::OnBackToMenu, this);
    }

private:
    MainFrame* mainFrame;

    void OnBackToMenu(wxCommandEvent& event) {
        mainFrame->ShowMenu();
    }
};

class HighscorePanel : public wxPanel {
public:
    HighscorePanel(wxWindow* parent, MainFrame* mainFrame)
        : wxPanel(parent), mainFrame(mainFrame) {
        auto mainSizer = new wxBoxSizer(wxVERTICAL);

        auto scrollableArea = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
        scrollableArea->SetScrollRate(5, 5);

        auto scrollSizer = new wxBoxSizer(wxVERTICAL);

        auto backButton = new wxButton(scrollableArea, wxID_ANY, "←", wxDefaultPosition, wxSize(50, 30));
        backButton->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        backButton->Bind(wxEVT_BUTTON, &HighscorePanel::OnBackToMenu, this);

        auto* title = new wxStaticText(scrollableArea, wxID_ANY, "Highscores", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        auto headerSizer = new wxBoxSizer(wxHORIZONTAL);
        headerSizer->Add(backButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxTOP, 10);
        headerSizer->AddStretchSpacer();
        headerSizer->Add(title, 0, wxALIGN_CENTER_VERTICAL | wxTOP, 10);
        headerSizer->AddStretchSpacer();

        scrollSizer->Add(headerSizer, 0, wxEXPAND | wxALL, 10);

        auto divider = new wxStaticLine(scrollableArea, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
        scrollSizer->Add(divider, 0, wxEXPAND | wxALL, 10);

        for (int i = 1; i <= 10; ++i) {
            auto* rowSizer = new wxBoxSizer(wxHORIZONTAL);
            auto* rank = new wxStaticText(scrollableArea, wxID_ANY, wxString::Format("#%d", i), wxDefaultPosition, wxSize(50, -1));
            auto* name = new wxStaticText(scrollableArea, wxID_ANY, wxString::Format("Player %d", i), wxDefaultPosition, wxSize(150, -1));
            auto* score = new wxStaticText(scrollableArea, wxID_ANY, wxString::Format("%d pts", 1000 - i * 50), wxDefaultPosition, wxSize(100, -1));

            rowSizer->Add(rank, 0, wxLEFT | wxRIGHT, 10);
            rowSizer->Add(name, 0, wxEXPAND | wxRIGHT, 10);
            rowSizer->Add(score, 0, wxEXPAND);

            scrollSizer->Add(rowSizer, 0, wxEXPAND | wxALL, 5);
        }

        scrollableArea->SetSizer(scrollSizer);
        scrollSizer->SetSizeHints(scrollableArea);

        mainSizer->Add(scrollableArea, 1, wxEXPAND);

        SetSizer(mainSizer);
    }

private:
    MainFrame* mainFrame;

    void OnBackToMenu(wxCommandEvent& event) {
        mainFrame->ShowMenu();
    }
};

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Simple Game", wxDefaultPosition, wxSize(600, 400)) {
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

wxIMPLEMENT_APP(MyApp);