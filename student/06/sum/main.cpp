#include <iostream>
#include <string>
#include <vector>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
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

int sum_recursive(vector<int>& v){
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------
    if (v.size() == 0) return 0;
    else if (v.size() == 1) return v[0];
    else
    {
        vector<int> v_rest(v.begin()+1, v.end());
        return v[0] + sum_recursive(v_rest);
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    cout << "Enter integers separated by spaces: ";
    string line;
    getline(cin, line);
    vector<string> strings = split(line, ' ', true);
    vector<int> integers;
    for(const auto& s : strings){
        integers.push_back(stoi(s));
    }

    cout << "Sum: " << sum_recursive(integers) << endl;
}
#endif
