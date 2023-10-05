#include <iostream>
using namespace std;

int main() {

    int x = 0, feet = 0, inches = 0;
    // cout << "Enter x: \n";
    cin >> x;
    feet = x / 12;
    inches = x - 12 * feet;
    cout << feet << "," << inches << "\n";

}
