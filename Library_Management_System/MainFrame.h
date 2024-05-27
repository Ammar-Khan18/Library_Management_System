#pragma once
#include<wx/wx.h>
#include<wx/listctrl.h>
#include<string>
#include<unordered_set>
using namespace std;

class MainFrame : public wxFrame {
private:

	wxPanel* panel;
	wxStaticText* headlineText;

	wxButton* sortButton;
	
	wxListView* listView;

	void CreateControls();
	void SetupSizers();
	void populateListView();
	void addSingleItem(string isbn, string bookName, string authorName, string price, string isAvailable);

	void BindEventHandlers();

	// For Sorting through Columns
	
	void sortByISBN(wxCommandEvent&);
	int sortDirection = 1;
	
	/*
	void sortByColumns(int column);
	int sortDirection = 1;

	struct ItemData {
		string isbn;
		string bookName;
		string authorName;
		string price;
		string isAvailable;
	};

	unordered_set<unique_ptr<ItemData>> itemDataBag;

	static int compareString(string s1, string s2, int direction);

	static int isbnSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int bookNameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int authorNameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	static int isAvailableSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
	*/
public:
	MainFrame(const wxString& title);
};