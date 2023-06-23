#include <locale>
#include <codecvt>

#include "CueCardPanel.h"

std::wstring stringToWideString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);
    
    return wideStr;
}

CueCardPanel::CueCardPanel(wxWindow *parent, const std::string& label) : wxPanel(parent) {
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer);
    text = new wxTextCtrl(this, wxID_ANY, label, wxDefaultPosition, 
    wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_CENTER);
    sizer->Add(text, 1, wxALIGN_CENTER);
    text->SetMinSize(wxSize(-1, 100));
}

void CueCardPanel::updateText(const std::string& content) {
    text->ChangeValue(stringToWideString(content));
}