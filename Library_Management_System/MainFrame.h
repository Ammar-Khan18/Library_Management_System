#pragma once
#include<wx/wx.h>

class MainFrame : public wxFrame {
private:
	wxPanel* panel;
	
	void CreateControls();



public:
	MainFrame(const wxString& title);
};