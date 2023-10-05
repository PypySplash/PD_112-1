#include <iostream>
using namespace std;

int main() {

    int x = 0, feet = 0, inches = 0, n = 0, t = 0, count = 0;
    // cout << "Enter x: \n";
    cin >> n >> t;
    
    for (int i = 0; i < n; i++) {
        
        cin >> x;
        
        feet = x / 12;

        if (feet >= t)
            count++;
    }
    cout << count << "\n";
}
