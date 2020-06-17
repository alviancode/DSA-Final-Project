#include <iostream>
#include <string>
#include "trie.h"
#include <chrono>
#include <thread>

#define MAX_WORD_SIZE 100
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

string word, partOfSpeech, meaning;


int main() {
    TrieNode *root = getNode();
    char str[MAX_WORD_SIZE];

    // Array of menu selection
    string funcNames[6] = {"Add word", "Remove word", "Search word", "Edit word", "View all words", "Quit"};
    int selectNumber;

    while (true) {
        cout << endl;
        cout << "\n####################### WORD DICTIONARY #######################\n";
        for (int i = 0; i < 6; i++) {
            cout << (i + 1) << ". " << funcNames[i] << endl;
        }
        cout << "===============================================================" << endl;
        cout << "Select Number: ";
        cin >> selectNumber;
        cin.ignore();
        switch (selectNumber) {

            // If user input number 1
            case 1:
                cout << "Enter new word: ";
                getline(cin, word);
                if (search(root, word)) {
                    cout << "Enter another word!" << endl;
                    sleep_for(seconds(1));
                    break;
                } else {
                    cout << "Part of Speech: ";
                    getline(cin, partOfSpeech);
                    cout << "Enter meaning of the word: ";
                    getline(cin, meaning);
                    insert(root, word, partOfSpeech, meaning);
                    cout << "Success add new word.";
                    sleep_for(seconds(1));
                    break;
                }

                // If user input number 2
            case 2:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    sleep_for(seconds(1));
                    break;
                } else {
                    cout << "Enter word to be deleted: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        remove(root, word);
                        cout << "Success remove word.";
                        sleep_for(seconds(1));
                        break;
                    } else {
                        cout << "Word not found.";
                        sleep_for(seconds(1));
                        break;
                    }
                }

                // If user input number 3
            case 3:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    sleep_for(seconds(1));
                    break;
                } else {
                    cout << "Enter word to search: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        cout << getMeaning(root, word);
                        sleep_for(seconds(1));
                        break;
                    } else {
                        cout << "Word not found.";
                        sleep_for(seconds(1));
                        break;
                    }
                }

                // If user input number 4
            case 4:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    sleep_for(seconds(1));
                    break;
                } else {
                    cout << "Enter word to edit: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        cout << "Enter New Part of Speech: ";
                        getline(cin, partOfSpeech);
                        cout << "Enter New Meaning: ";
                        getline(cin, meaning);
                        edit(root, word, partOfSpeech, meaning);
                        cout << "Success edit word.";
                        sleep_for(seconds(1));
                        break;
                    } else {
                        cout << "Word not found.";
                        sleep_for(seconds(1));
                        break;
                    }
                }

                // If user input number 5
            case 5:
                if (isEmpty(root) == 1) {
                    cout << "\nDictionary is empty!";
                    break;
                } else {
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~ ALL WORDS ~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    view(root, str);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    sleep_for(seconds(1));
                    break;
                }

                // If user input number 6
            case 6:
                cout << "See You Next Time!";
                exit(0);

                // If user input does not match any case
            default:
                cout << "Input is not valid!";
                sleep_for(seconds(1));
                break;
        }
    }
    return 0;
}
