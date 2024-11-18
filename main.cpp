#include <iostream>
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit(); // This method is called on application startup
};

class MyFrame : public wxFrame {
public:
    MyFrame()
        : wxFrame(nullptr, wxID_ANY, "wxWidgets Test App", wxDefaultPosition, wxSize(400, 300)) {
        // Add a simple button to the frame
        new wxButton(this, wxID_OK, "Click Me", wxPoint(150, 100), wxSize(100, 50));
    }
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true); // Show the frame
    return true; // Start the event loop
}

wxIMPLEMENT_APP(MyApp);