#include "course.hh"
#include <iostream>

Course::Course(const string& code,
               const string& name,
               int credits):
    course_code_(code),
    name_(name),
    credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        cout << endl;
    }
}

void Course::print_long_info()
{
    cout << "* Course name: " << name_ << endl
              << "* Code: " << course_code_ << endl;
    print_staff();
}

void Course::print_staff()
{
    cout << "* Staff: " << endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0;
          i < course_staff_.size();
          ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            cout << STAFF_EXISTS << endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    cout << STAFF_ADDED << endl;
}

const string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::add_student_to_the_course(Account *new_student)
{
    //check if student alr in the course
    for(unsigned int i = 0;
        i < students_registered_for_the_course_.size();
        i++)
    {
        if(students_registered_for_the_course_.at(i)
                == new_student)
        {
            return;
        }
    }
    students_registered_for_the_course_.push_back(new_student);;
}

void Course::print_students_in_the_course()
{
    for (auto student : students_registered_for_the_course_)
    {
        student->print();
    }
}




