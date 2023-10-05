#include <iostream>
using namespace std;

int main() {

    int s = 0, x = 0, feet = 0, inches = 0;
    // cout << "Enter x: \n";
    cin >> s >> x;

    if (s == 0)
    {
        feet = x / 12;
        inches = x - 12 * feet;
        cout << feet << "," << inches << "\n";
    }
    if (s == 1)
    {
        inches = x * 12;
        cout << inches << "\n";
    }

}
