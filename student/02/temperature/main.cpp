#include <iostream>

using namespace std;

int main()
{
    int x;
    double y, z;
    cout << "Enter a temperature: ";
    cin >> x;

    y = x * 1.8 + 32;
    z = (x - 32) / 1.8;
    cout << x <<" degrees Celsius is "<< y << " degrees Fahrenheit" <<endl;
    cout << x <<" degrees Fahrenheit is "<< z << " degrees Celsius" <<endl;

    return 0;
}
