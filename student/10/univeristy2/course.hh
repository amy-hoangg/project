

/* Class: Course
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a single course, with name and code, staff and students.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 * */

#ifndef COURSE_HH
#define COURSE_HH

#include "account.hh"
#include <string>
#include <vector>

using namespace std;

const string STUDENT_ADDED = "A new student has been added.";
const string STAFF_ADDED = "A new staff member has been added.";
const string STAFF_EXISTS = "Error: Staff member already added on this course.";
const string STUDENT_EXISTS = "Error: Student already added on this course.";
const string STUDENT_COMPLETED = "Error: Student already completed this course.";


class Course
{
public:
    /**
     * @brief Course
     * @param code unique code for the course, used as id
     * @param name
     * @param credits
     */
    Course( const string& code, const string& name, int credits = 5);

    /**
     * @brief Course destructor
     */
    ~Course();

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, pring also a newline
     * at the end.
     */
    void print_info(bool print_new_line);

    /**
     * @brief print_long_info
     * Print longer course info with staff.
     */
    void print_long_info();

    /**
     * @brief print_staff
     * Print all staff of the course.
     */
    void print_staff();

    /**
     * @brief add staff
     * @param new_staff
     * Add a staff member to course.
     */
    void add_staff(Account* new_staff_member);

    /**
     * @brief get_code
     * @return the course code.
     */
    const string get_code() const;

    /**
     * @brief get_credits
     * @return the amount of credits this course is valued.
     */
    int get_credits() const;

    /**
    * @brief Adds a new student to the course
    * @param new_student pointer to the Account of
    * the new student being added
    */
    void add_student_to_the_course(Account *new_student);

    /**
    * @brief Prints the list of students currently
    * registered in the course
    */
    void print_students_in_the_course();

private:
    string course_code_;
    string name_;
    int credits_;
    vector<Account*> course_staff_;
    vector<Account*> students_registered_for_the_course_;
};

#endif // COURSE_HH


