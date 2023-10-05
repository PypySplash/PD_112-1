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

    for(int i = 0; i < stationCnt - 1; i++)
    {
        onCar -= passengersOff[i];
        onCar += passengersOn[i];
    }
    
    // Initialize maxDifference as the difference at station 0; 
    // then, the following codes will work even if all numbers are negative   
    int maxDifference = passengersOn[0] - passengersOff[0];
    for(int i = 1; i < stationCnt - 1; i++)
    {
        int curDifference = passengersOn[i] - passengersOff[i];
        if(curDifference > maxDifference)
            maxDifference = curDifference;
    }

    cout << onCar << ',' << maxDifference;
    
    return 0;
}

