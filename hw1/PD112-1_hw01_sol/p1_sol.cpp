#include <iostream>
using namespace std;

const int MAX_STATION_CNT = 20;

int main()
{
    int stationCnt = 0, onCar = 0;
    cin >> stationCnt >> onCar; 
    
    // passengersOff[i] is the number of passengers geting off the bus at station i+1 
    
    int passengersOff[MAX_STATION_CNT] = {0};  // DO NOT write int passengersOff[stationCnt] = {0};
    for(int i = 0; i < stationCnt - 1; i++)
        cin >> passengersOff[i];

    for(int i = 0; i < stationCnt - 1; i++)
        onCar -= passengersOff[i];
    
    cout << onCar;
     
    return 0;
}

