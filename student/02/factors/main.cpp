#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int x, i = 0, y = 1, z;

    cout << "Enter a positive number: ";
    cin >> x;

    if (x <= 0){
        cout << "Only positive numbers accepted";
    }


    else {
        z = x;
        while (y < z) {
            i ++;
            if (x % i == 0){
                y = i;
                z = x/y;
            }
        }
        cout << x << " = "<< z << " * "<< y;
    }

    return 0;
}
