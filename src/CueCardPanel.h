#ifndef CUE_CARD_PANEL_INCLUDED
#define CUE_CARD_PANEL_INCLUDED

#include <wx/wx.h>
#include <string>

class CueCardPanel : public wxPanel {
public:
    CueCardPanel(wxWindow *parent, const std::string& label = "");

    void updateText(const std::string& content);
private:
    wxTextCtrl* text;
};

std::wstring stringToWideString(const std::string& str);

#endif