#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// 移除字串中的標點符號
void removePunctuations(char* str) {
    char* token = strtok(str, "「,.?!:;()-|」");
    char buffer[1000] = {0};
    while (token != nullptr) {
        strcat(buffer, token);
        token = strtok(nullptr, "「,.?!:;()-|」");
    }
    strcpy(str, buffer);
}

// 轉換字串到小寫
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char keyword[100];  // 假定關鍵字的長度不超過 100
    char input[1000];   // 假定輸入的字串長度不超過 1000

    // 輸入關鍵字
    // cout << "請輸入您要查找的關鍵字: ";
    cin.getline(keyword, sizeof(keyword));

    // 輸入目標字串
    // cout << "請輸入目標字串: ";
    cin.getline(input, sizeof(input));

    // 移除目標字串中的標點符號並轉換為小寫
    // removePunctuations(input);
    char* token = strtok(input, "「,.?!:;()-|」");
    char buffer[1000] = {0};
    while (token != nullptr) {
        strcat(buffer, token);
        token = strtok(nullptr, "「,.?!:;()-|」");
    }
    // strcpy(input, buffer);
    
    // toLowerCase(input);
    for (int i = 0; input[i]; i++) {
        input[i] = tolower(input[i]);
    }
    // toLowerCase(keyword);
    for (int i = 0; keyword[i]; i++) {
        keyword[i] = tolower(keyword[i]);
    }

    int count = 0;
    const char* pos = input;

    while ((pos = strstr(pos, keyword)) != nullptr) {
        count++;
        pos++; // 移動到下一個潛在的匹配開始位置
    }
    cout << count << "\n";
    // cout << keyword << " 出現了 " << count << " 次。" << endl;

    return 0;
}
