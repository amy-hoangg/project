#ifndef CHICKEN_HH
#define CHICKEN_HH
#include"bird.hh"

using namespace std;

class Owl: public Bird
{
public:
    Owl();
    void hoot(ostream& output) const;

};

#endif // CHICKEN_HH
