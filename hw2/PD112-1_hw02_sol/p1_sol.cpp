#include <iostream>
using namespace std;

const int MAX_STATION_NUM = 20;

int main(){

    int stationNum = 0, initPass = 0, maxPass = 0;
    cin >> stationNum >> initPass >> maxPass;
    
    int onCar = initPass;

    // getInPass[i] is the number of passengers geting on the bus at station i 
    // getOutPass[i] is the number of passengers geting off the bus at station i

    int getInPass[MAX_STATION_NUM] = {0};  // DO NOT write int getInPass[stationNum] = {0};
    for(int i = 1; i < stationNum; i++)
        cin >> getInPass[i];

    int getOutPass[MAX_STATION_NUM] = {0};
    for(int i = 1; i < stationNum; i++)
        cin >> getOutPass[i];

    int badStation = -1, badDataCode = 0;
    bool hasBadData = false;  // a boolean variable (called a "flag") 
                              // that indicates whether there is an anomaly in the data
    for(int i = 1; i < stationNum; i++)
    {
        if(onCar < getOutPass[i])
        {
            badStation = i;
            badDataCode += 1;
            hasBadData = true;
        }

        onCar -= getOutPass[i];
        onCar += getInPass[i];

        if(onCar > maxPass)
        {
            badStation = i;
            badDataCode -= 1;
            hasBadData = true;
        }
        
        if(hasBadData)  // typically we omit "== true" when putting boolean variables in an if-clause
            break;
    }
    
    if(hasBadData){
        // badDataCode = 0 initially, so if hasBadData is set to be true, then badDataCode will be 0 if and only if there is a type 3 error
        if(badDataCode == 1)
            cout << badStation << ",N";
        else if(badDataCode == -1)
            cout << badStation << ",C";
        else
            cout << badStation << ",B";
    }
    else
        cout << 0;

    return 0;
}