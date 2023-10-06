#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
const int MAX_KEYWORD_LENGTH = 101;
const int MAX_INPUT_LENGTH = 1001;

int main()
{
    char keyword[MAX_KEYWORD_LENGTH];
    char input[MAX_INPUT_LENGTH];
    // 標點符號也可能在 keyword 裡面，故不需要 strtok ，直接用指針開始找即可。
    cin.getline(keyword, MAX_KEYWORD_LENGTH);
    cin.getline(input, MAX_INPUT_LENGTH);

    for (int i = 0; keyword[i]; i++) keyword[i] = tolower(keyword[i]);
    for (int i = 0; input[i]; i++) input[i] = tolower(input[i]);

    int count = 0;
    char* p = strstr(input, keyword);
    while (p != nullptr)
    {
        count++;
        p = strstr(p + 1, keyword);
    }
    cout << count;
}
