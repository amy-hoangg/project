#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int main()
{
    string line = "";
    cout << "Enter a string: ";
    getline(cin, line);
    cout << "Enter the separator character: ";
    char separator = getchar();

    vector< string > parts  = split(line, separator);
    cout << "Splitted string including empty parts: " << endl;
    for( auto part : parts ) {
        cout << part << endl;
    }

    vector< string > parts_no_empty  = split(line, separator, true);
    cout << "Splitted string ignoring empty parts: " << endl;
    for( auto part : parts_no_empty ) {
        cout << part << endl;
    }
}
