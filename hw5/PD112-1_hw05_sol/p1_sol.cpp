// Include libraries
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

void toLowercase(char str[]) {
    // Convert all characters in str to lowercase
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = tolower(str[i]);
        }
    }
}

int main() {
    // Input, the maximum length of keyword is 100, the maximum length of text is 1000
    // So I set the size of array to 101 and 1001 to store the '\0'
    char keyword[101], text[1001];
    cin.getline(keyword, 101);
    cin.getline(text, 1001);

    // count: the number of keyword in text
    // spaceStart: the start index of space in keyword
    // spaceEnd: the end index of space in keyword
    // keyLen: the length of keyword
    // textLen: the length of text
    // leftBound: the left bound of our searching range
    int count = 0, spaceStart = 0, spaceEnd = 0;
    int keyLen = strlen(keyword), textLen = strlen(text), leftBound = 0;

    // Convert keyword and text to lowercase
    toLowercase(keyword);
    toLowercase(text);

    // Left bound is the first index of keyword in text
    // Whenever we find a keyword in text, we move left bound to the next index of keyword
    while(leftBound < textLen-1) {
        // sub: the substring of text
        // Using strstr() to first find the keyword in text
        char sub[1001];
        char *temp = strstr(text+leftBound, keyword);
        if(temp == NULL) {
            // If we cannot find the keyword in text, we break the loop
            break;
        }
        else {
            // If we find the keyword in text, we move right bound to the next index of keyword
            strcpy(sub, temp);
            // Calculate the index of the occurrence of the keyword in text
            int index = strlen(text+leftBound)-strlen(sub);
            sub[keyLen] = '\0';
            // If the keyword is not a substring of another word, we count it
            if(strcmp(sub, keyword) == 0) {
                count ++;
            }
            // Move left bound to index+1
            leftBound += index+1;
        }
    }
    // Output the number of keyword in text
    cout << count << endl;
    return 0;
}