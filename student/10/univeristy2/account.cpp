#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>

Account::Account(const string& full_name,
                 int account_number,
                 int duplicates,
                 const string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    vector<string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << endl;
}

string Account::get_email() const
{
    return email_;
}

string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

void Account::register_for_the_course(Course *new_registered_course)
{
    //already registered
    for(unsigned int i = 0;
        i<registered_courses_.size();
        i++)
    {
        if(registered_courses_.at(i)
                == new_registered_course)
        {
            cout << STUDENT_EXISTS <<endl;
            return;
        }
    }

    //already completed
    for(unsigned int i = 0;
        i<completed_courses_.size();
        i++)
    {
        if(completed_courses_.at(i)
                == new_registered_course)
        {
            cout << STUDENT_COMPLETED <<endl;
            return;
        }
    }

    //registered sucessfully
    registered_courses_.push_back(new_registered_course);
    cout << SIGNED_UP <<endl;
}

void Account::complete_course(Course *new_completed_course)
{
    //check completed
    auto iter1 = find(completed_courses_.begin(),
                      completed_courses_.end(),
                      new_completed_course);

    //not completed
    if(iter1 == completed_courses_.end())
    {
        auto iter2 = find(registered_courses_.begin(),
                         registered_courses_.end(),
                         new_completed_course);

        //not registered
        if(iter2 == registered_courses_.end())
        {
            cout << NO_SIGNUPS <<endl;
            return;
        }

        //registered
        else
        {
            cout << COMPLETED <<endl;
            completed_courses_
                    .push_back(new_completed_course);
            registered_courses_
                    .erase(iter2);
        }
    }

    //completed
    else
    {
        cout << NO_SIGNUPS <<endl;
        return;
    }
}

void Account::print_current_and_completed_courses()
{

}

void Account::print_completed_courses()
{

}

void Account::make_graduate()
{

}

bool Account::is_graduated()
{

}


