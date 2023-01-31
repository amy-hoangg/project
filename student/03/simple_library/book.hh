#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <string>

using namespace std;

class Book
{
public:
    Book(const string& title, const string& author, bool loan_or_not = false);

    void loan(Date day_loan);
    void renew();
    void give_back();
    void print();

private:
    string title_;
    string author_;
    bool loan_or_not_;
    Date loaning_date_;
    Date due_date_;

};


#endif // BOOK_HH
