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


/* Module: Utils
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Module for different utilities needed in the program.
 *
 * Note: Students shouldn't need to make changes to this file.
 * */
#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include <string>

using namespace std;

namespace Utils
{
/**
 * @brief split
 * @param str
 * @param delim
 * @return vector containing the parts, no delim chars
 * Splits the given string at every delim char.
 */
vector<string> split(const string& str, char delim = ';');

/**
 * @brief is_empty
 * @param str
 * @return true if given string consists only of empty spaces
 */
bool is_empty(const string& str);

/**
 * @brief is_numeric
 * @param str
 * @return true if given string is numeric
 */
bool is_numeric(const string& str);

/**
 * @brief numeric_part
 * @param str
 * @return numeric sequence from the given string,
 * if no numeric sequence occurs, returns 0
 */
int numeric_part(const string& str);

/**
 * @brief to_lower
 * @param str
 * @return the given string written with lower case letters
 */
string to_lower(const string& str);

}

#endif // UTILS_HH

