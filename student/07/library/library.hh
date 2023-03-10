#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <map>
#include <vector>

using namespace std;
struct Book;
using MapBooks = map<string, vector<Book>>;
using PairKeyValue = pair<string, string>;

struct Book
{
    string author;
    string title;
    int reservations;
};

class Library
{
public:
    Library(string const &libraryName);

    void addAuthor(string const &author);

    void addBook(string const &author,
            string const &title,
            int reservations);

    vector<PairKeyValue> flatDatabase() const;

    vector<PairKeyValue> books_reservations(string const &author) const;

    MapBooks getMapBooks () const;

private:
    string libraryName_;
    MapBooks mapBooks_;
};

#endif // LIBRARY_HH
