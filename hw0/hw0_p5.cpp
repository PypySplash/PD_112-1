#include <iostream>
using namespace std;

int main() {

    int x = 0, feet = 0, inches = 0, n = 0, t = 0, p = 0;
    int guardCount = 0, forwardCount = 0, centerCount = 0;
    // cout << "Enter x: \n";
    cin >> n >> t;
    
    for (int i = 0; i < n; i++) {
        
        cin >> x >> p;
        
        feet = x / 12;

        if (feet >= t && p == 1)
            guardCount++;
        if (feet >= t && p == 2)
            forwardCount++;
        if (feet >= t && p == 3)
            centerCount++;
    }
    cout << guardCount << "," << forwardCount << "," << centerCount << "\n";
}
