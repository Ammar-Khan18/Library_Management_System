#pragma once
#include<string>
#include<vector>
#include"wx/string.h"
#include"Book.h"
using namespace std;

struct User {
	string id;
	string name;
	vector<Book> loanedBooks;
	User(string i, string n) {
		id = i;
		name = n;
	}
	User(wxString i, wxString n) {
		id = i;
		name = n;
	}
};

void saveUserDataToFile(const vector<User>& users, const string& filename);
vector<User> loadUserDataFromFile(const string& filename);

