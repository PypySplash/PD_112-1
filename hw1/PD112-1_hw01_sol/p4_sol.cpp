#include <iostream>
using namespace std;

const int MAX_STATION_CNT = 20;

int main()
{
    int stationCnt = 0, onCar = 0;
    cin >> stationCnt >> onCar; 
    
    // passengersOn[i] is the number of passengers geting on the bus at station i+1 
    // passengersOff[i] is the number of passengers geting off the bus at station i+1
    
    int passengersOn[MAX_STATION_CNT] = {0};  // DO NOT write int passengersOn[stationCnt] = {0};
    for(int i = 0; i < stationCnt - 1; i++)
        cin >> passengersOn[i];

    int passengersOff[MAX_STATION_CNT] = {0};
    for(int i = 0; i < stationCnt - 1; i++)
        cin >> passengersOff[i];
    
    int badStation = -1;
    bool hasBadData = false;  // a boolean variable (called a "flag") 
                              // that indicates whether there is an anomaly in the data
    for(int i = 0; i < stationCnt - 1; i++)
    {
        if(onCar < passengersOff[i])
        {
            badStation = i + 1;
            hasBadData = true;
            break;
        }
        onCar -= passengersOff[i];
        onCar += passengersOn[i];
    }
    
    if(hasBadData)  // typically we omit "== true" when putting boolean variables in an if-clause 
        cout << badStation;
    else
        cout << 0;
    
    return 0;
}

