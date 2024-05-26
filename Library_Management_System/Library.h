#include<string>
#include<vector>
using namespace std;
struct Library {
	int isbn;
	string bookName;
	string authorName;
	float price;
	int copies;
	bool available;
};

void saveDataToFile(const vector<Library>& tasks, const string& filename);
vector<Library> loadDataFromFile(const string& filename);