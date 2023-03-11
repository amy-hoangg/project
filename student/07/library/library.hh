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
    // Param library: name of the library.
    Library(string const &libraryName);

    // Add author to the library's collection.
    // Param author: author to add to the collection.
    void addAuthor(string const &author);

    // Add book to the library's collection.
    // Param author: author of the book.
    // Param title: title of the book.
    // Param reservations :number of reservations for the book.
    void addBook(string const &author,
                 string const &title,
                 int reservations);

    // Flatten library's book database by
    //      iterates through the internal data structure of the library (mapBooks_),
    //      and for each author and book combination
    //      adds a new pair to a vector of pairs
    // Return: a vector contains all books in the library with
    //      their corresponding author names
    vector<PairKeyValue> flatDatabase() const;

    // Retrieve the list of books for the given author
    //      from the internal data structure of the library (mapBooks_),
    //      and for each book, adds a new pair to a vector of pairs,
    //      returns a list of books by a given author, along with their reservation counts
    // Param author: The name of the author for which to retrieve book information
    // Return: a vector contains all books by the given author with
    //      their corresponding reservation counts
    vector<PairKeyValue> books_reservations(string const &author) const;

    // Returns a copy of the library's internal book data structure (mapBooks_),
    //      the structure is a map indexed by author name, with a vector of books for each author.
    MapBooks getMapBooks () const;

private:
    // Name of the library
    string libraryName_;

    // Map of books, indexed by author name
    MapBooks mapBooks_;
};

#endif // LIBRARY_HH
