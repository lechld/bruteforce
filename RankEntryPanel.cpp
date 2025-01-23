//
// Created by Dominik Lechl on 23.01.25.
//

#include "RankEntryPanel.h"
#include <wx/dcbuffer.h>

RankEntryPanel::RankEntryPanel(wxWindow *parent, const wxString &rank, const wxString &name, const wxString &score)
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

void RankEntryPanel::OnPaint(wxPaintEvent&) {
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