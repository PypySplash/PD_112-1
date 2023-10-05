#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char str[1001];
    char result[2000];
    // cout << "請輸入字串: ";
    cin.getline(str, 1001);

    // formatString(str, result);
    int j = 0;
    char* point = str;
    while (*point) {
        if (*point == '(') {
            if (j > 0 && result[j - 1] != ' ') {
                result[j++] = ' ';
            }
            result[j++] = *point;
        } 
        else if (*point == '.' || *point == ',' || *point == '!' || *point == ')') {
            // 移除前方不必要的空格
            if (j > 0 && result[j - 1] == ' ') {
                j--;
            }
            result[j++] = *point;

            if (*(point + 1) && *(point + 1) != '.' && *(point + 1) != ',' && *(point + 1) != '!' && *(point + 1) != ')' && *(point + 1) != ' ') {
                result[j++] = ' ';
            }
        } 
        else {
            result[j++] = *point;
        }
        point++;
    }
    
    result[j] = '\0';

    // cout << "格式化後的字串: " << result << endl;
    cout << result;

    return 0;
}
