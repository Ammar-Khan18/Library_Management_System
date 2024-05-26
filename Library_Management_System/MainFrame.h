#pragma once
#include<wx/wx.h>

class MainFrame : public wxFrame {
private:

	wxPanel* panel;
	wxStaticText* headlineText;
	
	void CreateControls();
	void SetupSizers();


public:
	MainFrame(const wxString& title);
};