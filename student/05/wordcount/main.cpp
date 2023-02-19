#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

vector <string> splitLineIntoWords(const string& line, const string& separator)
{
    vector <string> words;
    string word;
    size_t position = 0;
    size_t last_position = 0;

    //while the position of the separator (starting from position of the last one) is not the end
    while((position = line.find(separator, last_position)) != string::npos)
    {
        word = line.substr(last_position, position - last_position);
        words.push_back(word);
        last_position = position + separator.size(); //increment if for ex separator is :::...
    }
    //The second push_back is necessary to add the last word of the line to the words vector.
    //When the while loop ends, the last word of the line has not been added to the vector yet,
    //since there is no separator after it.
    words.push_back(line.substr(last_position));
    return words;
}

int main()
{
    //get the file name
    string filename;
    cout << "Input file: ";
    cin >> filename;

    //open the file
    ifstream fileObject(filename);

    //check if file open
    if (!fileObject)
    {
        cout << "Error! The file "<< filename <<" cannot be opened.";
        return EXIT_FAILURE;
    }

    //init the datastructure
    string line;
    map <string, set <int>> found_words;
    unsigned int counter = 1; //line always positive

    while(getline(fileObject, line))
    {
        //split line into words
        vector <string> wordsInLine = splitLineIntoWords(line, " ");

        //go through words and pick up any new one
        for (string word : wordsInLine)
        {
            if (found_words.find(word) == found_words.end()) //if cannot find words
            {
                found_words.insert({word, {}}); //{} is empty set
            }
            found_words.at(word).insert(counter); //set.insert(line)
        }
        counter++;
    }

    //print out the results using iterator
    for(map<string, set<int>> ::iterator my_iterator = found_words.begin();
        my_iterator != found_words.end(); my_iterator ++)
    {
        cout << my_iterator->first << " " << (int) my_iterator->second.size()
             << ": ";

        //print individual line numbers
        set<int>::iterator line_number_iter = my_iterator->second.begin();
        while(true)
        {
            cout << *line_number_iter;
            line_number_iter ++;

            //when end exit
            if (line_number_iter == my_iterator->second.end())
            {
                break;
            }
            cout << ", ";
        }
        cout << endl;
    }

    return 0;
}
