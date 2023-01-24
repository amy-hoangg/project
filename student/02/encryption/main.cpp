#include <iostream>
#include <string>

using namespace std;

bool lower(string s2) {
    for (int i = 0; i < s2.length(); i++) {
        if (isupper(s2[i])) {
            return false;
        }

        else {
            return true;
        }
    }
}

bool pangram(string s) {
    int arr[26] = {0};

    for (int i = 0; i < s.length(); i++) {
        arr[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (arr[i] == 0)
            return false;
    }
    return true;
}

string encryption(string s, string key) {
    for (int i = 0; i < s.length(); i++) {
        s[i] ^= key[i%key.length()];
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

            else if (pangram(word) == false) {
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
}

