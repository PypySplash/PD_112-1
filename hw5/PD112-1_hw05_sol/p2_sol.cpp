// Include libraries
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int conversion(char *str, int start, int end) {
    // Use the startIndex and endIndex to slice the number string
    char number[101];
    strcpy(number, str+start);
    number[end-start] = '\0';

    // Convert the number string to integer
    if(strcmp(number, "zero") == 0) return 0;
    else if(strcmp(number, "one") == 0) return 1;
    else if(strcmp(number, "two") == 0) return 2;
    else if(strcmp(number, "three") == 0) return 3;
    else if(strcmp(number, "four") == 0) return 4;
    else if(strcmp(number, "five") == 0) return 5;
    else if(strcmp(number, "six") == 0) return 6;
    else if(strcmp(number, "seven") == 0) return 7;
    else if(strcmp(number, "eight") == 0) return 8;
    else if(strcmp(number, "nine") == 0) return 9;
}

int main() {
    // Input, the maximum length of input is 100 so I set the size of array to 101 to store the '\0'
    char input[101];
    cin.getline(input, 101);

    // Record 1. the start index of the number string 2. the end index of the number string
    int startIndex = 0, endIndex = 0;
    for(int i = 0; i < strlen(input); i++) {
        if(i < strlen(input)-1) {
            if(input[i] == ',') {
                // If we find a comma, we set the end index to the index before the comma
                endIndex = i;
                // Convert the number string to integer and print it out
                cout << conversion(input, startIndex, endIndex) << ",";
                // Set the start index to the index after the comma
                startIndex = i + 1;
            }
        }
        else {
            // If we reach the end of the string, we set the end index to the last index of the string
            endIndex = i+1;
            // Convert the number string to integer and print it out
            cout << conversion(input, startIndex, endIndex) << endl;
        }
    }
    return 0;
}