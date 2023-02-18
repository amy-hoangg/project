#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string fileInput = "";
    string fileOutput = "";

    cout << "Input file: ";
    getline(cin, fileInput);

    cout << "Output file: ";
    getline(cin, fileOutput);

    ifstream inputFile(fileInput);
    if (!inputFile)
    {
        cout << "Error! The file "<< fileInput << " cannot be opened.";
        return EXIT_FAILURE;
    }

    ofstream outputFile(fileOutput);
    string line;
    int lineNumber = 1;

    while (getline(inputFile, line))
    {
        outputFile<<lineNumber<<" "<<line<<endl;
        lineNumber++;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
