#include <iostream>
using namespace std;

int main() {
    
    int n = 0, w = 0, y = 0;
    // cout << "Enter n, w: \n";
    cin >> n >> w;
    
    for (int i = 0; i < (n - 1); i++) {
        
        cin >> y;

        w -= y;
    }
    cout << w << "\n";
}
