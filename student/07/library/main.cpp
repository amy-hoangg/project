#include "library.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdlib> //USE FOR EXIT
#include <climits>

using namespace std;
using MapLibs = map<string, Library>;
using PairKeyValue = pair<string, string>;

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false)
{
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool isLineValid(string const &line)
{
    vector<string> lineParts = split(line, ';');
    return lineParts.size() == 4;
}

void readFile(string const &filename,
              MapLibs &allLibraries)
{
    //OPEN FILE
    ifstream file(filename);

    //OPEN UNSUCCESSFULLY
    if(!file)
    {
        cout << "Error: input file cannot be opened" <<endl;
        exit(EXIT_FAILURE);
    }

    //OPEN SUCCESSFULLY
    string line;
    while(getline(file, line)) //HAM GETLINE NO TU DONG LOOP LUON
    {
        if(isLineValid(line))
        {
            //SPLIT
            vector<string> lineParts = split(line, ';');

            //WRITE OUT PARAMS
            string libraryName = lineParts.at(0);
            string author = lineParts.at(1);
            string title = lineParts.at(2);
            int reservations = 0;
            if(lineParts.at(3) != "on-the-shelf")
            {
                reservations = stoi(lineParts.at(3));
            }

            //ADD LIB TO SYSTEM IF NOT AVAILABLE
            if(allLibraries.find(libraryName) == allLibraries.end())
            {
                allLibraries.insert({libraryName, Library(libraryName)});
            }

            //ADD BOOK, AUTHOR, RESERVE
            allLibraries.at(libraryName).addBook(author, title, reservations);
        }
        else
        {
            cout << "Error: empty field" <<endl;
            exit(EXIT_FAILURE);
        }
    }
    file.close();
}

void printLibraries(MapLibs const &allLibraries)
{
    for(MapLibs::const_iterator iter = allLibraries.begin();
        iter != allLibraries.end();
        iter++)
    {
        cout << iter->first << endl;
    }
}

bool comparison(const PairKeyValue &pair1,
                const PairKeyValue &pair2)
{
    if(pair1.first != pair2.first)
    {
        return pair1.first<pair2.first;
    }
    return pair1.second<pair2.second;
}

bool comparisonForReservations(const pair<string, int> &pair1,
                              const pair<string, int> &pair2)
{
    if(pair1.second != pair2.second)
    {
        return pair1.second<pair2.second;
    }
    return pair1.first<pair2.first;
}


void printMaterial(Library const &libraryName)
{
    vector<PairKeyValue> flatLib = libraryName.flatDatabase();

    //sort the data
    sort(flatLib.begin(), flatLib.end(), comparison);

    for(const auto &author_books : flatLib)
    {
        cout << author_books.first << ": " << author_books.second <<endl;
    }
}

void printBooks(Library const &libraryName,
                string const &authorName)
{
    vector<PairKeyValue> books_reservations = libraryName.books_reservations(authorName);
    sort(books_reservations.begin(), books_reservations.end(), comparison);
    for(const auto &books : books_reservations)
    {
        if(stoi(books.second) == 0)
        {
            cout << books.first << " --- " << "on the shelf" <<endl;
        }
        else
        {
            cout << books.first << " --- " << books.second <<" reservations "<<endl;
        }
    }
}

bool isOnTheShelf(vector<pair<string,int>> libs_reservations)
{
    for(const auto &pair : libs_reservations)
    {
        if(pair.second == 0)
            return true;
    }
    return false;
}

void printReservable(MapLibs allLibraries,
                     string const& reservableAuthorName,
                     string const& reservableBookName)
{
    vector<pair<string, int>> libs_reservations;
    int leastReservations = INT_MAX;
    bool bookFound = false; //flag to know if the book is found or not

    for (const auto& key_value_libs : allLibraries) {
        MapBooks mapBooksGotten = key_value_libs.second.getMapBooks();
        for (const auto& key_value_books : mapBooksGotten) {
            vector<Book> vector_books = key_value_books.second;
            for (Book bookFinding : vector_books) {
                if (bookFinding.author == reservableAuthorName &&
                    bookFinding.title == reservableBookName) {
                    bookFound = true;
                    int current_reservations = bookFinding.reservations;
                    if (current_reservations < leastReservations) {
                        leastReservations = current_reservations;
                        libs_reservations.clear();
                        libs_reservations.push_back(make_pair(key_value_libs.first, leastReservations));
                    } else if (current_reservations == leastReservations) {
                        libs_reservations.push_back(make_pair(key_value_libs.first, leastReservations));
                    }
                }
            }
        }
    }

    //SORT NAME KEY_VALUE_LIBS
    sort(libs_reservations.begin(), libs_reservations.end(), comparisonForReservations);

    //NOT FOUND
    if (!bookFound) {
        cout << "Book is not a library book" << endl;
        return; //EXIT THE FUNCTION
    }

    //CANNOT BE RESERVED
    if (leastReservations == 100) {
        cout << "Book is not reservable from any library" << endl;
        return;
    }

    //CAN BE RESERVED
    if (isOnTheShelf(libs_reservations) == true) {
        cout << "on the shelf" << endl;
    } else {
        cout << leastReservations << " reservations" << endl;
    }

    for (const auto& pair : libs_reservations) {
        cout << "--- " << pair.first << endl;
    }
}
void printLoanable (MapLibs allLibraries)
{
    //USING SET TO KEEP TRACK, BUT NEED TO USE SORT
    //SO HAVE TO STORE IN VECTOR INSTEAD OF SET
    vector<PairKeyValue> author_book;
    set<pair<string,string>> added_pairs;

    for(const auto &key_value_libs : allLibraries)
    {
        MapBooks mapBooksGotten = key_value_libs.second.getMapBooks();
        for(const auto &key_value_books : mapBooksGotten)
        {
            vector<Book> vector_books = key_value_books.second;
            for(Book bookFinding : vector_books)
            {
                if(bookFinding.reservations == 0)
                {
                    PairKeyValue new_pair = make_pair(bookFinding.author,
                                                      bookFinding.title);
                    //The if (added_pairs.count(new_pair) == 0)
                    //condition checks if the new pair is already
                    //in the set added_pairs or not.
                    if(added_pairs.count(new_pair) == 0)
                    {
                        author_book.push_back(new_pair);
                        added_pairs.insert(new_pair);
                    }
                }
            }
        }
    }
    sort(author_book.begin(), author_book.end(), comparison);

    for(const auto &pair : author_book)
    {
        cout << pair.first << ": " << pair.second <<endl;
    }
}


string removeQuotes(string stringIncludeQuotes)
{
    if(stringIncludeQuotes.front() != '"'
            && stringIncludeQuotes.back() != '"')
    {
        return stringIncludeQuotes;
    }
    size_t first = stringIncludeQuotes.find_first_not_of('"');
    size_t last = stringIncludeQuotes.find_last_not_of('"');
    string stringRemoveQuotes = stringIncludeQuotes.substr(first,
                                                           last-first+1);
    return stringRemoveQuotes;
}

bool isLibraryValid(MapLibs allLibraries,
                      string const &libraryName)
{
    bool valid = false;
    for(const auto &key_value_libs : allLibraries)
    {
        if(libraryName == key_value_libs.first)
            valid = true;
    }
    if(valid == true) return true;

    return false;
}

bool isAuthorValid(MapLibs allLibraries,
                   string const &authorName)
{
    bool valid = false;
    for(const auto &key_value_libs : allLibraries)
    {
        MapBooks mapBooksGotten = key_value_libs.second.getMapBooks();
        for(const auto &key_value_books : mapBooksGotten)
        {
            if(authorName == key_value_books.first)
                valid = true;
        }
    }
    if(valid == true) return true;
    return false;
}

int main()
{
    //INIT DATABASE
    MapLibs allLibraries;

    //READ FILENAME
    string filename;
    cout << "Input file: ";
    getline(cin, filename);

    //READ FILE AND PUT INTO DATABASE
    readFile(filename, allLibraries);


    //************COMMANDS************
    string userCommand;
    while(true)
    {
        cout << "lib> ";
        getline(cin, userCommand);

        //SPLIT THE COMMAND
        vector<string> command = split(userCommand, ' ');

        //COMMAND = QUIT
        if(userCommand == "quit")
            break;

        //COMMAND = LIBRARIES
        else if(userCommand == "libraries")
            printLibraries(allLibraries);

        //COMMAND = MATERIAL
        else if(command.at(0) == "material")
        {
            if(isLibraryValid(allLibraries, command.at(1)) == false)
            {
                cout << "Error: unknown library" <<endl;
            }
            else
            {
                string materialLibraryName = command.at(1);
                printMaterial(allLibraries.at(materialLibraryName));
            }
        }
        //COMMAND = BOOK LIB AUTHOR
        else if(command.at(0) == "books")
        {
            //WRONG SIZE
            if(command.size() != 3)
            {
                cout << "Error: wrong number of parameters" <<endl;
            }

            //WRONG LIBRARY
            else if(isLibraryValid(allLibraries,command.at(1)) == false)
            {
                cout << "Error: unknown library" <<endl;
            }

            //TRUE LIBRARY, WRONG AUTHOR
            else if(isAuthorValid(allLibraries, command.at(2)) == false)
            {
                cout << "Error: unknown author" <<endl;
            }

            else
            {
                string booksLibraryName = command.at(1);
                string booksAuthorName = command.at(2);
                printBooks(allLibraries.at(booksLibraryName), booksAuthorName);
            }
        }
        
        //COMMAND = RESERVABLE AUTHOR BOOK
        else if(command.at(0) == "reservable")
        {
            string reservableAuthorName = command.at(1);
            string reservableBookName;

            for(auto iter_reservable = command.begin() + 2;
                iter_reservable != command.end();
                iter_reservable ++)
            {
                if(iter_reservable != command.begin()+2)
                    reservableBookName += " ";
                reservableBookName += *iter_reservable;
            }
            //TRUONG HOP CNO CO CAI QUOTES THI PHAI REMOVE
            reservableBookName = removeQuotes(reservableBookName);

            printReservable(allLibraries, reservableAuthorName, reservableBookName);
        }

        //COMMAND = LOANABLE
        else if(command.at(0) == "loanable")
        {
            printLoanable(allLibraries);
        }

        //UNKNOWN COMMAND
        else
        {
            cout << "Error: unknown command" <<endl;
        }
    }

    return EXIT_SUCCESS;
}
