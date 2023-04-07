#include "animal.hh"

Animal::Animal(): x_(0), y_(0), moving_noise_("")
{

}

Animal::Animal(const string& moving_noise):
    x_(0), y_(0), moving_noise_(moving_noise)
{

}

Animal::~Animal()
{

}
void Animal::move(int x, int y, ostream& output)
{
    x_ = x;
    y_ = y;

    output << moving_noise_ << endl;
}

void Animal::print_location(ostream &output) const
{
    output << "Location: " << x_ << " " << y_ << endl;

}
