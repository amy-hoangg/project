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

#include "utils.hh"
#include "cli.hh"
#include "university.hh"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

