#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

void stringProcessing(char* input, char* output);

int main()
{
    char input[2000];
    cin.getline(input, 2000);
    char output[2000];
    
    stringProcessing(input, output);

    cout << output << "\n";

    return 0;
}

void stringProcessing(char* input, char* output) 
{
    int index = 0;
    char* p = input;
    int count = 0;
    while (*p != '\0')
    {
        if (*p == '(') 
        {
            // 若左括號 ( 前方沒有空格，則空一格
            if (*(p - 1) != ' ' && *(p + 1) == ' ') 
            {
                output[index] = ' ';
                output[index + 1] = *p;
                index += 2;
                p++;
            }
            else if (*(p - 1) == ' ' && *(p + 1) == ' ')
            {
                output[index] = *p;
                index++;
                p++;
            }
            else if (*(p - 1) != ' ' && *(p + 1) != ' ')
            {
                output[index] = ' ';
                output[index + 1] = *p;
                index += 2;
            }
            else if (*(p - 1) == ' ' && *(p + 1) != ' ')
            {
                output[index] = *p;
                index++;
            }
            // 若左括號 ( 後方是空格，則 p 會多跳過一格
            p++;
        }
        else if (*p == '.' || *p == ',' || *p == '!' || *p == ')')
        {
            // 若其餘標點符號前面有空格，則刪除空格
            if (*(p - 1) == ' ') 
                index--;
            output[index] = *p;
            index++;
            // 若其餘標點符號後方無空格，則視情況添加
            if (*(p + 1) != ' ') 
            {
                // 要補空格的情況
                if (*(p + 1) != '\0' && ((*(p + 1) != '.') && (*(p + 1) != ',') && (*(p + 1) != '!') && (*(p + 1) != ')') ))
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
        if (*(p+1) == '\0')
        {
            output[index] = '\0';
        }
    }
}
