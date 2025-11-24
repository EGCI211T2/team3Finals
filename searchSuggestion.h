#ifndef SEARCHSUGGESTION_H
#define SEARCHSUGGESTION_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <conio.h>

// A simple Trie structure
struct TrieNode {
    std::map<char, TrieNode*> children;
    std::vector<std::string> words; // Store  words ending at this node
};

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

std::string runAutocomplete(std::vector<std::string> dictionary){
    TrieNode* root = new TrieNode();
    for (const std::string& word : dictionary) {
        insertWord(root, word);
    }

    std::string currentInput = "";
    std::cout << "\n" << "Enter text (press Esc to exit): " << std::endl;

    while (true) {
        char c;
        c = _getch();
        //c = tolower(c);

        //detect key inputs
        if (c == 27) { // ESC key
            break;
        } else if (c == '\b' || c == 127) { // Backspace
            if (!currentInput.empty()) {
                currentInput.pop_back();
            }
        } else if (c >= 32 && c <= 126) { // Printable character
            currentInput += c;
        }

        // Clear previous output and display current input
        std::vector<std::string> suggestions;
        std::cout << "\r" << std::string(80, ' ') << "\r"; // Clear line
        std::cout << "Enter text (enter to select): " << currentInput;

        //suggestions handler
        if (!currentInput.empty()) { //generates a list of suggestions
            getSuggestions(root, currentInput, suggestions, 3);
        }

        if(c == 13) { //returns first option in suggestions when ENTER
            if(!currentInput.empty()) {
                return suggestions[0];
            }
        }

        if (!suggestions.empty()) { //prints the list of suggestions
            std::cout << std::endl << "Suggestions: " << std::endl;
            for (const std::string& s : suggestions) {
                std::cout << s << std::endl;
            }
        }
        std::cout << std::flush;
    }
    // Clean up Trie memory (not shown for brevity)
    return "";
}


#endif

