#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// Prints the elements in the parameter vector ints.
void print_integers(const vector< int >& ints)
{
    for(auto elem : ints) {
        cout << elem << " ";
    }
    cout << endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.

void read_integers(vector<int>& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(const vector<int>& ints)
{
    if (ints.empty()) return true;
    
    int first_value = ints[0];
    
    for(vector<int>:: size_type i = 1; i < ints.size(); i++)
    {
        if (ints[i] != first_value) return false;
    }
    return true;
}

bool is_ordered_non_strict_ascending(const vector<int>& ints)
{
    for (vector<int> ::size_type i = 1; i < ints.size(); i++)
    {
        if (ints[i-1] > ints[i]) return false;
    }
    return true;
}

bool is_arithmetic_series (const vector<int>& ints)
{
    if (ints.size() < 3) return false;
    int common_difference = ints[1] - ints[0];
    for (vector<int> :: size_type i = 2; i< ints.size(); i++)
    {
        if(ints[i] - ints[i-1] != common_difference) return false;
    }
    return true;
    
}

bool is_geometric_series(const vector<int>& ints)
{
    if (ints.size() <=2) return false;

    if (same_values(ints)) return true;

    int common_ratio = ints[1] / ints[0];

    for (vector<int> :: size_type i = 2; i<ints.size(); i++)
    {
        if (ints[i] / ints[i-1] != common_ratio) return false;
    }
    return true;
}

void triple_integers(vector<int>& ints)
{
    for (int &i : ints) {
        i *= 3;
        //cout << i<< endl;
    }
}

int main()
{
    cout << "How many integers are there? ";
    int how_many = 0;
    cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }
    cout << "Enter the integers: ";
    vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        cout << "All the integers are the same" << endl;
    } else {
        cout << "All the integers are not the same" << endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        cout << "The integers are in a non-strict ascending order" << endl;
    } else {
        cout << "The integers are not in a non-strict ascending order" << endl;
    }

    if(is_arithmetic_series(integers)) {
        cout << "The integers form an arithmetic series" << endl;
    } else {
        cout << "The integers do not form an arithmetic series" << endl;
    }

    if(is_geometric_series(integers)) {
        cout << "The integers form a geometric series" << endl;
    } else {
        cout << "The integers do not form a geometric series" << endl;
    }

    triple_integers(integers);
    cout << "Tripled values: ";
    print_integers(integers);

    return EXIT_SUCCESS;
}

