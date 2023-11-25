#include <iostream>
#include <string>
#include <cstring>
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

string CurrencyString::getFormattedStr(bool commaSep, bool minusSign)
{
   // implement this function
   string str = to_string(abs(num));  // 取絕對值就可以去掉負號
   int insertPosition = str.length() - 3;
   while (insertPosition > 0)
   {
        if (commaSep) str.insert(insertPosition, ",");
        else str.insert(insertPosition, ".");
        insertPosition -= 3;
   }
   str.insert(0, "$");
   
   if (minusSign && num < 0) str = "-" + str;
   else if (minusSign == 0 && num < 0) str = "(" + str + ")";

   return str;
}

int main() 
{
    int n = 0, c = 0, m = 0;
    cin >> n >> c >> m;
    
    CurrencyString cs(n);
    cout << cs.getFormattedStr(c, m) << endl;
}
