#include <iostream>
using namespace std;

int main()
{
  int cnt = 0;
  cin >> cnt; // get the iteration count

  for (int i = 0; i < cnt; i++)
  {
    int s = 0, x = 0, y = 0;
    cin >> s >> x;

    if (s == 0)
    { // case foot to (foot, inch)
      y = x / 12;
      x = x - y * 12;
      cout << y << "," << x << endl;
    }

    if (s == 1)
    { // case inth to foot
      x *= 12;
      cout << x << endl;
    }
  }

  return 0;
}
