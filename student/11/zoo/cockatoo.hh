#ifndef COCKATOO_HH
#define COCKATOO_HH
#include "bird.hh"

using namespace std;

class Cockatoo : public Bird
{
public:
    Cockatoo();
    void sing(ostream &output);
};

#endif // COCKATOO_HH
