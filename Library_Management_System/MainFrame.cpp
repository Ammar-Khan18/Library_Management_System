#include "MainFrame.h"
#include "wx/wx.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	CreateControls();
	SetupSizers();
	populateListView();
	BindEventHandlers();
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
	listView->SetColumnWidth(3, 80);
	listView->SetColumnWidth(4, 140);

	sortButton = new wxButton(panel, wxID_ANY, "Sort By ISBN");
	sortButton->Bind(wxEVT_BUTTON, &MainFrame::sortByISBN, this);
}

void MainFrame::SetupSizers() {
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
	inputSizer->Add(sortButton, 0, wxALIGN_LEFT,5);
	
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
	addSingleItem("18818186", "ABC", "XYZ", "12.99", "1");
	addSingleItem("98974616", "OPD", "LPW", "19.99", "0");
	addSingleItem("45651897", "INF", "RIN", "50.99", "0");
	addSingleItem("03945184", "AUB", "OAN", "12.99", "1");
}

void MainFrame::addSingleItem(string isbn, string bookName, string authorName, string price, string isAvailable) {
	int index = listView->GetItemCount();
	string available = "False";

	listView->InsertItem(index, isbn);
	listView->SetItem(index, 1, bookName);
	listView->SetItem(index, 2, authorName);
	listView->SetItem(index, 3, price);
	if (isAvailable == "1") {
		available = "True";
	}
	listView->SetItem(index, 4, available);

	listView->SetItemData(index, stoi(isbn));
	/*
	ItemData data{isbn, bookName, authorName, price, isAvailable};
	auto dataPtr = make_unique<ItemData>(data);


	listView->SetItemData(index, reinterpret_cast<wxIntPtr>(dataPtr.get()));
	itemDataBag.insert(move(dataPtr));
	*/
}

void MainFrame::BindEventHandlers() {
	
	/*
	listView->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent& evt) {
		this->sortByColumns(evt.GetColumn());
		});
	*/
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
/*
void MainFrame::sortByColumns(int column) {
	switch (column) {
	case 0:
		listView->SortItems(isbnSortCallback, this->sortDirection);
		break;
	case 1:
		listView->SortItems(bookNameSortCallback, this->sortDirection);
		break;
	case 2:
		listView->SortItems(authorNameSortCallback, this->sortDirection);
		break;
	case 3:
		listView->SortItems(priceSortCallback, this->sortDirection);
		break;
	case 4:
		listView->SortItems(isAvailableSortCallback, this->sortDirection);
		break;
	default:
		return;
	}

	listView->Refresh();
	this->sortDirection = -this->sortDirection;
}
// All of these functions are for sorting
int MainFrame::compareString(string s1,string s2, int direction)
{
	return s1.compare(s2) * direction;
}

int MainFrame::isbnSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareString(reinterpret_cast<ItemData *>(item1)->isbn, reinterpret_cast<ItemData *>(item2)->isbn, static_cast<int>(direction));
}

int MainFrame::bookNameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareString(reinterpret_cast<ItemData*>(item1)->bookName, reinterpret_cast<ItemData*>(item2)->bookName, static_cast<int>(direction));
}

int MainFrame::authorNameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareString(reinterpret_cast<ItemData*>(item1)->authorName, reinterpret_cast<ItemData*>(item2)->authorName, static_cast<int>(direction));
}

int MainFrame::priceSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareString(reinterpret_cast<ItemData*>(item1)->price, reinterpret_cast<ItemData*>(item2)->price, static_cast<int>(direction));
}

int MainFrame::isAvailableSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
	return compareString(reinterpret_cast<ItemData*>(item1)->isAvailable, reinterpret_cast<ItemData*>(item2)->isAvailable, static_cast<int>(direction));
}
*/
