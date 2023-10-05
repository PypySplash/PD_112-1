#include <iostream>
using namespace std;

int main()
{
  int num = 0, limit = 0;
  cin >> num >> limit;
  limit *= 12; // foot to inch

  int cntOne = 0, cntTwo = 0, cntThree = 0; // create three counter for three positions
  for (int i = 0; i < num; i++)
  { // for each player, check the relation between height and limit and modify the corresponding counter
    int height = 0, position = 0;
    cin >> height >> position;

    if (height >= limit)
    {
      if (position == 1)
        cntOne++;
      else if (position == 2)
        cntTwo++;
      else
        cntThree++;
    }
  }

  cout << cntOne << "," << cntTwo << "," << cntThree << endl;

  return 0;
}
