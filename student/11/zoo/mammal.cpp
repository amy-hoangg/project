#include "mammal.hh"

Mammal::Mammal(): Animal("Mus mus")
{

}

void Mammal::suckle(ostream &output)
{
    output << "Mus mus" << endl;
}
