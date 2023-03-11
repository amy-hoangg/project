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

    return EXIT_SUCCESS;
}
