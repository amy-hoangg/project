#include "book.hh"
#include <iostream>
#include <string>

using namespace std;

Book::Book(const string& title, const string& author, bool loan_or_not):
    title_(title), author_(author), loan_or_not_(loan_or_not)
{
}

void Book::loan(Date day_loan)
{
    if (loan_or_not_ == true)
    {
        cout <<"Already loaned: cannot be loaned"<<endl;
    }
    else
    {
        loan_or_not_ = true;
        loaning_date_ = day_loan;
        due_date_ = day_loan;
        due_date_.advance(28);
    }
}

void Book::renew()
{
    if (loan_or_not_ == true)
    {
        due_date_.advance(28);
    }
    else
    {
        cout << "Not loaned: cannot be renewed"<<endl;
    }
}

void Book::give_back()
{
    if (loan_or_not_ == true)
    {
        loan_or_not_ = false;
    }
    else
    {

    }
}

void Book::print()
{
    cout << title_<< " : "<<author_<<endl;
    if (loan_or_not_ == false)
    {
        cout << "- available"<<endl;
    }
    else
    {
        cout <<"- loaned: ";
        loaning_date_.print(); //no da cho iostream
        cout <<"- to be returned: ";
        due_date_.print();
    }
}


