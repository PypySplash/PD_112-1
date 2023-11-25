#include <iostream>
#include <string>
using namespace std;

class CurrencyString
{
private:
    int num;
public:
    CurrencyString() : num(0) {}
    CurrencyString(int n) : num(n) {}
    string getFormattedStr(bool commaSep, bool minusSign);
};

string CurrencyString::getFormattedStr(bool commaSep , bool minusSign)
{
    string numStr = to_string(this->num);
    // remove minus sign if number is negative
    if (this->num < 0) 
        numStr.erase(0, 1);
    
    // handle the thousand separator
    string formattedStr = "";
    string separator = (commaSep) ? "," : ".";
    for (int i = 0; i < numStr.length(); i++) {
        if ((i % 3 == 0) && (i > 0)) {
            formattedStr = separator + formattedStr;
        } 
        formattedStr = numStr[numStr.length()-1-i] + formattedStr;
    }

    // adding "$" to the front
    formattedStr = "$" + formattedStr;

    // convert minus sign into corresponding symbol
    if (this->num < 0) {
        if (minusSign) {
            formattedStr = "-" + formattedStr;
        }
        else {
            formattedStr = "(" + formattedStr + ")";
        }
    }
    return formattedStr;
}

int main() {
    int amount = 0;
    bool isCommaSep = 0, isMinusSign = 0;

    cin >> amount >> isCommaSep >> isMinusSign;

    CurrencyString currencyStr(amount);
    string formattedCurrencyStr = currencyStr.getFormattedStr(isCommaSep, isMinusSign);

    cout << formattedCurrencyStr;

    return 0;
}