// Include libraries
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int main() {
    // The maximum length of input is 1000
    // Since I modify the original input string and the length of the string may exceed 1000
    // So I set the size of array to 5001 to avoid segmentation fault
    char input[5001];
    cin.getline(input, 5001);

    // currentIndex: This variable point to the current index of the string while traversing
    // If we remove a space in front of a punctuation, we need to decrease the currentIndex by 1
    int currentIndex = 0;
    while(currentIndex < strlen(input)) {
        // If we encounter , . !, we check if there is a space in the front and back
        if((input[currentIndex] == ',' || input[currentIndex] == '.' || input[currentIndex] == '!')) { // No space in the front, but space in the back
            // If there is a space in the front, we need to remove it
            if(input[currentIndex-1] == ' ') {
                // Cut the string into two parts and remove the space
                // front: the substring of input from 0 to currentIndex-1
                // back: the substring of input from currentIndex
                // Then we concatenate front and back to get the new input string
                char front[5001];
                strcpy(front, input);

                // Set the space to '\0' to remove it
                front[currentIndex-1] = '\0';
                char back[5001];
                strcpy(back, input+currentIndex);
                strcpy(input, strcat(front, back));

                // currentIndex -- because the front string is now shorter by 1
                currentIndex--; 
            }
            // If this is not the last character of the string, we check if there is a space in the back
            // If there is no space in the back, we need to add one
            if(currentIndex < strlen(input)-1) {
                if(input[currentIndex+1] != ' ') {
                    // Cut the string into two parts and remove the space
                    // front: the substring of input from 0 to currentIndex-1
                    // back: the substring of input from currentIndex
                    // Then we concatenate front and back to get the new input string
                    char front[5001];
                    strcpy(front, input);

                    // Add a space and set the next index to '\0'
                    front[currentIndex+1] = ' ';
                    front[currentIndex+2] = '\0';
                    char back[5001];
                    strcpy(back, input+currentIndex+1);
                    strcpy(input, strcat(front, back));
                }
            }
        }
        else if(input[currentIndex] == '(') {
            // If we encounter (, we check if there is a space in the front and back
            // If there is not a space in the front, we need to add one
            if(input[currentIndex-1] != ' ') {
                // Cut the string into two parts and remove the space
                // Then we concatenate front and back to get the new input string
                char front[5001];
                strcpy(front, input);

                // Add a space and set the next index to '\0'
                front[currentIndex] = ' ';
                front[currentIndex+1] = '\0';
                char back[5001];
                strcpy(back, input+currentIndex);
                strcpy(input, strcat(front, back));
            }
            // If this is not the last character of the string, we check if there is a space in the back
            // If there is a space in the back, we need to remove it
            if(currentIndex < strlen(input)-1) {
                if(input[currentIndex+1] == ' ') {
                    // Cut the string into two parts and remove the space
                    // Then we concatenate front and back to get the new input string
                    char front[5001];
                    strcpy(front, input);

                    // Set the space to '\0' to remove it
                    front[currentIndex+1] = '\0';
                    char back[5001];
                    strcpy(back, input+currentIndex+2);
                    strcpy(input, strcat(front, back));
                }
            }
        }
        else if(input[currentIndex] == ')') { // No space in the front, but space in the back excpet for ). ), )!
            if(input[currentIndex-1] == ' ') {
                // Cut the string into two parts and remove the space
                // Then we concatenate front and back to get the new input string
                char front[5001];
                strcpy(front, input);

                // Set the space to '\0' to remove it
                front[currentIndex-1] = '\0';
                char back[5001];
                strcpy(back, input+currentIndex);
                strcpy(input, strcat(front, back));

                // currentIndex -- because the front string is now shorter by 1
                currentIndex--;
            }
            if(currentIndex < strlen(input)-1) {
                if(input[currentIndex+1] != ' ' && input[currentIndex+1] != ',' && input[currentIndex+1] != '.' && input[currentIndex+1] != '!') {
                    // Cut the string into two parts and remove the space
                    // Then we concatenate front and back to get the new input string
                    char front[5001];
                    strcpy(front, input);

                    // Add a space and set the next index to '\0'
                    front[currentIndex+1] = ' ';
                    front[currentIndex+2] = '\0';
                    char back[5001];
                    strcpy(back, input+currentIndex+1);
                    strcpy(input, strcat(front, back));
                }
            }
        }
        currentIndex++;
    }

    // Output the modified input string
    cout << input << endl;
    return 0;
}