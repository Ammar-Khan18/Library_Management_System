#include<string>
#include<vector>
using namespace std;
struct Book {
	string isbn;
	string bookName;
	string authorName;
	float price;
	string isAvailable;
	Book(string i, string b, string a, float p, string is) {
		isbn = i;
		bookName = b;
		authorName = a;
		price = p;
		isAvailable = is;
	}
};

void saveDataToFile(const vector<Book>& tasks, const string& filename);
vector<Book> loadDataFromFile(const string& filename);