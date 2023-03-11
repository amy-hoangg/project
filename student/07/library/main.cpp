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
    while(true)
    {
        cout << "lib> ";
        getline(cin, userCommand);

        //split command
        vector<string> command = split(userCommand, ' ');

        //command = quit
        if(userCommand == "quit")
            break;

        //command = libraries
        else if(userCommand == "libraries")
            printLibraries(allLibraries);

        //command = material
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

        //command = book
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
    }
    return EXIT_SUCCESS;
}
