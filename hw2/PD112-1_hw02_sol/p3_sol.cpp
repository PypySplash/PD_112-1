#include <iostream>
using namespace std;
const int MAX_STATION_NUM = 20;

int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]);

int main(){
    int stationNum = 0, carNum = 0, maxPass = 0;
    int getInPass[MAX_STATION_NUM] = {0};
    int getOutPass[MAX_STATION_NUM] = {0};

    cin >> stationNum >> carNum >> maxPass;

    // for each car, check its corresponding error type
    // 0: no unreasonable situation; 1: type 1; 2: type 2; 3: type 3
    int typeCnt[4] = {0};
    for(int i = 0; i < carNum; i++){
        int initPass = 0;
        cin >> initPass;
        for(int i = 1; i < stationNum; i++)
            cin >> getInPass[i];
        for(int i = 1; i < stationNum; i++)
            cin >> getOutPass[i];

        int ret = checkCorrectness(stationNum, initPass, maxPass, getInPass, getOutPass);
        typeCnt[ret] += 1;
    }

    cout << typeCnt[1] << ',' << typeCnt[2] << ',' << typeCnt[3];
    
    return 0;
}

// this function will return 0 if there's no unreasonable situation; and 1, 2, 3 for type 1, 2, 3 error respectedly
int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]){
    
    int onCar = initPass, ret = 0;

    for(int i = 1; i < stationNum; i++)
    {
        if(onCar < getOutPass[i])
            ret += 1;
        
        onCar -= getOutPass[i];
        onCar += getInPass[i];
        
        if(onCar > maxPass)
            ret += 2;
        
        if(ret != 0)
            break;
    }
    return ret;
}