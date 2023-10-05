#include <iostream>
using namespace std;
const int MAX_STATION_NUM = 20;

// This is the prototype of the function you need to complete.
// 這是你需要完成的函數的 prototype
void checkCorrectness(int stationNum, int initPass, int maxPass, const int passenger[][MAX_STATION_NUM], int ret[]);

int main(){
    int stationNum = 0, initPass = 0, maxPass = 0;
    int passenger[2][MAX_STATION_NUM] = {0};
    int ret[2] = {0};
    cin >> stationNum >> initPass >> maxPass;
    // Please note that in the two loops below,
    // the boarding and alighting counts for the first stop are placed in the array's first element rather than the zeroth element.
    // The same applies to the subsequent stops.
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

void checkCorrectness(int stationNum, int initPass, int maxPass, const int passenger[][MAX_STATION_NUM], int ret[]) {

    int countN = 0, countC = 0, temp = 0;
    
    
    for (int i = 1; i < stationNum; i++) {
        
        initPass -= passenger[1][i];
        if (initPass < 0)
            countN++;
        
        initPass += passenger[0][i];
        if (initPass > maxPass)
            countC++;
        
        // 記錄有問題的車站編號
        if (countC != 0 || countN != 0) {
            ret[0] = i;
            break;
        }
    }
    
    if (countN == 0 && countC == 0)
        ret[1] = 0;
    else {
        if (countN != 0 && countC == 0)
            ret[1] = 1;
        if (countC != 0 && countN == 0)
            ret[1] = 2;
        if (countN != 0 && countC != 0)
            ret[1] = 3;
    }
}
// After you upload the function you've written, PDOGS will paste the code you uploaded HERE and then compile it.
// 你上傳你寫的函數後，PDOGS 會把你上傳的程式碼貼在這裡，然後編譯