#ifndef ANIMAL_HH
#define ANIMAL_HH

#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    //Animal o day co 2 cai constructor lien
    Animal();
    Animal(const string& moving_noise);

    //this is base class so it should have virtual structure
    virtual ~Animal();

    void move(int x, int y, ostream& output);
    void print_location(ostream& output) const;

private:
    //this will not be inherited
    int x_;
    int y_;
    string moving_noise_;

};

#endif // ANIMAL_HH
