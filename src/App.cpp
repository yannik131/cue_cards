#include <wx/wx.h>

#include "App.h"
#include "MainFrame.h"

bool MyApp::OnInit() {
    if( !wxApp::OnInit() ) {
        return false;
    }

    MainFrame* frame = new MainFrame("Ach du Scheiße!");
    frame->Show(true);
    
    return true;
}
