#include <iostream>
using namespace std;

int main()
{
  int num = 0, limit = 0;
  cin >> num >> limit;
  limit *= 12; // foot to inch

  int cnt = 0;
  for (int i = 0; i < num; i++)
  { // for each player, check the relation between height and limit
    int height = 0;
    cin >> height;
    if (height >= limit)
      cnt++;
  }

  cout << cnt << endl;

  return 0;
}
