#pragma once
#include<wx/wx.h>
#include<wx/listctrl.h>
#include<string>
#include "User.h"
using namespace std;

class MainFrame : public wxFrame {
private:

	wxPanel* panel;
	wxStaticText* headlineText;

	wxButton* sortButton;
	wxButton* saveButton;
	wxButton* addBook;
	wxButton* removeBook;
	wxButton* loanToUser;

	wxStaticText* userInfo;
	
	wxListView* listView;

	void CreateControls();
	void SetupSizers();
	void populateListView();
	void BindEventHandlers();
	void addSingleItem(string isbn, string bookName, string authorName, string price, string isAvailable);

	void OnSaveButton(wxCommandEvent& evt);

	// For Sorting with ISBN
	void sortByISBN(wxCommandEvent&);
	int sortDirection = 1;

public:
	MainFrame(const wxString& title);
	vector<Book> AllBooks;
};