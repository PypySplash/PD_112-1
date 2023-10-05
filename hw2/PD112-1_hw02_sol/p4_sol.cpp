#include <iostream>
using namespace std;
const int MAX_STATION_NUM = 20;

// 這是你需要完成的函數的 prototype
void checkCorrectness(int stationNum, int initPass, int maxPass, const int passenger[][MAX_STATION_NUM], int ret[]);

int main(){
    int stationNum = 0, initPass = 0, maxPass = 0;
    int passenger[2][MAX_STATION_NUM] = {0};
    int ret[2] = {0};
    cin >> stationNum >> initPass >> maxPass;
    // 請注意在下面的兩個迴圈中，
    // 第一站的上下車人數放在陣列的第一個而非第零個元素。
    // 其他依此類推
    for(int i = 1; i < stationNum; i++){
        cin >> passenger[0][i];
    }
    for(int i = 1; i < stationNum; i++){
        cin >> passenger[1][i];
    }
    
    checkCorrectness(stationNum, initPass, maxPass, passenger, ret);

    if(ret[0] == 0){
        cout << ret[0];
    }
    else{
        if(ret[1] == 1){
            cout << ret[0] << ",N";
        }
        else if(ret[1] == 2){
            cout << ret[0] << ",C";
        }
        else if(ret[1] == 3){
            cout << ret[0] << ",B";
        }
    }
    
    return 0;
}

// 你上傳你寫的函數後，PDOGS 會把你上傳的程式碼貼在這裡，然後編譯
// this function will not return any value but will change the value of ret array
void checkCorrectness(int stationNum, int initPass, int maxPass, const int passenger[][MAX_STATION_NUM], int ret[]){
    int onCar = initPass;

    for(int i = 1; i < stationNum; i++)
    {
        // check if there is type 1 error
        if(onCar < passenger[1][i])
        {
            ret[0] = i;
            ret[1] = 1;
        }

        onCar -= passenger[1][i];
        onCar += passenger[0][i];

        // check if there is type 2 error
        // there is an interesting design here:
        // if both type 1 & type 2 error occurs,
        // ret will be 1 + 2 = 3,
        // which is exactly the wanted return value for type 3 error
        if(onCar > maxPass)
        {
            ret[0] = i;
            ret[1] += 2;
        }
        
        if(ret[0] != 0)
            break;
    }
}
