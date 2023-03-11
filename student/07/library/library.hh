#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <map>
#include <vector>

using namespace std;

// Forward declaration of Book to resolve circular dependency
struct Book;

// Define types for readability
using MapBooks = map<string, vector<Book>>;
using PairKeyValue = pair<string, string>;

// Define Book struct
struct Book
{
    string author;
    string title;
    int reservations;
};

// Define Library class
class Library
{
public:
    // Constructor for Library.
    // Param libraryName Name of the library.
    Library(string const &libraryName);

    // Add author to the library's collection.
    // Param author Author to add to the collection.
    void addAuthor(string const &author);

    // Add book to the library's collection.
    // Param author: author of the book.
    // Param title: title of the book.
    // Param reservations :number of reservations for the book.
    void addBook(string const &author,
                 string const &title,
                 int reservations);

private:
    // Name of the library
    string libraryName_;

    // Map of books, indexed by author name
    MapBooks mapBooks_;
};

#endif // LIBRARY_HH
