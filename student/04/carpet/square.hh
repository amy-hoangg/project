#ifndef SQUARE_HH
#define SQUARE_HH


#include <vector>
#include <iostream>

using namespace std;


class Square;
using Carpet = vector<vector<Square>>;


class Square
{
public:
    Square(int x, int y, string color, Carpet* carpet);
    ~Square();

    string getColor() const;

private:
    int x_;
    int y_;
    string color_;

    Carpet* carpet_;
};

#endif // SQUARE_HH
