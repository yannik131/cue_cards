#include <wx/wx.h>
#include <filesystem>
#include <vector>

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

class MyApp : public wxApp {
    virtual bool OnInit() override;
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    void CreateMenu();
    void CreateMainSizer();
    void PopulateListBox();
    void CreateMiddlePanel();
    void CreateRightPanel();
    void OnListBoxDoubleClick(wxCommandEvent& event);

    wxListBox* listBox;
    wxDECLARE_EVENT_TABLE();
};

enum {
    Test_Quit = wxID_EDIT,
    Test_About = wxID_ABOUT
};

class CueCard : public wxPanel {
public:
    CueCard(wxWindow *parent, const std::string& label) : wxPanel(parent) {
        wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        SetSizer(sizer);
        text = new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, 
        wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_CENTER);
        sizer->Add(text, 1, wxALIGN_CENTER);
        text->SetMinSize(wxSize(-1, 100));
    }

    void updateText(const std::string& content) {
        text->ChangeValue(content);
    }
private:
    wxTextCtrl* text;
};

bool MyApp::OnInit() {
    if( !wxApp::OnInit() ) {
        return false;
    }

    MyFrame* frame = new MyFrame("Ach du Scheiße!");
    frame->Show(true);
    
    return true;
}

MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    SetSize(wxSize(1024, 768));
    CreateMenu();
    CreateMainSizer();
    PopulateListBox();
    CreateMiddlePanel();
    CreateRightPanel();
    Centre();
}

void MyFrame::CreateMenu() {
    wxMenu* fileMenu = new wxMenu();
    wxMenu* helpMenu = new wxMenu();

    fileMenu->Append(Test_Quit, "&Exit\tAlt-X", "Weg mit der Scheiße!");
    helpMenu->Append(Test_About, L"&Über\tF1", "Was ist das für ne Scheiße?");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&Datei");
    menuBar->Append(helpMenu, "&Hilfe");
    SetMenuBar(menuBar);
}

void MyFrame::CreateMainSizer() {
    wxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(mainSizer);

    listBox = new wxListBox(this, wxID_ANY);
    mainSizer->Add(listBox, 1, wxEXPAND | wxALL, 20);
    listBox->Bind(wxEVT_LISTBOX_DCLICK, &MyFrame::OnListBoxDoubleClick, this);
}

void MyFrame::PopulateListBox() {
    std::vector<std::string> files = getTxtFilesInExecutionFolder();
    for (const std::string& path : files) {
        listBox->Append(std::filesystem::path(path).stem().string());
    }
}

void MyFrame::CreateMiddlePanel() {
    wxPanel* middlePanel = new wxPanel(this, wxID_ANY);
    wxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    middlePanel->SetSizer(panelSizer);
    wxPanel* buttonsPanel = new wxPanel(middlePanel, wxID_ANY);
    wxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsPanel->SetSizer(buttonSizer);
    buttonSizer->Add(new wxButton(buttonsPanel, wxID_ANY, "Knew that"), 1, wxEXPAND | wxALL, 20);
    buttonSizer->Add(new wxButton(buttonsPanel, wxID_ANY, "Didn't know that"), 1, wxEXPAND | wxALL, 20);
    panelSizer->Add(new CueCard(middlePanel, "Cue card"), 2, wxEXPAND | wxALL, 20);
    panelSizer->Add(buttonsPanel, 1, wxEXPAND | wxALL, 20);
    GetSizer()->Add(middlePanel, 1, wxEXPAND | wxALL, 20);
}

void MyFrame::CreateRightPanel() {
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY);
    wxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    rightPanel->SetSizer(rightSizer);
    CueCard* topCard = new CueCard(rightPanel, "Correct card asdf sad fads fads fads fadsf asdf dsf");
    CueCard* bottomCard = new CueCard(rightPanel, "Incorrect card");
    rightSizer->Add(topCard, 1, wxEXPAND | wxALL, 10);
    rightSizer->Add(bottomCard, 1, wxEXPAND | wxALL, 10);
    GetSizer()->Add(rightPanel, 1, wxEXPAND | wxALL, 20);
}


void MyFrame::OnListBoxDoubleClick(wxCommandEvent& event) {
    int selectedIdx = event.GetSelection();
    wxString selectedText = event.GetString();

    // Execute your callback code here
    wxMessageBox(wxString::Format("Double-clicked: %s", selectedText), "Double-Click");
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
        wxMessageBox(wxString::Format(
            "Dies ist wxWidgets, %s.\n"
            "Betriebssystem: %s.",
            wxVERSION_STRING,
            wxGetOsDescription()
        ), 
        "Gib mir die scheiß Infos!",
        wxOK | wxICON_INFORMATION,
        this
    );
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame) 
    EVT_MENU(Test_Quit, MyFrame::OnQuit)
    EVT_MENU(Test_About, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);