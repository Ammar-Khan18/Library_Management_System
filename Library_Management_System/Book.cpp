#include "Book.h"
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

void saveDataToFile(const vector<Book>& books, const string& filename) {
	ofstream ostream(filename);
	ostream << books.size();
	for (const Book& task : books) {
		string isbn = task.isbn;
		string title = task.bookName;
		string author = task.authorName;
		string price = task.price;
		string isAvailable = task.isAvailable;

		replace(title.begin(), title.end(), ' ', '_');
		replace(author.begin(), author.end(), ' ', '_');
		string newMsg = isbn + ' ' + title + ' ' + author + ' ' + price + ' ' + isAvailable;
		ostream << '\n' << newMsg;
	}
}

vector<Book> loadDataFromFile(const string& filename) {
	vector<Book> books;
	ifstream istream(filename);
	int n;
	istream >> n;
	for (int i = 0; i < n; i++) {
		string isbn,title,author,price,avble;
		istream >> isbn >> title >> author >> price >> avble;
		replace(title.begin(), title.end(), '_', ' ');
		replace(author.begin(), author.end(), '_', ' ');
		
		books.push_back(Book{ isbn,title,author,price,avble });
	}
	return books;
}
