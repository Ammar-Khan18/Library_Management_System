#include "Book.h"
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>
using namespace std;

void saveDataToFile(const vector<Book>& tasks, const string& filename) {
	ofstream ostream(filename);
	ostream << tasks.size();
	for (const Book& task : tasks) {
		/*
		string description = task.description;
		replace(description.begin(), description.end(), ' ', '_');
		ostream << '\n' << description << ' ' << task.done;
		*/
	}
}

vector<Book> loadDataFromFile(const string& filename) {
	/*
	if (!filesystem::exists(filename)) {
		return vector<Library>();
	}
	*/
	vector<Book> tasks;
	ifstream istream(filename);
	int n;
	istream >> n;
	/*
	for (int i = 0; i < n; i++) {
		string description;
		bool done;
		istream >> description >> done;
		replace(description.begin(), description.end(), '_', ' ');
		tasks.push_back(Library{ description,done });
	}
	*/
	return tasks;
}