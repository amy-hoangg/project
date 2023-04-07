#include "utils.hh"

vector<string> Utils::split(const string& str, char delim)
{
    vector<string> result = {""};
    bool insideQuotation = false;
    for ( char currentChar : str )
    {
        if ( currentChar == '"' )
        {
            insideQuotation = not insideQuotation;
        }
        else if ( currentChar == delim and not insideQuotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(currentChar);
        }
    }
    return result;
}

bool Utils::is_empty(const string &str)
{
    for ( char ch : str )
    {
        if ( ch != ' ' )
        {
            return false;
        }
    }
    return true;
}

bool Utils::is_numeric(const string& s)
{
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        if( not isdigit(s.at(i)) )
        {
            return false;
        }
    }
    return true;
}

int Utils::numeric_part(const string &s)
{
    string num = "";
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        while ( i < s.size() and isdigit(s.at(i)) )
        {
            num += s.at(i);
            ++i;
        }
    }
    if ( num == "" )
    {
        return 0;
    }
    else
    {
        return stoi(num);
    }
}

string Utils::to_lower(const string &s)
{
    string result = "";
    for ( unsigned int i = 0; i < s.size(); ++i )
    {
        result += tolower(s.at(i));
    }
    return result;
}

