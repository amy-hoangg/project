#include "cli.hh"
#include "utils.hh"
#include <fstream>
#include <sstream>

Cli::Cli(University* university, const string& prompt):
    university_(university),
    prompt_(prompt),
    can_start(university != nullptr)
{
}

bool Cli::exec()
{
    if ( not can_start )
    {
        cout << UNINITIALIZED << endl;
        return false;
    }
    vector<string> input;
    string cmd;
    cout << prompt_ ;
    getline(cin, cmd);
    input = Utils::split(cmd, ' ');
    if ( input.empty() or Utils::is_empty(input.at(0)))
    {
        return true;
    }
    cmd = input.front();
    pop_front(input);
    Cmd* func = find_command(cmd);
    if ( func == nullptr )
    {
        cout << UNKNOWN_CMD << endl;
        return true;
    }
    if ( func->name == "Quit" )
    {
        return false;
    }

    if  ( func->name == "Help" )
    {
        print_help(input);
        return true;
    }

    if ( func->params.size() != input.size() )
    {
        cout << WRONG_PARAMETERS << endl;
        return true;
    }

    if( func->numeric_param_index >= 0 and
        not Utils::is_numeric(input.at(func->numeric_param_index)) )
    {
        cout << NOT_NUMERIC << endl;
        return true;
    }

    if ( func->name == "Read")
    {
        if ( not read_from_file(input.at(0)) )
        {
            cout << FILE_READING_ERROR << endl;
            return false;
        }
        else
        {
            cout << FILE_READING_OK << input.at(0) << endl;
        }
        return true;
    }

    // Call to member func ptr: (OBJ ->* FUNC_PTR)(PARAMS)
    (university_->*(func->func_ptr))(input);
    return true;
}

void Cli::pop_front(vector<string> &vec)
{
    vector<string> result;
    for ( unsigned int i = 1; i < vec.size(); ++i )
    {
        if ( not Utils::is_empty(vec.at(i)) )
        {
            result.push_back(vec.at(i));
        }
    }
    vec = result;
}

Cmd *Cli::find_command(string cmd)
{
    for ( unsigned int i = 0; i < cmd.size(); i++ )
    {
        cmd.at(i) = toupper(cmd.at(i));
    }
    for ( auto command = cmds_.begin(); command != cmds_.end(); command++ )
    {
        for ( auto alias : command->aliases )
        {
            if ( alias == cmd )
            {
                return &(*command);
            }
        }
    }
    return nullptr;
}

void Cli::print_help(const vector<string>& params)
{
    if ( params.size() != 0 )
    {
        print_cmd_info(find_command(params.at(0)), true);
        return;
    }
    for ( Cmd cmd : cmds_ )
    {
        print_cmd_info(&cmd);
    }
}

void Cli::print_cmd_info(Cmd* cmd, bool longer)
{
    cout << cmd->name << " : " ;
    for ( auto alias : cmd->aliases )
    {
        cout << alias << " ";
    }
    cout << endl;
    if ( longer )
    {
        cout << cmd->brief_expl
                  << endl
                  << "Params: " << endl;
        if ( cmd->params.size() == 0 )
        {
            cout << "None." << endl;
        }
        else
        {
            for ( auto param : cmd->params )
            {
                cout << param << endl;
            }
        }
    }
}

bool Cli::read_from_file(const string &filename)
{
    ifstream inputfile(filename);
    if ( not inputfile )
    {
        return false;
    }

    // Redirect the file to cin and save the old cin
    auto cinbuf = cin.rdbuf(inputfile.rdbuf());
    ostringstream unwanted_output;
    auto coutbuf = cout.rdbuf(unwanted_output.rdbuf());

    while( exec() );

    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);
    inputfile.close();

    return true;
}


