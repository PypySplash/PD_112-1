#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int MAX_SENTENCE_LEN = 1001;  // 長度不超過 1000，再加上 "\0"
const int MAX_OUTPUT_LEN = 2001;  // 最壞的情況每個地方都要調整

void stringProcessing(char* input, char* output);

int main()
{
    char input[MAX_SENTENCE_LEN];
    cin.getline(input, MAX_SENTENCE_LEN);
    char output[MAX_OUTPUT_LEN];
    
    stringProcessing(input, output);
    cout << output << "\n";
}

void stringProcessing(char* input, char* output) 
{
    int index = 0;
    char* p = input;
    // 只要 pointer *p 還在句子範圍內
    while (*p != '\0')
    {
        // 處理找到左括號的情況
        if (*p == '(') 
        {
            // 若左括號前方沒有空格，後方有空格
            if (*(p - 1) != ' ' && *(p + 1) == ' ') 
            {
                output[index] = ' ';
                output[index + 1] = *p;
                index++;
                p++;
            }
            // 若左括號前方有空格，後方也有空格
            else if (*(p - 1) == ' ' && *(p + 1) == ' ')
            {
                output[index] = *p;
                p++;
            }
            // 若左括號前方沒有空格，後方也沒有空格
            else if (*(p - 1) != ' ' && *(p + 1) != ' ')
            {
                output[index] = ' ';
                output[index + 1] = *p;
                index ++;
            }
            // 若左括號前方有空格，後方沒有空格
            else if (*(p - 1) == ' ' && *(p + 1) != ' ') {
                output[index] = *p;
            }
            index++;
            p++;
        }
        // 處理遇到其他標點符號的問題
        else if (*p == '.' || *p == ',' || *p == '!' || *p == ')')
        {
            // 若其餘標點符號前面有空格，則刪除空格
            if (*(p - 1) == ' ') {
                index--;
            }
            output[index] = *p;
            index++;
            // 若其餘標點符號後方無空格，則視情況添加
            if (*(p + 1) != ' ') 
            {
                // 要補空格的情況
                if (*(p + 1) != '\0' && (*(p + 1) != '.' && *(p + 1) != ',' && *(p + 1) != '!'))
                {
                    output[index] = ' ';
                    index++;
                }
            }
            p++;
        }
        else 
        {
            output[index] = *p;
            index++;
            p++;
        }
    }
}
