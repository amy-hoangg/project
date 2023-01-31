#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

void Account::set_credit_limit(int money)
{
    if (has_credit_ == false)
    {
        cout << "Cannot set credit limit: the account has no credit card";
        cout << endl;
    }
    else
    {
        credit_limit_ = money;
    }
}

void Account::save_money(int money)
{
    balance_ += money;
}

void Account::take_money(int money)
{
    if (has_credit_ == false)
    {
        if (balance_ < money)
        {
            cout << "Cannot take money: balance underflow";
            cout << endl;
        }
        else
        {
            balance_ -= money;
            cout << money <<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros";
            cout << endl;
        }
    }
    else
    {
        if (balance_ < credit_limit_)
        {
            cout << "Cannot take money: credit limit overflow";
            cout << endl;
        }
        else
        {
            balance_ -= money;
            cout << money <<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros";
            cout << endl;
        }
    }
}

void Account::transfer_to(Account &account, int money)
{
    if (has_credit_ == false)
    {
        if (balance_ < money)
        {
            cout << "Cannot take money: balance underflow"<<endl;
            cout << "Transfer from "<<iban_<<" failed";
            cout << endl;
        }
        else
        {
            balance_ -= money;
            account.balance_ += money;
            cout << money <<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros";
            cout << endl;
        }
    }
    else
    {
        if (credit_limit_ < -(balance_ - money))
        {
            cout << "Cannot take money: credit limit overflow"<<endl;
            cout << "Transfer from "<<iban_<<" failed";
            cout << endl;
        }
        else
        {
            balance_ -= money;
            account.balance_ += money;
            cout << money <<" euros taken: new balance of "<<iban_<<" is "<<balance_<<" euros";
            cout << endl;
        }
    }
}

void Account::print() const
{
    cout << owner_ <<" : "<< iban_ <<" : "<<balance_<<" euros \n";
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        cout << "Too many accounts" << endl;
    }
    suffix.append(to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
