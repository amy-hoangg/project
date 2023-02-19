#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstddef>

using namespace std;

int main()
{
    string filename;
    cout << "Input file: ";
    cin  >> filename;

    ifstream fileObject(filename);

    if(!fileObject)
    {
        cout << "Error! The file "<<filename<<" cannot be opened.";
        return EXIT_FAILURE;
    }
    else
    {
        string line;
        string player;
        double points;

        map<string, double> info;

        map<string, double>::iterator my_iterator;


        while (getline(fileObject, line))
        {
            size_t separator_index = line.find(":");
            player = line.substr(0, separator_index);
            points = stoi(line.substr(separator_index+1));

            info[player] = points;
        }

        cout << "Final scores: "<<endl;
        for (my_iterator = info.begin(); my_iterator != info.end(); my_iterator++)
        {
            cout << my_iterator ->first <<": " <<my_iterator -> second<< endl;
        }
    }
    return 0;
}

