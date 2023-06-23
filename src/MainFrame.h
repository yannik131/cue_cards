#ifndef MAIN_FRAME_INCLUDED
#define MAIN_FRAME_INCLUDED

#include <wx/wx.h>
#include <memory>
#include <string>
#include <vector>

#include "CueCardManager.h"
#include "CueCardPanel.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    void CreateMenu();
    void CreateMainSizer();
    void PopulateListBox();
    void CreateMiddlePanel();
    void CreateRightPanel();
    void OnListBoxDoubleClick(wxCommandEvent& event);
    void OnKnewThatClick(wxCommandEvent& event);
    void OnDidntKnowThatClick(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnContinueWithIncorrectCardsClick(wxCommandEvent& event);
    void update();
    void swapCurrentCueCardPanelWithButton();

    wxListBox* listBox;
    wxPanel* middlePanel;
    wxPanel* continueButtonPanel;
    CueCardPanel* currentCueCard;
    CueCardPanel* lastCorrectCueCard;
    CueCardPanel* lastIncorrectCueCard;
    std::unique_ptr<CueCardManager> cueCardManager;
    wxDECLARE_EVENT_TABLE();
};

std::vector<std::string> getTxtFilesInExecutionFolder();

#endif