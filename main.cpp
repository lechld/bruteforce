#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/dcbuffer.h>
#include <wx/timer.h>

const int GAME_DURATION_SECONDS = 300;

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
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

class RankEntryPanel : public wxPanel {
public:
    RankEntryPanel(wxWindow* parent, const wxString& rank, const wxString& name, const wxString& score)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE) {
        SetBackgroundStyle(wxBG_STYLE_PAINT);

        auto sizer = new wxBoxSizer(wxHORIZONTAL);

        auto rankLabel = new wxStaticText(this, wxID_ANY, rank, wxDefaultPosition, wxDefaultSize);
        rankLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        rankLabel->SetForegroundColour(*wxBLACK);

        auto nameLabel = new wxStaticText(this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize);
        nameLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        nameLabel->SetForegroundColour(*wxBLACK);

        auto scoreLabel = new wxStaticText(this, wxID_ANY, score, wxDefaultPosition, wxDefaultSize);
        scoreLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        scoreLabel->SetForegroundColour(*wxBLACK);

        sizer->Add(rankLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
        sizer->Add(nameLabel, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
        sizer->Add(scoreLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);

        SetSizer(sizer);

        SetMinSize(wxSize(-1, 60));
        Bind(wxEVT_PAINT, &RankEntryPanel::OnPaint, this);
    }

protected:
    void OnPaint(wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(this);
        wxSize size = GetSize();

        wxColour bgColor(240, 240, 240);
        wxColour borderColor(200, 200, 200);
        dc.SetBrush(wxBrush(bgColor));
        dc.SetPen(wxPen(borderColor, 2));
        dc.DrawRoundedRectangle(0, 0, size.GetWidth(), size.GetHeight(), 10);

        dc.SetBrush(wxBrush(wxColour(0, 0, 0, 50)));
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRoundedRectangle(3, 3, size.GetWidth() - 3, size.GetHeight() - 3, 10);
    }
};

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

class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow* parent, MainFrame* mainFrame)
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

        // Timer label
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
        timer.Start(1000); // Each second

        UpdateTimerLabel();
    }
private:
    MainFrame* mainFrame;

    wxStaticText* timerLabel;
    wxTimer timer;
    int remainingTime;

    void OnBackToMenu(wxCommandEvent& event) {
        if (int response = wxMessageBox("Are you sure you want to go back to the menu? Progress will be lost.", "Confirm", wxYES_NO | wxICON_QUESTION, this); response == wxYES) {
            mainFrame->ShowMenu();
        }
    }

    void OnTimer(wxTimerEvent& event) {
        if (remainingTime > 0) {
            remainingTime--;
            UpdateTimerLabel();
        } else {
            timer.Stop();
            wxMessageBox("Time's up!", "Notification", wxOK | wxICON_INFORMATION, this);
        }
    }

    void UpdateTimerLabel() {
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        timerLabel->SetLabel(wxString::Format("%02d:%02d", minutes, seconds));
    }

    void OnShow(wxShowEvent& event) {
        remainingTime = GAME_DURATION_SECONDS;
    }
};

class HighscorePanel : public wxPanel {
public:
    HighscorePanel(wxWindow* parent, MainFrame* mainFrame)
        : wxPanel(parent), mainFrame(mainFrame) {
        auto* mainSizer = new wxBoxSizer(wxVERTICAL);

        auto* headerSizer = new wxBoxSizer(wxHORIZONTAL);

        auto* backButton = new wxButton(this, wxID_ANY, "←", wxDefaultPosition, wxSize(50, 30));
        backButton->Bind(wxEVT_BUTTON, &HighscorePanel::OnBackToMenu, this);
        headerSizer->Add(backButton, 0, wxALIGN_LEFT | wxTOP | wxLEFT, 10);

        auto* title = new wxStaticText(this, wxID_ANY, "Highscores", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        headerSizer->Add(title, 1, wxALIGN_CENTER | wxALIGN_CENTER_HORIZONTAL | wxTOP | wxLEFT, 10);

        auto* spacer = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));
        headerSizer->Add(spacer, 0, wxTOP | wxLEFT, 10);

        mainSizer->Add(headerSizer, 0, wxEXPAND | wxALL, 10);

        auto* divider = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2), wxLI_HORIZONTAL);
        mainSizer->Add(divider, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

        scrollableWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
        scrollableWindow->SetScrollRate(5, 5);

        auto* scrollableSizer = new wxBoxSizer(wxVERTICAL);

        for (int i = 1; i <= 20; ++i) {
            wxString rank = wxString::Format("#%d", i);
            wxString name = wxString::Format("Player %d", i);
            wxString score = wxString::Format("%d pts", 1000 - i * 50);

            auto* rankEntry = new RankEntryPanel(scrollableWindow, rank, name, score);

            scrollableSizer->Add(rankEntry, 0, wxEXPAND | wxALL, 10);
        }

        scrollableWindow->SetSizer(scrollableSizer);
        mainSizer->Add(scrollableWindow, 1, wxEXPAND | wxALL, 10);

        SetSizer(mainSizer);

        // TODO: This feels like a nasty workaround to avoid state issues.
        Bind(wxEVT_SHOW, &HighscorePanel::OnShow, this);
    }

private:
    MainFrame* mainFrame;
    wxScrolledWindow* scrollableWindow;

    void OnBackToMenu(wxCommandEvent& event) {
        mainFrame->ShowMenu();
    }

    void OnShow(wxShowEvent& event) {
        if (event.IsShown()) {
            scrollableWindow->Scroll(0, 0);
        }
        event.Skip();
    }
};

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

wxIMPLEMENT_APP(MyApp);