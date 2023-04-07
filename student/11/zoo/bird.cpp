#include "bird.hh"


Bird::Bird(): Animal("Flap flap")
{

}

void Bird::print_altitude(ostream &output) const
{
    output << "Altitude: " << z_ << endl;
}

void Bird::fly(int x, int y, int z, ostream& output)
{
    move(x, y, output);
    z_ = z;
}
