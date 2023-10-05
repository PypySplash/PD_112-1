#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
const int CNT = 100;
const int MAX_PASSAGE_LEN = 1000;
const int MAX_KEYWORD_LEN = 100;

int main()
{
    char keyword[MAX_KEYWORD_LEN];
    cin >> keyword;

    char delim[] = ",.?!:;()-|";
    char word[CNT][MAX_KEYWORD_LEN] = {0};
    int wordCnt = 0;

    char a[MAX_PASSAGE_LEN];
    cin >> a;

    char* start = strtok(a, delim);
    while (start != nullptr)
    {
        strcpy(word[wordCnt], start);
        wordCnt++;
        start = strtok(nullptr, delim);
    }

    for (int i = 0; i < wordCnt; i++)
        cout << word[i] << "";

    // char* p = strstr(a, keyword);
    char* p = strstr(a, "apple");
    int count = 0;

    while (p != nullptr) 
    {
        *p = 'A';
        *(p+1) = 'P';
        // cout << count << "\n";
        // count++;
        p = strstr(p, keyword);
    }
    // cout << a;
    // cout << count << "\n";

    delete [] p;
    p = nullptr;
}