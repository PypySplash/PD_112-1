#include <iostream>
using namespace std;

int main()
{
  int x = 0, y = 0;
  cin >> x;
  y = x / 12;     // 1 foot = 12 inches, take the floor of the result
  x = x - y * 12; // remainder
  cout << y << "," << x << endl;

  return 0;
}
