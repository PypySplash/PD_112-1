// Include libraries
#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <cmath>
using namespace std;


int conversion(char input[], int start, int end) {
    // Use the startIndex and endIndex to slice the number string
    char str[1001];
    strcpy(str, input+start);
    str[end-start] = '\0';

    // Convert the number string to integer
    int result = 0;
    for(int i = 0; i < strlen(str); i++) {
        int pow = 1;
        for(int j = 0; j < i; j++) {
            pow *= 10;
        }
        result += (str[strlen(str)-i-1]-'0')*pow;
    }
    return result;
}
int main() {
    // Input, the maximum length of input is 1000 so I set the size of array to 1001 to store the '\0'
    int n;
    char input[1001];
    cin >> n;
    cin.get();
    cin.getline(input, 1001);

    // Record 1. the start index of the number string 2. the end index of the number string
    // idx is the index of the array we use to store the numbers
    int startIndex = 0, endIndex = 0, idx = 0;;
    int *arr = new int[n];
    for(int i = 0; i < strlen(input); i++) {
        if(i < strlen(input)-1) {
            if(input[i] == ',') {
                // If we find a comma, we set the end index to the index before the comma
                endIndex = i;
                // Convert the number string to integer and store it into the array
                int m = conversion(input, startIndex, endIndex);
                arr[idx] = m;
                idx++;
                // Set the start index to the index after the comma
                startIndex = i + 1;
            }
        }
        else {
            endIndex = i+1;
            // Convert the number string to integer and store it into the array
            int m = conversion(input, startIndex, endIndex);
            arr[idx] = m;
            idx++;
        }
    }

    // Use whatever sorting algorithm you want and print out the second largest number
    // Here I use the built-in sort() function in C++
    sort(arr, arr+idx);
    cout << arr[n-2] << endl;
    return 0;
}