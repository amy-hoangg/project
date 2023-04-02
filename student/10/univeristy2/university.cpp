#include "university.hh"
#include <iostream>

University::University(const string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    string code = params.at(0);
    string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        cout << ALREADY_EXISTS << endl;
        return;
    }
    else
    {
        cout << NEW_COURSE << endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        cout << CANT_FIND << code << endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    string full_name = params.at(0);
    int num = 0;
    for ( map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    cout << NEW_ACCOUNT << endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = stoi(params.at(0));
    map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        cout << CANT_FIND << account << endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    string code = params.at(0);
    int account = stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        cout << CANT_FIND << code << endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        cout << CANT_FIND << account << endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    string course_code = params.at(0);
    int account_number = stoi(params.at(1));

    //deal with wrong params
    if (courses_.find(course_code) == courses_.end() )
    {
        cout << CANT_FIND << course_code << endl;
        return;
    }
    else if (accounts_.find(account_number) == accounts_.end() )
    {
        cout << CANT_FIND << account_number << endl;
        return;
    }

    //check graduated
    else if(accounts_.at(account_number)
            ->is_graduated() == true)
    {
        cout << ALREADY_GRADUATED <<endl;
        return;
    }


    else
    {
        accounts_.at(account_number)
                ->register_for_the_course(courses_.at(course_code));
        courses_.at(course_code)
                ->add_student_to_the_course(accounts_.at(account_number));
    }
}

void University::complete(Params params)
{
    string course_code = params.at(0);
    int account_number = stoi(params.at(1));

    //deal with wrong params
    if (courses_.find(course_code) == courses_.end() )
    {
        cout << CANT_FIND << course_code << endl;
        return;
    }
    if (accounts_.find(account_number) == accounts_.end() )
    {
        cout << CANT_FIND << account_number << endl;
        return;
    }

    //deal with exit
    accounts_.at(account_number)
            ->complete_course(courses_.at(course_code));
}

void University::print_signups(Params params)
{
    string course_code = params.at(0);

    if (courses_.find(course_code) == courses_.end() )
    {
        cout << CANT_FIND << course_code << endl;
        return;
    }

    else
    {
        map<string, Course*>::iterator iter
                = courses_.find(course_code);
        iter->second->print_students_in_the_course();
    }
}

void University::print_completed(Params params)
{

}

void University::print_study_state(Params params)
{
    int account_number = stoi(params.at(0));

    if (accounts_.find(account_number) == accounts_.end() )
    {
        cout << CANT_FIND << account_number << endl;
        return;
    }
    else
    {
        map<int, Account*>::iterator iter
                = accounts_.find(account_number);
        iter->second->print_current_and_completed_courses();
    }
}

void University::graduate(Params params)
{

}
