#include "library.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;
using MapLibs = map<string, Library>;
using PairKeyValue = pair<string, string>;

//Function: split a string -> a vector of substrings
//          based on delimiter
//Param s: input string
//Param delimiter: character used to split the string
//Param ignore_empty: optional flag to indicate whether ignore
//                    empty substrings in output vector or not
//Return: a vector of substrings, split by the delimiter character

vector<string> split(const string& s,
                     const char delimiter,
                     bool ignore_empty = false)
{
    vector<string> result;
    string tmp = s;

    // Loop through the input string,
    // Split it into substrings at each occurrence of the delimiter character
    // Add each non-empty substring to the output vector if the ignore_empty flag is not set
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

// Function: validate a line of input data to ensure it has correct format
// Param line: the line of data to validate
// Return: true if the line has the correct format, false otherwise

bool isLineValid(string const &line)
{
    // Split the input line into parts using the ';' delimiter.
    vector<string> lineParts = split(line, ';');

    // Check that there are exactly 4 fields in the input line.
    if (lineParts.size() != 4) {
        return false; // wrong number of fields
    }

    // Check that each field in the input line is non-empty.
    for (auto const &part : lineParts) {
        if (part.empty()) {
            return false; // empty field
        }
    }
    return true;
}

// Function: Check if the input file is valid
// Param filename: The name of the input file
// Return: True if the file is valid, False otherwise
bool isFileValid(string const &filename)
{
    // Open the file
    ifstream file(filename);

    // Check if the file could be opened
    if(!file)
    {
        cerr << "Error: input file cannot be opened" <<endl;
        return false;
    }

    // Read each line from the file and check if it is valid
    string line;
    while(getline(file, line))
    {
        if(!isLineValid(line))
        {
            cerr << "Error: empty field" <<endl;
            return false;
        }
    }
    file.close();
    return true;
}

// Function: Read the input file and add books to the library system
//
// Param filename: The name of the input file
// Param allLibraries: A Map of all the libraries in the system
void readFile(string const &filename, MapLibs &allLibraries)
{
    // Open the file
    ifstream file(filename);

    // Read each line from the file and process it
    string line;
    while(getline(file, line))
    {
        // Split the line into parts
        vector<string> lineParts = split(line, ';');

        // Extract the parameters from the line
        string libraryName = lineParts.at(0);
        string author = lineParts.at(1);
        string title = lineParts.at(2);
        int reservations = 0;
        if(lineParts.at(3) != "on-the-shelf")
        {
            reservations = stoi(lineParts.at(3));
        }

        // Add the library to the system if it is not already available
        if(allLibraries.find(libraryName) == allLibraries.end())
        {
            allLibraries.insert({libraryName, Library(libraryName)});
        }

        // Add the book, author, and reservations to the library
        allLibraries.at(libraryName).addBook(author, title, reservations);
    }
    file.close();
}

// Print the names of all libraries in the MapLibs container.
// Param allLibraries: a MapLibs container containing the libraries.
void printLibraries(MapLibs const &allLibraries)
{
    for(MapLibs::const_iterator iter = allLibraries.begin();
        iter != allLibraries.end();
        iter++)
    {
        cout << iter->first << endl;
    }
}

// Compare two pairs of strings to determine which comes first lexicographically.
// Param pair1: a reference to a PairKeyValue object.
// Param pair2: a reference to another PairKeyValue object.
// Return: true if pair1 comes before pair2, false otherwise.
bool comparison(const PairKeyValue &pair1,
                const PairKeyValue &pair2)
{
    if(pair1.first != pair2.first)
    {
        return pair1.first<pair2.first;
    }
    return pair1.second<pair2.second;
}

// Print the books in a library sorted by author.
// Param libraryName: a reference to a Library object.
void printMaterial(Library const &libraryName)
{
    vector<PairKeyValue> flatLib = libraryName.flatDatabase();

    //sort the data in flatLib by author.
    sort(flatLib.begin(), flatLib.end(), comparison);

    // output the sorted book data for each author in the library.
    for(const auto &author_books : flatLib)
    {
        cout << author_books.first << ": " << author_books.second <<endl;
    }
}

// Check if a library name is present in the MapLibs container.
// Param allLibraries: a MapLibs container containing the libraries.
// Param libraryName: the name of the library to check.
// Return: true if the libraryName is present in the container, false otherwise.
bool isLibraryValid(MapLibs allLibraries,
                      string const &libraryName)
{
    bool valid = false;
    for(const auto &key_value_libs : allLibraries)
    {
        if(libraryName == key_value_libs.first) //If libraryName is found in the container.
            valid = true;
    }
    if(valid == true) return true;

    return false;
}

// Check if an author exists in the collections of all libraries.
// Param allLibraries: a map containing all libraries.
// Param authorName: the author name to check.
// Return true if the author exists in the collections of all libraries, false otherwise.
bool isAuthorValid(MapLibs allLibraries,
                   string const &authorName)
{
    bool valid = false;
    for(const auto &key_value_libs : allLibraries)
    {
        //Get the map of books for the current library.
        MapBooks mapBooksGotten = key_value_libs.second.getMapBooks();
        for(const auto &key_value_books : mapBooksGotten)
        {
            // Check if the author name exists in the current library's map of books.
            if(authorName == key_value_books.first)
                valid = true;
        }
    }
    if(valid == true) return true;
    return false;
}

// Print the books written by a specific author in a library.
// Param libraryName: a reference to a Library object.
// Param authorName: the name of the author.
void printBooks(Library const &libraryName,
                string const &authorName)
{
    // Get the books and their number of reservations for the given author.
    vector<PairKeyValue> books_reservations = libraryName.books_reservations(authorName);

    // Sort the books in alphabetical order.
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

// Remove quotes from the input string if it is surrounded by quotes.
// Param stringIncludeQuotes: string that may or may not be surrounded by quotes.
// Returns: string without the surrounding quotes if present,
//      otherwise the original string.
string removeQuotes(string stringIncludeQuotes)
{
    // Check if the first and last character of the string are double quotes.
    if(stringIncludeQuotes.front() != '"'
            && stringIncludeQuotes.back() != '"')
    {
        return stringIncludeQuotes;
    }
    // Find the first and last non-quote character in the string.
    size_t first = stringIncludeQuotes.find_first_not_of('"');
    size_t last = stringIncludeQuotes.find_last_not_of('"');

    // Extract the substring without the surrounding quotes.
    string stringRemoveQuotes = stringIncludeQuotes.substr(first,
                                                           last-first+1);
    return stringRemoveQuotes;
}

// Check if the book is on the shelf or not
// Param: a vector of pairs of strings and integers
//      representing a book's status across multiple libraries.
// Returns a boolean indicating whether the book is available
//      on the shelf in any of the libraries.
bool isOnTheShelf(vector<pair<string,int>> libs_reservations)
{
    for(const auto &pair : libs_reservations)
    {
        if(pair.second == 0)
            return true;
    }
    return false;
}

// Comparison function to sort a vector of pairs
//      containing a library name and its number of book reservations.
//      compares two pairs based on their reservation count and library name.
//      If the reservation counts are different, the pair with the smaller count
//      comes first. If the reservation counts are the same, the pair with the
//      smaller library name comes first.
// Param pair1: the first pair to be compared.
// Param pair2: the second pair to be compared.
// Returns: true if pair1 should come before pair2 in the sorted vector.
bool comparisonForReservations(const pair<string, int> &pair1,
                              const pair<string, int> &pair2)
{
    if(pair1.second != pair2.second)
    {
        return pair1.second<pair2.second;
    }
    return pair1.first<pair2.first;
}

// Find the libraries where a given book is available,
//      calculate the number of reservations for each copy,
//      output the libraries that have the lowest number of
//      reservations or are on the shelf.
// Param allLibraries: a map that contains all the libraries,
//      and for each library, a map of its books and the
//      corresponding vector of books.
// Param reservableAuthorName: a string that represents the author
//      name of the book to be reserved.
// Param reservableBookName: a string that represents the title of
//      the book to be reserved.
void printReservable(MapLibs allLibraries,
                     string const& reservableAuthorName,
                     string const& reservableBookName)
{
    // This vector will store the names of the libraries where the book
    //      can be reserved and the number of reservations for each copy.
    vector<pair<string, int>> libs_reservations;

    // This variable will store the number of reservations for the copy
    //      that has the lowest number of reservations.
    int leastReservations = INT_MAX;

    // This flag is used to check if the book has been found or not.
    bool bookFound = false;

    // Iterate over all the libraries and books to find the given book.
    for (const auto& key_value_libs : allLibraries) {
        MapBooks mapBooksGotten = key_value_libs.second.getMapBooks();
        for (const auto& key_value_books : mapBooksGotten) {
            vector<Book> vector_books = key_value_books.second;
            for (Book bookFinding : vector_books) {

                // If the book is found, calculate the number of reservations
                //      and store it in libs_reservations.
                if (bookFinding.author == reservableAuthorName &&
                        bookFinding.title == reservableBookName) {
                    bookFound = true;
                    int current_reservations = bookFinding.reservations;
                    if (current_reservations < leastReservations) {
                        leastReservations = current_reservations;
                        libs_reservations.clear();
                        libs_reservations.push_back(make_pair(key_value_libs.first,
                                                              leastReservations));
                    } else if (current_reservations == leastReservations) {
                        libs_reservations.push_back(make_pair(key_value_libs.first,
                                                              leastReservations));
                    }
                }
            }
        }
    }

    // Sort the libraries based on the number of reservations.
    sort(libs_reservations.begin(), libs_reservations.end(),
         comparisonForReservations);

    // If the book is not found, output a message and exit the function.
    if (!bookFound) {
        cout << "Book is not a library book" << endl;
        return;
    }

    // If the book cannot be reserved from any library, output a message
    //  and exit the function.
    if (leastReservations == 100) {
        cout << "Book is not reservable from any library" << endl;
        return;
    }

    // If the book can be reserved, output the message "on the shelf"
    //      if there is at least one copy available on the shelf,
    //      and the number of reservations otherwise.
    if (isOnTheShelf(libs_reservations) == true) {
        cout << "on the shelf" << endl;
    } else {
        cout << leastReservations << " reservations" << endl;
    }

    // Output the names of the libraries where the book can be reserved.
    for (const auto& pair : libs_reservations) {
        cout << "--- " << pair.first << endl;
    }
}

// Prints all books that are currently loanable in all libraries,
//      sorted by author name and book title.
//      Keeps track of unique author and book pairs that are loanable
//      using a set, then stores them in a vector for sorting.
//      Finally, loops through the sorted vector and prints out the
//      author name and book title pairs.
// Param allLibraries: map of all libraries and their books.
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

int main()
{
    //initialize the data structures
    MapLibs allLibraries;

    //ask user to input filename
    string filename;
    cout << "Input file: ";
    getline(cin, filename);

    //check if the file file is valid
    //exit the program if the file is invalid
    if(isFileValid(filename) == false)
    {
        return EXIT_FAILURE;
    }

    //read the file
    //put the library data into database
    readFile(filename, allLibraries);

    string userCommand;
    // Run the command line interface until the user quits.
    while(true)
    {
        // Prompt the user for a command.
        cout << "lib> ";

        // Get the user's input command.
        getline(cin, userCommand);

        // Split the command into a vector of strings.
        vector<string> command = split(userCommand, ' ');

        //command = "quit", exit the program.
        if(userCommand == "quit")
            break;

        //command = "libraries", print a list of all libraries.
        else if(userCommand == "libraries")
            printLibraries(allLibraries);

        //command = "material", print a list of all materials in a library.
        else if(command.at(0) == "material")
        {
            // If the library name is invalid, print an error message.
            if(isLibraryValid(allLibraries, command.at(1)) == false)
            {
                cout << "Error: unknown library" <<endl;
            }
            else
            {
                // If the library name is valid, print a list of all materials in the library.
                string materialLibraryName = command.at(1);
                printMaterial(allLibraries.at(materialLibraryName));
            }
        }

        //command = "books", print a list of books by author in a library.
        else if(command.at(0) == "books")
        {
            // If the command has the wrong number of parameters, print an error message.
            if(command.size() != 3)
            {
                cout << "Error: wrong number of parameters" <<endl;
            }

            // If the library name is invalid, print an error message.
            else if(isLibraryValid(allLibraries,command.at(1)) == false)
            {
                cout << "Error: unknown library" <<endl;
            }

            // If the author name is invalid, print an error message.
            else if(isAuthorValid(allLibraries, command.at(2)) == false)
            {
                cout << "Error: unknown author" <<endl;
            }

            else
            {
                // If both the library and author names are valid, print a list of books by author in the library.
                string booksLibraryName = command.at(1);
                string booksAuthorName = command.at(2);
                printBooks(allLibraries.at(booksLibraryName), booksAuthorName);
            }
        }

        //command = "reservable", print a list of books that can be reserved.
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
            reservableBookName = removeQuotes(reservableBookName);

            printReservable(allLibraries, reservableAuthorName, reservableBookName);
        }

        //command = "loanable", print a list of all loanable books.
        else if(command.at(0) == "loanable")
        {
            printLoanable(allLibraries);
        }

        //command is unknown, print an error message.
        else
        {
            cout << "Error: unknown command" <<endl;
        }
    }
    return EXIT_SUCCESS;
}
