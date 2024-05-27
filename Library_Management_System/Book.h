#include<string>
#include<vector>
using namespace std;
struct Book {
	int isbn;
	string bookName;
	string authorName;
	float price;
	bool isAvailable;
};

void saveDataToFile(const vector<Book>& tasks, const string& filename);
vector<Book> loadDataFromFile(const string& filename);