#include <iostream>
#include <string>

using namespace std;

bool lower(string s2) {
    for (int i = 0; i < int (s2.length()); i++) {
        if (isupper(s2[i])) {
            return false;
        }
    }
    return true;
}

bool pangram(string s) {
    int arr[26] = {0};

    for (int i = 0; i < int(s.length()); i++) {
        arr[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (arr[i] == 0)
            return false;
    }
    return true;
}

string encryption(string s, string text) {
    for (int i = 0;i< int(text.length()); i++) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int u = alphabet.find(text[i]);
    text.at(i) = s[u];
    }
    return s;
}


int main() {
    string word;
    cout << "Enter the encryption key: ";
    cin >> word;

    if (word.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters.";
        return EXIT_FAILURE;
    }

    else {
        if (lower(word) == false) {
            cout << "Error! The encryption key must contain only lower case characters.";
            return EXIT_FAILURE;
        }

        else {
            if (pangram(word) == false) {
                cout << "Error! The encryption key must contain all alphabets a-z.";
                return EXIT_FAILURE;
            }

            else if (pangram(word) == true) {
                string encrypt;
                cout << "Enter the text to be encrypted: ";
                cin >> encrypt;

                if (lower(encrypt) == false) {
                    cout << "Error! The text to be encrypted must contain only lower case characters.";
                    return EXIT_FAILURE;
                }

                else {
                    string result = encryption(word, encrypt);
                    cout << "Encrypted text: " << result;
                }

            }
        }
    }
    return 0;
}

