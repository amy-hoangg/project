#include "library.hh"

Library::Library(string const &libraryName):
    libraryName_(libraryName),
    mapBooks_({})
{

}

void Library::addAuthor(const string &author)
{
    if(mapBooks_.find(author) == mapBooks_.end())
    {
        mapBooks_.insert({author, {}});
    }
}

void Library::addBook(const string &author, const string &title, int reservations)
{
    Book newBook{author, title, reservations};
    addAuthor(author);
    mapBooks_.at(author).push_back(newBook);

}



