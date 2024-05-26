#include "Library.h"
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>
using namespace std;

void saveDataToFile(const vector<Library>& tasks, const string& filename) {
	ofstream ostream(filename);
	ostream << tasks.size();
	for (const Library& task : tasks) {
		/*
		string description = task.description;
		replace(description.begin(), description.end(), ' ', '_');
		ostream << '\n' << description << ' ' << task.done;
		*/
	}
}

vector<Library> loadDataFromFile(const string& filename) {
	/*
	if (!filesystem::exists(filename)) {
		return vector<Library>();
	}
	*/
	vector<Library> tasks;
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