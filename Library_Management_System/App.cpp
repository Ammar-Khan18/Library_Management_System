#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainframe = new MainFrame("Library Management System");
	mainframe->SetClientSize(1000, 900);
	mainframe->Center();
	mainframe->Show();
	return true;
}