#include "MainFrame.h"
#include "wx/wx.h"
#include<vector>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	CreateControls();
	SetupSizers();
	BindEventHandlers();
	populateListView();
}

void MainFrame::CreateControls() {

	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "Library Management System");
	headlineText->SetFont(headlineFont);
	
	listView = new wxListView(panel);
	listView->AppendColumn("ISBN");
	listView->AppendColumn("Title");
	listView->AppendColumn("Author");
	listView->AppendColumn("Price");
	listView->AppendColumn("Availability");
	listView->SetColumnWidth(0, 150);
	listView->SetColumnWidth(1, 200);
	listView->SetColumnWidth(2, 250);
	listView->SetColumnWidth(3, 140);
	listView->SetColumnWidth(4, 140);

	sortButton = new wxButton(panel, wxID_ANY, "Sort By ISBN");
	saveButton = new wxButton(panel, wxID_ANY, "Save Data");
}

void MainFrame::SetupSizers() {
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
	inputSizer->Add(sortButton, 0, wxALIGN_LEFT, 5);
	inputSizer->Add(saveButton, 0, wxALIGN_CENTER, 5);
	
	wxBoxSizer* listSizer = new wxBoxSizer(wxVERTICAL);
	listSizer->Add(listView, 1, wxALL | wxEXPAND, 0);

	mainSizer->Add(inputSizer, wxSizerFlags().Expand());
	mainSizer->AddSpacer(10);
	mainSizer->Add(listSizer, wxSizerFlags().Expand());

	wxGridSizer* outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 15).Expand());
	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);
}

void MainFrame::populateListView() {
	auto books = loadDataFromFile("T1.txt");
	AllBooks = books;
	for (auto i : books) {
		addSingleItem(i.isbn, i.bookName, i.authorName, to_string(i.price), i.isAvailable);
	}
}

void MainFrame::addSingleItem(string isbn, string bookName, string authorName, string price, string isAvailable) {
	int index = listView->GetItemCount();

	listView->InsertItem(index, isbn);
	listView->SetItem(index, 1, bookName);
	listView->SetItem(index, 2, authorName);
	listView->SetItem(index, 3, price);
	listView->SetItem(index, 4, isAvailable);

	listView->SetItemData(index, stoi(isbn));
}

void MainFrame::OnSaveButton(wxCommandEvent& evt) {
	saveDataToFile(AllBooks, "T1.txt");
}

void MainFrame::BindEventHandlers() {
	sortButton->Bind(wxEVT_BUTTON, &MainFrame::sortByISBN, this);
	saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButton, this);
}

void MainFrame::sortByISBN(wxCommandEvent&) {
	listView->SortItems(
		[](wxIntPtr item1, wxIntPtr item2, wxIntPtr direction) {
			if (item1 == item2) {
				return 0;
			}
			else if (item1 < item2) {
				return -(int)direction;
			}
			else {
				return (int)direction;
			}
		},
		this->sortDirection);
	
	listView->Refresh();
	this->sortDirection = -this->sortDirection;
}