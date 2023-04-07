#ifndef GIRAFFE_HH
#define GIRAFFE_HH
#include "mammal.hh"

using namespace std;

class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(ostream &output);
};

#endif // GIRAFFE_HH
