#include "square.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const string color[] = {"R", "G", "B", "Y", "W"};

using namespace std;

void initCarpetRandom (Carpet& carpet, int width, int height, int seed)
{
    default_random_engine rand_gen;
    rand_gen.seed(seed);
    uniform_int_distribution<int> colorDist(0, NUMBER_OF_COLORS - 1);
    for (int y = 0; y < height; y++)
    {
        vector<Square> row;
        for (int x = 0; x < width; x++)
        {
            Square new_square(x, y, color[colorDist(rand_gen)], &carpet);
            row.push_back(new_square);
        }
        carpet.push_back(row);
    }
}

void initCarpetFromInput (Carpet& carpet, int width, int height, string input)
{
    int inputIndex = 0;

    for (int y = 0; y < height; y++)
    {
        vector<Square> row;
        for (int x = 0; x < width; x++)
        {
            string color = string( 1, input[inputIndex++]);
            Square new_square(x, y, color, &carpet);
            row.push_back(new_square);
        }
        carpet.push_back(row);
    }
}

void printCarpet (const Carpet& carpet)
{
    for (const auto &row :carpet)
    {
        for (const auto &square :row)
        {
            cout << square.getColor()<<" ";
        }
        cout << endl;
    }
}

bool isValidColor (string color)
{
    for (int i = 0; i < NUMBER_OF_COLORS; i ++)
        if (color == ::color[i]) return true;
    return false;
}

bool isInputValid(string input, int number)
{
    if (int(input.length()) != number)
    {
        cout << " Error: Wrong amount of colors." << endl;
        return false;
    }

    else
    {
        for (int i = 0; i < int(input.length()); i++)
        {
            string current_color = input.substr(i,1);
            if (!isValidColor(current_color))
            {
                cout << " Error: Unknown color." << endl;
                return false;
                break;
            }
        }
        return true;
    }
}

vector<pair<int, int>> searchForMatches(Carpet& carpet, int width, int height, string color)
{
    vector<pair<int, int>> matches;
    for (int y = 0; y < height; y++)
    {
       for (int x = 0; x < width; x++)
       {
           if (y + 2 <= height &&
                   x + 2 <= width &&
                   carpet[y][x].getColor() == string(1, color[0]) &&
                   carpet[y][x+1].getColor() == string(1, color[1]) &&
                   carpet[y+1][x].getColor() == string(1, color[2]) &&
                   carpet[y+1][x+1].getColor() == string(1, color[3]))
               matches.push_back(make_pair(x, y));
       }
    }
    return matches;
}

int main()
{
    //2d vector carpet
    Carpet carpet;
    //**********

    int width, height;
    cout << "Enter carpet's width and height: ";
    cin >> width >> height;

    if (width < 2 || height < 2)
    {
        cout << " Error: Carpet cannot be smaller than pattern." << endl;
        return EXIT_FAILURE;
    }

    string start_choice;
    while (true)
    {
        cout << "Select start (R for random, I for input): ";
        cin >> start_choice;

        transform(start_choice.begin(), start_choice.end(), start_choice.begin(), ::tolower);

        if (start_choice == "r")
        {
            int seed;
            cout << "Enter a seed value: ";
            cin >> seed;

            //********** create carpet ***********
            initCarpetRandom(carpet, width, height, seed);
            printCarpet(carpet);
            //************************************

            break;
        }

        else if (start_choice == "i")
        {
            string color_input;
            cout << "Input: ";
            cin >> color_input;

            if (isInputValid(color_input, int(width * height)) == false)
                continue;

            //********** create carpet ***********
            initCarpetFromInput(carpet, width, height, color_input);
            printCarpet(carpet);
            //************************************
            break;
        }
    }

    string pattern;
    while(true)
    {
        cout << "Enter 4 colors, or q to quit: ";
        cin >> pattern;
        transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);

        if (pattern == "Q")
            break;
        else if (!isInputValid(pattern, 4) && pattern != "q")
            continue;
        else
        {
            vector<pair<int, int>> matches = searchForMatches(carpet, width, height, pattern);
            for (const auto &match : matches)
            {
                    cout << " - Found at (" << match.first + 1 << ", " << match.second + 1 << ")" << endl;
            }
            cout << " = Matches found: " << matches.size() << endl;
        }

    }
    return 0;
}
