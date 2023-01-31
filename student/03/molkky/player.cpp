#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(const string& name):
    name_(name)
{
}


string Player::get_name()
{
    return name_;
}

void Player::add_points(int pts)
{
    if (points_ + pts > 50)
    {
        points_ = 25;
        cout << name_ <<" gets penalty points!"<<endl;
    }
    else
    {
        points_ += pts;
    }
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    if (points_ == 50)
    {
        has_won_ = true;
    }
    else
    {
        has_won_ = false;
    }
    return has_won_;
}
