#include <filesystem>

#include "MainFrame.h"
#include "CueCardReader.h"

enum {
    Test_Quit = wxID_EDIT,
    Test_About = wxID_ABOUT,
    Knew_that_Button_ID = wxID_HIGHEST + 1,
    Didnt_know_that_Button_ID,
    Continue_with_incorrect_cards_Button_ID
};

std::vector<std::string> getTxtFilesInExecutionFolder() {
    std::vector<std::string> txtFiles;
    std::filesystem::path currentDir = std::filesystem::current_path();

    // Iterate over all files and directories in the current directory
    for (const auto& entry : std::filesystem::directory_iterator(currentDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            // Store the full path of the text file
            txtFiles.push_back(entry.path().string());
        }
    }

    return txtFiles;
}

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    SetSize(wxSize(1024, 768));
    CreateMenu();
    CreateMainSizer();
    PopulateListBox();
    CreateMiddlePanel();
    CreateRightPanel();
    Centre();
}

void MainFrame::CreateMenu() {
    wxMenu* fileMenu = new wxMenu();
    wxMenu* helpMenu = new wxMenu();

    fileMenu->Append(Test_Quit, "&Exit\tAlt-X", "Weg mit der Scheiße!");
    helpMenu->Append(Test_About, L"&Über\tF1", "Was ist das für ne Scheiße?");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&Datei");
    menuBar->Append(helpMenu, "&Hilfe");
    SetMenuBar(menuBar);
}

void MainFrame::CreateMainSizer() {
    wxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(mainSizer);

    listBox = new wxListBox(this, wxID_ANY);
    mainSizer->Add(listBox, 1, wxEXPAND | wxALL, 20);
    listBox->Bind(wxEVT_LISTBOX_DCLICK, &MainFrame::OnListBoxDoubleClick, this);
}

void MainFrame::PopulateListBox() {
    std::vector<std::string> files = getTxtFilesInExecutionFolder();
    for (const std::string& path : files) {
        listBox->Append(std::filesystem::path(path).stem().string());
    }
}

void MainFrame::CreateMiddlePanel() {
    this->middlePanel = new wxPanel(this, wxID_ANY);
    wxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    this->middlePanel->SetSizer(panelSizer);
    wxPanel* buttonsPanel = new wxPanel(middlePanel, wxID_ANY);
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsPanel->SetSizer(buttonSizer);

    buttonSizer->Add(new wxButton(buttonsPanel, Knew_that_Button_ID, "Knew that"), 1, wxEXPAND | wxALL, 20);
    buttonSizer->Add(new wxButton(buttonsPanel, Didnt_know_that_Button_ID, "Didn't know that"), 1, wxEXPAND | wxALL, 20);
    this->currentCueCard = new CueCardPanel(middlePanel);

    this->continueButtonPanel = new wxPanel(middlePanel, wxID_ANY);
    wxSizer* continueButtonPanelSizer = new wxBoxSizer(wxVERTICAL);
    this->continueButtonPanel->SetSizer(continueButtonPanelSizer);
    wxButton* continueWithIncorrectCardsButton = new wxButton(this->continueButtonPanel, 
    Continue_with_incorrect_cards_Button_ID, "Continue with incorrect cards");
    continueButtonPanelSizer->AddStretchSpacer();
    continueButtonPanelSizer->Add(continueWithIncorrectCardsButton, 0, wxALIGN_CENTER);
    continueButtonPanelSizer->AddStretchSpacer();
    this->continueButtonPanel->Hide();

    panelSizer->Add(this->currentCueCard, 2, wxEXPAND | wxALL, 20);
    panelSizer->Add(this->continueButtonPanel, 2, wxEXPAND | wxALL, 20);
    panelSizer->Add(buttonsPanel, 1, wxEXPAND | wxALL, 20);
    GetSizer()->Add(this->middlePanel, 1, wxEXPAND | wxALL, 20);
}

