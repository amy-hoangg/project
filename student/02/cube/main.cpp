#include <iostream>

using namespace std;

int main()
{
    int x, y;
    cout << "Enter a number: ";
    cin >> x;

    y = x*x*x;
    if (x > 2154) {
        cout<< "Error! The cube of "<<x<<" is not "<<y<<".";
    }
    else {
        cout << "The cube of 2 is " << y << ".";
    }
    return 0;
}
