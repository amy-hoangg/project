#include <iostream>

using namespace std;

long int factorial(long int num) {
    long int fact = 1;
    for(long int i = 1; i <= num; i++) {
        fact = fact * i;
    }
    return fact;
}

long int probability(long int t, long int d) {
    long int pro;
    pro = factorial(t)/(factorial(t-d)*factorial(d));
    return pro;
}

int main() {
    long int total, drawn;

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