void MainFrame::CreateRightPanel() {
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY);
    wxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    rightPanel->SetSizer(rightSizer);
    lastCorrectCueCard = new CueCardPanel(rightPanel);
    lastIncorrectCueCard = new CueCardPanel(rightPanel);
    rightSizer->Add(new wxStaticText(rightPanel, wxID_ANY, "Correct:"), 1, wxALL, 10);
    rightSizer->Add(lastCorrectCueCard, 1, wxEXPAND | wxALL, 10);
    rightSizer->Add(new wxStaticText(rightPanel, wxID_ANY, "Incorrect:"), 1, wxALL, 10);
    rightSizer->Add(lastIncorrectCueCard, 1, wxEXPAND | wxALL, 10);
    GetSizer()->Add(rightPanel, 1, wxEXPAND | wxALL, 20);
}


void MainFrame::OnListBoxDoubleClick(wxCommandEvent& event) {
    int selectedIdx = event.GetSelection();
    std::string selectedText = event.GetString().ToStdString();
    std::string path = std::filesystem::current_path().append(selectedText+".txt");
    
    CueCardReader reader;
    try {
        CueCardCollection cueCardCollection = reader.getCueCardsFromFile(path);
        CueCardManager* manager = new CueCardManager(cueCardCollection);
        manager->shuffleCards();
        this->cueCardManager.reset(manager);
        this->currentCueCard->updateText(this->cueCardManager->getCurrentCards().back()->mFrontText);
        this->lastCorrectCueCard->updateText("");
        this->lastIncorrectCueCard->updateText("");
        if(this->continueButtonPanel->IsShown()) {
            this->swapCurrentCueCardPanelWithButton();
        }
    }
    catch(const std::exception& exc) {
        wxMessageBox(wxString::Format(exc.what()), "Exception");
    }
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
        wxMessageBox(wxString::Format(
            "Using %s.\n"
            "OS %s.",
            wxVERSION_STRING,
            wxGetOsDescription()
        ), 
        "Gib mir die scheiß Infos!",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void MainFrame::OnKnewThatClick(wxCommandEvent& event) {
    if(this->cueCardManager == nullptr || this->cueCardManager->getCurrentCards().empty()) {
        return;
    }
    this->cueCardManager->studentKnewTheCard();
    this->update();
}

void MainFrame::OnDidntKnowThatClick(wxCommandEvent& event) {
    if(this->cueCardManager == nullptr || this->cueCardManager->getCurrentCards().empty()) {
        return;
    }
    this->cueCardManager->studentDidntKnowTheCard();
    this->update();
}

void MainFrame::swapCurrentCueCardPanelWithButton() {
    wxWindow* toHide = this->currentCueCard, *toShow = this->continueButtonPanel;
    if(this->continueButtonPanel->IsShown()) {
        toHide = this->continueButtonPanel;
        toShow = this->currentCueCard;
    }
    toHide->Hide();
    toShow->Show();
    this->middlePanel->GetSizer()->Layout();
}

void MainFrame::update() {
    if(!this->cueCardManager->getCorrectCards().empty()) {
        this->lastCorrectCueCard->updateText(this->cueCardManager->getCorrectCards().back()->mBackText);
    }
    if(!this->cueCardManager->getIncorrectCards().empty()) {
        this->lastIncorrectCueCard->updateText(this->cueCardManager->getIncorrectCards().back()->mBackText);
    }
    if(this->cueCardManager->getCurrentCards().empty() && !this->cueCardManager->getIncorrectCards().empty()) {
        this->swapCurrentCueCardPanelWithButton();
        return;
    }
    else if(this->cueCardManager->getCurrentCards().empty()) {
        this->currentCueCard->updateText("Done!");
        return;
    }
    this->currentCueCard->updateText(this->cueCardManager->getCurrentCards().back()->mFrontText);
}

void MainFrame::OnContinueWithIncorrectCardsClick(wxCommandEvent& event) {
    this->cueCardManager->continueWithIncorrectCards();
    this->swapCurrentCueCardPanelWithButton();
    this->update();
    this->lastIncorrectCueCard->updateText("");
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame) 
    EVT_MENU(Test_Quit, MainFrame::OnQuit)
    EVT_MENU(Test_About, MainFrame::OnAbout)
    EVT_BUTTON(Knew_that_Button_ID, MainFrame::OnKnewThatClick)
    EVT_BUTTON(Didnt_know_that_Button_ID, MainFrame::OnDidntKnowThatClick)
    EVT_BUTTON(Continue_with_incorrect_cards_Button_ID, MainFrame::OnContinueWithIncorrectCardsClick)
wxEND_EVENT_TABLE()