#ifndef BIRD_HH
#define BIRD_HH
#include "animal.hh"

using namespace std;

class Bird: public Animal
{
public:
    Bird();
    void fly(int x, int y, int z, ostream& output);
    void print_altitude(ostream& output) const;

private:
    int z_;


};

#endif // BIRD_HH
