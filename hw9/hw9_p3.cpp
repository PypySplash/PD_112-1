#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

const int MAX_WORDS = 100; // 假定單詞的最大數量

void removeCarriageReturn(string &str) {
    if (!str.empty() && str.back() == '\r') {
        str.pop_back(); // 移除字符串末尾的 '\r'
    }
}

void toLowercase(string &str) {  // 做字串處理，全部改成小寫，較好進行比較
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
}

string replacePunctuationWithSpace(const string &str) {  // 將標點符號改為空格
    string result;
    for (size_t i = 0; i < str.length(); i++) {
        if (ispunct(str[i])) { // 检查是否为标点符号
            result += ' '; // 替换为空格
        } else {
            result += str[i]; // 保持原样
        }
    }
    return result;
}

int main ()
{
    string articleFileName, dicFileName;
    cin.ignore();  // 將檔名前的 / 去掉
    getline(cin, articleFileName);
    cin.ignore();  // 將檔名前的 / 去掉
    getline(cin, dicFileName);

    ifstream dicFile(dicFileName);
    int numWords = 0;
    dicFile >> numWords;
    dicFile.ignore();  // 將換行符去掉
    dicFile.ignore();
    
    string dicWords[MAX_WORDS];
    for (int i = 0; i < numWords; i++) 
    {
        getline(dicFile, dicWords[i]);
        removeCarriageReturn(dicWords[i]); // 移除可能的 '\r'
        toLowercase(dicWords[i]);
    }
    // for (int i = 0; i < numWords; i++)
    // {
    //     cout << dicWords[i] << "\n";
    // }
    dicFile.close();

    char ch;
    string tempWord;

    ifstream articleFile(articleFileName);
    string word;
    int wordCnt = 0;
    bool isEndOfWord = false;

    while (articleFile.get(ch)) {  // 一次 get 一個字母
        if (isalpha(ch)) {  // 若是字母
            if (isEndOfWord) {  // 則檢查上一個單字結束了沒
                tempWord.clear();  // 若結束了，清除 tempWord
                isEndOfWord = false;
            }
            tempWord += tolower(ch);  // 若沒結束，繼續加字母進一個單字裡面
        } 
        else {  // 若不是字母
            isEndOfWord = true;  // 則上一個單字結束
            if (!tempWord.empty()) {  // 若 tempWord 是有效單字，則開始進行檢查是否在 dictionary 裡
                // cout << tempWord << endl;
                for (int i = 0; i < numWords; i++) {
                    if (tempWord == dicWords[i]) {  // 若 tempWord 在 dic 裡：
                        wordCnt++;
                        // cout << "find: " << tempWord << ": " << wordCnt << endl;
                        break;
                    }
                }
                tempWord.clear();
            }
        }
    }
    cout << wordCnt << endl;
    articleFile.close();
}
