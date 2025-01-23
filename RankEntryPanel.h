//
// Created by Dominik Lechl on 23.01.25.
//

#ifndef RANKENTRYPANEL_H
#define RANKENTRYPANEL_H

#include <wx/wx.h>

class RankEntryPanel : public wxPanel {
public:
    RankEntryPanel(wxWindow* parent, const wxString& rank, const wxString& name, const wxString& score);
protected:
    void OnPaint(wxPaintEvent&);
};

#endif //RANKENTRYPANEL_H
