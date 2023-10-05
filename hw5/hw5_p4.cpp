#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
const int CNT = 100;
const int WORD_LEN = 50;
const int SEN_LEN = 200;

int main() 
{
    int n = 0, wordCnt = 0;
    cin >> n;

    char num[SEN_LEN];
    char word[CNT][WORD_LEN] = {0};
    cin >> num;

    char* start = strtok(num, ",");
    while (start != nullptr) 
    {
        strcpy(word[wordCnt], start);
        wordCnt++;
        start = strtok(nullptr, ",");
    }

    int* temp = new int [n];
    for (int i = 0; i < wordCnt; i++) 
        temp[i] = atoi(word[i]);  // atoi, stoi 在這個 case 都可以

    int maxNumber = 0;
    for (int i = 0; i < wordCnt; i++) 
    {
        if (maxNumber < temp[i]) 
            maxNumber = temp[i];
    }
    
    int secondMaxNumber = 0;
    for (int i = 0; i < wordCnt; i++) 
    {
        if (secondMaxNumber < temp[i] && temp[i] != maxNumber)
            secondMaxNumber = temp[i];
    }
    cout << secondMaxNumber << "\n";
    
    delete [] temp;
    temp = nullptr;

    return 0;
}
