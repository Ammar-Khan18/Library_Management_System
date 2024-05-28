#include<string>
#include<vector>
#include"wx/string.h"
using namespace std;
struct Book {
	string isbn;
	string bookName;
	string authorName;
	string price;
	string isAvailable;
	Book(string i, string b, string a, string p, string is) {
		isbn = i;
		bookName = b;
		authorName = a;
		price = p;
		isAvailable = is;
	}
	Book(wxString i, wxString b, wxString a, wxString p, string is) {
		isbn = i;
		bookName = b;
		authorName = a;
		price = p;
		isAvailable = is;
	}
};

void saveDataToFile(const vector<Book>& tasks, const string& filename);
vector<Book> loadDataFromFile(const string& filename);