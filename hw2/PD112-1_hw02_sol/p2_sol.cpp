#include <iostream>
using namespace std;
const int MAX_STATION_NUM = 20;

// 這是你需要完成的函數的 prototype
int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]);

int main(){
    int stationNum = 0, initPass = 0, maxPass = 0;
    int getInPass[MAX_STATION_NUM] = {0};
    int getOutPass[MAX_STATION_NUM] = {0};

    cin >> stationNum >> initPass >> maxPass;
    // 請注意在下面的兩個迴圈中，
    // 第一站的上下車人數放在陣列的第一個而非第零個元素。
    // 其他依此類推
    for(int i = 1; i < stationNum; i++){
        cin >> getInPass[i];
    }
    for(int i = 1; i < stationNum; i++){
        cin >> getOutPass[i];
    }

    int ret = checkCorrectness(stationNum, initPass, maxPass, getInPass, getOutPass);

    if(ret == 0){
        cout << ret;
    }
    else
    {
        if(ret - 3 * stationNum > 0){
            cout << ret - 3 * stationNum << ",B";
        }
        else if(ret - 2 * stationNum > 0){
            cout << ret - 2 * stationNum << ",C";
        }
        else{
            cout << ret - stationNum << ",N";
        }
    }
    
    return 0;
}

// 你上傳你寫的函數後，PDOGS 會把你上傳的程式碼貼在這裡，然後編譯

int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]){
    
    int onCar = initPass, badStation = -1, ret = 0;

    for(int i = 1; i < stationNum; i++)
    {
        // check if there is type 1 error
        if(onCar < getOutPass[i])
        {
            badStation = i;
            ret += stationNum;
        }

        onCar -= getOutPass[i];
        onCar += getInPass[i];

        // check if there is type 2 error
        // there is an interesting design here:
        // if both type 1 & type 2 error occurs,
        // ret will be stationNum + 2 * stationNum + badStation = 3 * stationNum + badStation,
        // which is exactly the wanted return value for type 3 error
        if(onCar > maxPass)
        {
            badStation = i;
            ret += 2 * stationNum;
        }
        
        if(badStation != -1){
            ret += badStation;
            break;
        }
    }
    return ret;
}
