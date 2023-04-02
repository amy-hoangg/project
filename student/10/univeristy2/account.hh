
/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 * */

#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Course;

const string NO_SIGNUPS = "No signups found on this course.";
const string SIGNED_UP = "Signed up on the course.";
const string COMPLETED = "Course completed.";
const string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const string& full_name, int account_number, int duplicates,
            const string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief Registers a new course for the student
     * @param new_registered_course pointer to the
     * new course being registered
    */
    void register_for_the_course(Course *new_registered_course);

    /**
    * @brief Marks a course as completed by the student
    * @param new_completed_course pointer to the course
    * being completed
    */
    void complete_course(Course *new_completed_course);

    /**
    * @brief Prints the list of currently registered
    * and completed courses for the student
    */
    void print_current_and_completed_courses();

    /**
    * @brief Prints the list of completed courses for the student
    */
    void print_completed_courses();

    /**
    * @brief Marks the student as graduated
    */
    void make_graduate();

    /**
    * @brief Checks if the student has graduated
    * @return true if the student has graduated, false otherwise
    */
    bool is_graduated();

private:
    string full_name_;
    string last_name_;
    string first_name_;
    string email_;
    const int account_number_;
    vector<Course*> registered_courses_;
    vector<Course*> completed_courses_;
    bool is_graduated_ = false;
};

#endif // ACCOUNT_HH


