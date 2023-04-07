#include "mammal.hh"

Mammal::Mammal(): Animal("Kip kop kip kop")
{

}

void Mammal::suckle(ostream &output)
{
    output << "Mus mus" << endl;
}
