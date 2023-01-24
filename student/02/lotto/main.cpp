#include <iostream>

using namespace std;

unsigned int factorial(unsigned int num) {
    int fact = 1;
    for(unsigned int i = 1; i <= num; i++) {
        fact = fact * i;
    }
    return fact;
}

int probability(int t, int d) {
    int pro;
    pro = factorial(t)/(factorial(t-d)*factorial(d));
    return pro;
}

int main() {
    int total, drawn;

    cout << "Enter the total number of lottery balls: ";
    cin >> total;

    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    if (drawn <= 0 or total <= 0) {
        cout << "The number of balls must be a positive number.";
    }
    else {
        cout << "The probability of guessing all "<<drawn<<" balls correctly is 1/" << probability(total, drawn)<<".";
    }
    return 0;
}
