/* Program author
 * Name: Hoang Tra My
 * Student number: 151395127
 * UserID: vcmyho
 * E-Mail: my.hoang@tuni.fi
 */

/* Project Name: University
 *
 * Project Description: This program allows users to
     *  manage accounts and courses in a university.
     *  It consists of classes Account, Course, University, Cli,
     *  and Utils module as well as the main program module.
     *  The main program module starts the command line interpreter (CLI)
     *  which allows users to give commands to manage the university.
     *  The program implements six out of the 15 available commands.
 *
 * Modules:
 *
 * Account: Allows users to add new accounts and generates
     * an email address with the suffix tuni.fi for each account.
     * Accounts contain information such as account number, name,
     * contact information, current signups for courses, and passed courses.
 *
 * Course: Allows users to add new courses and contains information
     * such as course code, name, credit points, course staff, and
     * implementations.By default, all courses give five credit points.
 *
 * University: Allows users to manage the university by adding new
     * courses and accounts. Students can sign up for courses and complete them.
     * It contains information about all the courses and persons in the university.
 *
 * Cli: The command line interpreter identifies commands from user input
     * and shows which function in class University implements each command.
 *
 * Utils: Provides utility functions, including the split function.
 *
 * At start and each time the user is expected to give input,
 * the program prints the prompt "Uni>". To this prompt, the user
 * can give commands to manage the university. Commands can be written
 * in upper or lower case, or mixed case. The program's available commands
 * are listed and described in the code.
 */

/* Class: University
 * -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * Class representing a simple university with students, staff and courses.
 *
 * Note: Students shouldn't need to make changes to the existing functions
 * or their implementations.
 * */

#ifndef UNIVERSITY_HH
#define UNIVERSITY_HH

#include "account.hh"
#include "course.hh"
#include "utils.hh"
#include <map>
#include <string>

using namespace std;

const string ALREADY_EXISTS = "Error: Already exists.";
const string ALREADY_GRADUATED = "Error: Student already graduated.";
const string CANT_FIND = "Error: Can't find anything that matches the given string: ";
const string NEW_ACCOUNT = "A new account has been created.";
const string NEW_COURSE = "A new course has been created.";

using Params = const vector<string>&;

using Courses = map<string, Course*>; // <course_code, Course*>
using Accounts = map<int, Account*>;  // <account_number, Account*>

class University
{
public:
    /**
     * @brief University constructor
     * @param email_suffix e.g. "tuni.fi"
     */
    University(const string& email_suffix);

    /**
     * @brief University destructor
     */
    ~University();

    /**
     * @brief new_course
     * @param params: course code, name
     * Adds a new course to the system.
     * If course with given code is found from the system, gives an error.
     */
    void new_course(Params params);

    /**
     * @brief print_courses
     * Prints short info of all courses in the system.
     */
    void print_courses(Params);

    /**
     * @brief print_course
     * @param params: course code
     * Prints longer info of given course.
     * If no course with given code is found, gives an error.
     */
    void print_course(Params params);

    /**
     * @brief new_account
     * @param params: full name
     * Adds a new account to the system.
     * If there's an account in the system with the same full name,
     * a different e-mail address is generated.
     */
    void new_account(Params params);

    /**
     * @brief print_accounts
     * Print all accounts found in the system.
     */
    void print_accounts(Params);

    /**
     * @brief print_account
     * @param params: account number
     * Print single account's info
     * If account is not found from the system, gives an error.
     */
    void print_account(Params params);

    /**
     * @brief add_staff
     * @param params: course code, account number
     * Add staff to the course.
     * If course or account is not found, gives an error.
     */
    void add_staff(Params params);

    /**
     * @brief sign_up
     * @param params: course code, account number
     * Signs up the account on course.
     * If any of the parameters is not found, gives an error.
     */
    void sign_up(Params params);

    /**
     * @brief complete_course
     * @param params: course code, account number
     * Complete the course student has previously signed up on.
     * If any of the parameters is not found, gives an error.
     */
    void complete(Params params);

    /**
     * @brief print_signups
     * @param params: course code
     * Print current signups on a course.
     * If course is not found, gives an error.
     */
    void print_signups(Params params);

    /**
     * @brief print_completed
     * @param params: account number
     * Prints completed courses and total credits of the student.
     * If no account is found, gives an error.
     */
    void print_completed(Params params);

    /**
     * @brief print_study_state
     * @param params: account number
     * Print student's all signups, completed courses and total credits.
     * If no account is found, gives an error.
     */
    void print_study_state(Params params);

    /**
     * @brief graduate
     * @param params: account number
     * Completes all courses account has signed up.
     * After graduation account cannot sign up for any course.
     * If no account is found, gives an error.
     */
    void graduate(Params params);

private:
    Courses courses_; // all courses: map<Course code, Course*>
    Accounts accounts_; // all accounts: map<Account number, Account*>

    // Keeps track of the next account id to be given
    int running_number_;

    string email_suffix_;
};

#endif // UNIVERSITY_HH


