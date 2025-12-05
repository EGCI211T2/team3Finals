#ifndef SEARCHSUGGESTION_H
#define SEARCHSUGGESTION_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

// A simple Trie structure
struct TrieNode {
    std::map<char, TrieNode*> children;
    std::vector<std::string> words; // Store  words ending at this node
};

void clearscreen()
{
        // Clear the screen based on the operating system
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Unix-like systems (Linux, macOS)
        system("clear");
    #endif
}

// Function to insert a word into the Trie
void insertWord(TrieNode* root, const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->words.push_back(word); // Add the complete word
}

// Function to get suggestions based on a prefix
void getSuggestions(TrieNode* root, const std::string& prefix, std::vector<std::string>& suggestions, int maxSuggestions) {
    TrieNode* current = root;
    for (char c : prefix) {
        if (current->children.find(c) == current->children.end()) {
            return; // Prefix not found
        }
        current = current->children[c];
    }

    // Recursively collect words from this node and its children
    std::function<void(TrieNode*)> collectWords = [&](TrieNode* node) {
        for (const std::string& word : node->words) {
            if (suggestions.size() < maxSuggestions) {//checks if there not more than max suggestions
                suggestions.push_back(word);
            } else {
                return;
            }
        }
        for (auto const& [key, val] : node->children) {
            if (suggestions.size() < maxSuggestions) {
                collectWords(val);
            } else {
                return;
            }
        }
    };
    collectWords(current);
}

void deleteTrie(TrieNode* node) { // deconstructor
    if (!node) return;

    for (auto& [ch, child] : node->children) {
        deleteTrie(child);
    }

    delete node;
}


std::string runAutocomplete(std::vector<std::string> dictionary){
    TrieNode* root = new TrieNode();
    for (const std::string& word : dictionary) {
        insertWord(root, word);
    }

    std::string currentInput = "";
    std::cout << "\n\n=== Trash Search ===\n";
    std::cout << "Enter trash name (press Esc to exit): " << std::endl;

    #ifndef _WIN32
    // Set terminal to raw mode for non-blocking input on Linux/macOS
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    #endif

    while (true) {
        char c;
        #ifdef _WIN32
            c = _getch();
        #else
            read(STDIN_FILENO, &c, 1);
        #endif

        //detect key inputs
        if (c == 27) { // ESC key
            clearscreen();
            cout << "Searching finished." << endl;
            break;
        } else if (c == '\b' || c == 127) { // Backspace
            if (!currentInput.empty()) {
                currentInput.pop_back();
            }
        } else if (c >= 32 && c <= 126) { // Printable character
            currentInput += c;
        }

        // Clear previous output and display current input

        clearscreen();

        std::vector<std::string> suggestions;
        std::cout << "\r" << std::string(80, ' ') << "\r"; // Clear line
        std::cout << "===Trash search===" << endl << "Enter trash name (enter to select and ESC to exit):\n " << currentInput;

        // suggestions handler
        if (!currentInput.empty()) { // generates a list of suggestions
            getSuggestions(root, currentInput, suggestions, 3);
        } 

        if (suggestions.empty()) {
            std::cout << endl << "No matches found for \"" << currentInput << "\". Try again.\n";
        }

        if(c == '\n' || c == 13) { // returns first option in suggestions when ENTER
            if(!currentInput.empty() && !suggestions.empty()) {
                clearscreen();
                cout << endl << suggestions[0] << " is added to your list.";
                return suggestions[0];
            } else {
                std::cout << endl << "Invalid input, try again" << endl;
                currentInput = "";
                continue;
            }
        }

        if (!suggestions.empty()) { // prints the list of suggestions
            std::cout << std::endl << "Suggestions: " << std::endl;
            for (const std::string& s : suggestions) {
                std::cout << s << std::endl;
            }
        }
        std::cout << std::flush;
    }

    // house keeping
    #ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore terminal mode
    #endif

    deleteTrie(root);
    return "";
}


#endif


