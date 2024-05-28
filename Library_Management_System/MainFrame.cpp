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
	listView->SetColumnWidth(1, 280);
	listView->SetColumnWidth(2, 250);
	listView->SetColumnWidth(3, 140);
	listView->SetColumnWidth(4, 140);

	sortButton = new wxButton(panel, wxID_ANY, "Sort By ISBN");
	saveButton = new wxButton(panel, wxID_ANY, "Save Data");
	addBook = new wxButton(panel, wxID_ANY, "Add New Book");
	removeBook = new wxButton(panel, wxID_ANY, "Remove Book");
	loanToUser = new wxButton(panel, wxID_ANY, "Loan Books to Users");
	
	userInfo = new wxStaticText(panel, wxID_ANY, "User Info Here");
	userInfo->SetBackgroundColour("WHITE");
}

void MainFrame::SetupSizers() {
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
	inputSizer->Add(sortButton, 0, wxALIGN_LEFT, 5);
	inputSizer->AddSpacer(5);
	inputSizer->Add(saveButton, 0, wxALIGN_LEFT, 5);
	inputSizer->AddSpacer(5);
	
	wxBoxSizer* inputSizer2 = new wxBoxSizer(wxHORIZONTAL);
	inputSizer2->Add(removeBook, 0, wxALIGN_LEFT, 5);
	inputSizer2->AddSpacer(5);
	inputSizer2->Add(addBook, 0, wxALIGN_LEFT, 5);
	inputSizer2->AddSpacer(5);
	inputSizer2->Add(loanToUser, 0, wxALIGN_LEFT, 5);
	inputSizer2->AddSpacer(5);

	wxBoxSizer* UserInfoSizer = new wxBoxSizer(wxVERTICAL);
	UserInfoSizer->Add(userInfo, 0, wxALL);
	UserInfoSizer->AddSpacer(5);

	wxBoxSizer* listSizer = new wxBoxSizer(wxVERTICAL);
	listSizer->Add(listView, 1, wxALL | wxEXPAND, 0);

	mainSizer->Add(inputSizer, wxSizerFlags().Expand());
	mainSizer->AddSpacer(10);
	mainSizer->Add(inputSizer2, wxSizerFlags().Expand());
	mainSizer->AddSpacer(10);
	mainSizer->Add(UserInfoSizer, wxSizerFlags().Expand());
	mainSizer->AddSpacer(10);
	mainSizer->Add(listSizer, wxSizerFlags().Expand());

	wxGridSizer* outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 15).Expand());
	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);
}

void MainFrame::populateListView() {
	auto books = loadDataFromFile("Books.txt");
	AllBooks = books;
	for (auto i : books) {
		addSingleItem(i.isbn, i.bookName, i.authorName, i.price, i.isAvailable);
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
	saveDataToFile(AllBooks, "Books.txt");
}

void MainFrame::BindEventHandlers() {
	sortButton->Bind(wxEVT_BUTTON, &MainFrame::sortByISBN, this);
	saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButton, this);

	addBook->Bind(wxEVT_BUTTON, [this](wxCommandEvent& evt) {
		auto BookISBN = wxGetTextFromUser("Enter Book ISBN", "ISBN", "");
		auto BookTitle = wxGetTextFromUser("Enter Book Title", "Tilte", "");
		auto BookAuthor = wxGetTextFromUser("Enter Book Author Name", "Author", "");
		auto BookPrice = wxGetTextFromUser("Enter Price of Book", "Price", "");
		Book final{BookISBN,BookTitle,BookAuthor,BookPrice,"True"};
		AllBooks.push_back(final);
		listView->Refresh();
		});

	removeBook->Bind(wxEVT_BUTTON, [this](wxCommandEvent& evt) {
		auto isbn = wxGetTextFromUser("Enter the ISBN of the book you want to delete", "ISBN", "");
		int index = 0;
		for (int i = 0; i < AllBooks.size();i++) {
			if (AllBooks[i].isbn == isbn) {
				index = i;
				break;
			}
		}
		listView->DeleteItem(index);
		AllBooks.erase(AllBooks.begin() + index);
		});

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