#include <iostream>
using namespace std;

int main() {
    
    int n = 0, w = 0, y = 0, x = 0;
    
    // cout << "Enter n, w: \n";
    cin >> n >> w;

    int* xArray = new int[n - 1];
    int* yArray = new int[n - 1];
    
    for (int i = 0; i < (n - 1); i++) {
        cin >> x;
        xArray[i] = x;
    }

    for (int i = 0; i < (n - 1); i++) {
        cin >> y;
        yArray[i] = y;
        w += xArray[i];
        w -= yArray[i]; 
    }

    cout << w << "\n";
}
