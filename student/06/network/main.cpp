#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using Network = unordered_map<string, vector<string>>;

const string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


vector<string> split(const string& s,
                               const char delimiter,
                               bool ignore_empty = false)
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

void store(string const &marketer, string const &marketee,
           Network &network)
{
    //check if marketer in network
    if(network.find(marketer) == network.end())
        network.insert({marketer, {}});

    //create index for marketee
    if (network.find(marketee) == network.end())
        network.insert({marketee, {}});

    network.at(marketer).push_back(marketee);
}

void print_recursive(string const &id,
                     Network const &network,
                     string const dots = "")
{
    cout << dots << id <<endl;
    //search deeper part of network of this person
    vector<string> recruited_marketers = network.at(id);
    //trivial case if vector is empty
    for (string const &marketer : recruited_marketers)
    {
        print_recursive(marketer, network, dots + "..");
    }
}
int count_recursive(string const &id,
                     Network const &network, int count = 1)
{

    //similar to print, go through subnetworks
    vector<string> recruited = network.at(id);
    for (string const &marketer :recruited)
    {
        count += count_recursive(marketer, network);
    }
    return count;
}

int depth_recursive(string const &id, Network const &network)
{
    vector<string> followers = network.at(id);
        int n=0;
        if (network.at(id).empty())
         {
             return 0;
         }
        for(string const &i :followers)
        {
            int d = depth_recursive(i,network);
            if (d>n)
                n=d;
        }

        return n+1;
}
int main()
{
    Network network;

    while(true)
    {
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id1 = parts.at(1);
            string id2 = parts.at(2);

            store(id1, id2, network);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            print_recursive(id, network);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            cout << count_recursive(id, network, 0) <<endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            int depth_record = depth_recursive(id, network);
            cout << depth_record + 1 <<endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}

