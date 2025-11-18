#include <iostream>
#include "searchSugesstion.h"

int main() {
    //converting string arr to vector
    std::string stringArr[] = {"plastic", "paper", "plastic bag", "banana"}; //for compatability (this an example)
    int arraySize = sizeof(stringArr)/sizeof(stringArr[0]); 
    std::vector<std::string> dictionary(stringArr, stringArr + arraySize); //range constructor

    //searchSuggestion
    std::string input = runAutocomplete(dictionary); //this junk uses vectors not string arrays

    std::cout << "\n" << input << std::endl;
    return 0;
}
