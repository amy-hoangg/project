#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    minstd_rand generator;

    cout << "Enter some text. Quit by entering the word \"END\"." << endl;
    string word;

    while (cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            if (word.length() != 1){
               shuffle(word.begin()+1, word.end()-1, generator);
            }
        }
	
        cout << word << endl;
    }
}
