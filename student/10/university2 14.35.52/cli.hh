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

/* Class: Cli
 * ----------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * ----------
 * Command line interface example with function pointers.
 *
 * Note: Students shouldn't need to make changes to this file.
 * */
#ifndef CLI_HH
#define CLI_HH

#include "university.hh"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Declare a type of function called.
using MemberFunc = void (University::*)(const vector<string>& params);


// Struct that 'defines' a function.
struct Cmd
{
    vector<string> aliases;
    string name;
    vector<string> params;
    int numeric_param_index;
    string brief_expl;
    MemberFunc func_ptr;
};

// Error strings.
const string UNINITIALIZED = "Error: Given object hasn't been initialized. Stopping.";
const string WRONG_PARAMETERS = "Error: Wrong amount of parameters.";
const string NOT_NUMERIC = "Error: Wrong type of parameters.";
const string UNKNOWN_CMD = "Error: Unknown commands given.";
const string FILE_READING_ERROR = "Error: Can't read given file.";
const string FILE_READING_OK = "Input read from file: ";

class Cli
{
public:
    /**
     * @brief Cli
     * @param university pointer to the university obj the functions are called to
     * @param prompt that is printed before taking in user input
     */
    Cli(University* university, const string& prompt);

    /**
     * @brief exec the cli
     * @return false if execution should end, true if it should continue.
     */
    bool exec();

private:
    /**
     * @brief pop_front
     * @param vec
     * vector utility func that erases the first element of given vector,
     * as well as empty elements.
     *
     * @note All iterators to the container are invalitaded
     */
    void pop_front(vector<string>& vec);

    /**
     * @brief find_command
     * @param cmd
     * @return Cmd pointer if one with given alias is found.
     */
    Cmd* find_command(string cmd);

    /**
     * @brief print_help
     * @param params
     * Generate and print a help, either generic ( no params ) or
     * specific ( func name as param )
     */
    void print_help(const vector<string>& params);

    /**
     * @brief print_cmd_info
     * @param cmd
     * @param longer
     * Print info of a single cmd.
     * if longer == true, print brief and params.
     */
    void print_cmd_info(Cmd *cmd, bool longer = false);

    /**
     * @brief read_from_file
     * @param filename
     * @return false if file could not be read, true otherwise.
     *
     * @note will remove informative output, so even cmds are read, they may
     * not have worked.
     */
    bool read_from_file(const string& filename);

    University* university_;
    string prompt_;
    bool can_start;

    // Vector that stores all cmd info.
    vector<Cmd> cmds_ =
    {
        {{"PRINT_COURSES","PAC"},"Print all courses",{},-1,"Prints all available courses.",&University::print_courses},
        {{"PRINT_ACCOUNTS","PAA"},"Print all accounts",{},-1,"Prints all available accounts.",&University::print_accounts},
        {{"NEW_COURSE","NC"},"Add new course",{"course code","name"},-1,"Adds a new course, if none with param code are found in the system.",&University::new_course},
        {{"PRINT_COURSE","PC"},"Print course",{"course code"},-1,"Print long info of course with given code.", &University::print_course},
        {{"NEW_ACCOUNT","NA"},"Add new account",{"full name"},-1,"Add a new generic account", &University::new_account},
        {{"PRINT_ACCOUNT","PA"},"Print account",{"account number"},0,"Prints account's long info",&University::print_account},
        {{"ADD_STAFF","AS"},"Add staff on course",{"course code","account number"},1,"Adds account with given number to course staff.",&University::add_staff},
        {{"SIGN_UP","S"},"Sign up on a course",{"course code","account number"},1,"Sign account up on a course instance.",&University::sign_up},
        {{"COMPLETE","C"},"Complete a course",{"course code","account number"},1,"Mark a course as completed.",&University::complete},
        {{"GRADUATE","G"},"Graduate",{"account number"},0,"Mark student's all courses completed",&University::graduate},
        {{"PRINT_SIGNUPS","PS"},"Print current signups on a course",{"course code"},-1,"Print all currently active signups on given course, separated by instances",&University::print_signups},
        {{"PRINT_STUDY_STATE","PSS"},"Print student's study state",{"account number"},0,"Print all signups and courses of a given student.",&University::print_study_state},
        {{"PRINT_COMPLETED","PCC"},"Print student's completed courses",{"account number"},0,"Prints short info of al courses the student has completed.",&University::print_completed},
        {{"READ_FROM","RF"},"Read",{"filename"},-1,"Read the database from given file. Does not clear the database.",nullptr},
        {{"HELP","H"},"Help",{"function"},-1,"Prints generic or func specific help.",nullptr},
        {{"QUIT","Q"},"Quit",{},-1,"Quits the program.",nullptr}
    };

};

#endif // CLI_HH


