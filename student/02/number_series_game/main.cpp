#include <iostream>


int main()
{
    int x;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> x;
    for (int i = 1; i <= x; i++) {
        if (i % 3 == 0 and i % 7 != 0){
            std::cout << "zip"<< "\n";
        }
        else if (i % 7 == 0 and i % 3 != 0) {
            std::cout << "boing"<< "\n";
        }
        else if (i % 3 == 0 and i % 7 == 0) {
            std::cout <<"zip boing"<< "\n";
        }
        else {
            std::cout <<i<< "\n";
        }
    }
    return 0;
}
