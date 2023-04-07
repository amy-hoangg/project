#include <iostream>

#include "owl.hh"
#include "giraffe.hh"
#include "cockatoo.hh"

using namespace std;

int main()
{

    cout << "Owl" << endl;

    Owl owl;
    owl.move(3, 5, cout);
    owl.fly(56, 23, 6, cout);
    owl.print_location(cout);
    owl.print_altitude(cout);
    owl.hoot(cout);


    cout << endl << "Giraffe" << endl;

    Giraffe giraffe;
    giraffe.move(1, 2, cout);
    giraffe.print_location(cout);
    giraffe.suckle(cout);

    cout << endl << "Cockatoo" << endl;

    Cockatoo cockatoo;
    cockatoo.move(23, 57, cout);
    cockatoo.fly(63, 1, 10, cout);
    cockatoo.print_location(cout);
    cockatoo.print_altitude(cout);
    cockatoo.sing(cout);

}
