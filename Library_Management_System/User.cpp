#include "User.h"
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

void saveUserDataToFile(const vector<User>& users, const string& filename) {
	ofstream ostream(filename);
	ostream << users.size();
	for (User tasks : users) {
		string name = tasks.name;
		replace(name.begin(), name.end(), ' ', '_');
		string id = tasks.id;
		int loanBooks = tasks.loanedBooks.size();
		string newMsg = id + ' ' + name + ' ' + to_string(loanBooks) + ' ';
		string loanBookString = "";
		for (int i = 0; i < tasks.loanedBooks.size(); i++) {
			string title = tasks.loanedBooks[i].bookName;
			string author = tasks.loanedBooks[i].authorName;
			replace(title.begin(), title.end(), ' ', '_');
			replace(author.begin(), author.end(), ' ', '_');
			loanBookString += tasks.loanedBooks[i].isbn + ' ' + title + ' ' + author + ' ' + tasks.loanedBooks[i].price + ' ' + tasks.loanedBooks[i].isAvailable + ' ';
		}
		newMsg += loanBookString;
		ostream << '\n' << newMsg;
	}
}

vector<User> loadUserDataFromFile(const string& filename)
{
	return vector<User>();
}
