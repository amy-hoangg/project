#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int x, y;
    cout << "Enter a number: ";
    cin >> x;

    y = x*x*x;
    if (y <= -pow(10, 9)) {
        cout<< "Error! The cube of "<<x<<" is not "<<y<<".";
    }
    else if (y >= pow(10, 9)) {
        cout<< "Error! The cube of "<<x<<" is not "<<y<<".";
    }
    else {
        cout << "The cube of 2 is " << y;
    }
    return 0;
}
