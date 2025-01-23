#include <wx/wx.h>

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
        auto* vbox = new wxBoxSizer(wxVERTICAL);

        auto* highscoreLabel = new wxStaticText(this, wxID_ANY, "Highscores:");
        auto* backButton = new wxButton(this, wxID_ANY, "←");

        vbox->Add(highscoreLabel, 0, wxALL, 10);
        vbox->Add(backButton, 0, wxALL, 10);

        SetSizer(vbox);

        backButton->Bind(wxEVT_BUTTON, &HighscorePanel::OnBackToMenu, this);
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