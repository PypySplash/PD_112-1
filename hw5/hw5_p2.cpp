#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAX_STRING_LENGTH = 50;

void checkPair(const char* word);

int main()
{
    char input[MAX_STRING_LENGTH];
    cin.getline(input, MAX_STRING_LENGTH);
    char* word = strtok(input, ",");
    
    while (word != nullptr) 
    {
        checkPair(word);
        word = strtok(nullptr, ",");

        if (word != nullptr) cout << ",";
    }
}

void checkPair(const char* word)
{
    if (strcmp(word, "zero") == 0) cout << 0;
    else if (strcmp(word, "one") == 0) cout << 1;
    else if (strcmp(word, "two") == 0) cout << 2;
    else if (strcmp(word, "three") == 0) cout << 3;
    else if (strcmp(word, "four") == 0) cout << 4;
    else if (strcmp(word, "five") == 0) cout << 5;
    else if (strcmp(word, "six") == 0) cout << 6;
    else if (strcmp(word, "seven") == 0) cout << 7;
    else if (strcmp(word, "eight") == 0) cout << 8;
    else if (strcmp(word, "nine") == 0) cout << 9;
}
