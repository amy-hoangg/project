#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here
    string str_num = to_string(num);
    if (str_num.length() == 1)
        cout << str_num[0] <<endl;
    else
    {
        cout << str_num[0] <<endl;
        print_vertical(stoi(str_num.substr(1)));
    }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
