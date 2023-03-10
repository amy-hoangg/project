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

vector<PairKeyValue> Library::flatDatabase() const
{
    vector<PairKeyValue> flatDatabase = {};
    for(const auto &author : mapBooks_)//author is pair
    {
        for(const auto &book : author.second)
        {
            flatDatabase.push_back(make_pair(author.first,
                                             book.title));
            //book is not a string but a struct so have to extract title
        }
    }
    return flatDatabase;
}

vector<PairKeyValue> Library::books_reservations(const string &author) const
{
    vector<PairKeyValue> books_reservations = {};
    for(const auto &book : mapBooks_.at(author))
    {
        books_reservations.push_back(make_pair(book.title,
                                     to_string(book.reservations)));
    }
    return books_reservations;
}

MapBooks Library::getMapBooks() const
{
    return mapBooks_;
}


