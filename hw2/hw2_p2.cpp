#include <iostream>
using namespace std;
const int MAX_STATION_NUM = 20;

// This is the prototype of the function you need to complete.
// 這是你需要完成的函數的 prototype
int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]);

int main(){
    int stationNum = 0, initPass = 0, maxPass = 0;
    int getInPass[MAX_STATION_NUM] = {0};
    int getOutPass[MAX_STATION_NUM] = {0};

    cin >> stationNum >> initPass >> maxPass;
    // Please note that in the two loops below,
    // the boarding and alighting counts for the first stop are placed in the array's first element rather than the zeroth element.
    // The same applies to the subsequent stops.
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

int checkCorrectness(int stationNum, int initPass, int maxPass, const int getInPass[], const int getOutPass[]) {
    
    int countN = 0, countC = 0, temp = 0;
    
    for (int i = 1; i < stationNum; i++) {
        
        initPass -= getOutPass[i];
        if (initPass < 0)
            countN++;
        
        initPass += getInPass[i];
        if (initPass > maxPass)
            countC++;

        if (countC != 0 || countN != 0) {
            temp = i;
            break;
        }

    }
    if (countN == 0 && countC == 0)
        temp = 0;
    else {
        if (countN != 0 && countC == 0)
            temp += stationNum;

        if (countC != 0 && countN == 0)
            temp += 2 * stationNum;
        
        if (countN != 0 && countC != 0)
            temp += 3 * stationNum;
    }
    
    return temp;
}


// After you upload the function you've written, PDOGS will paste the code you uploaded HERE and then compile it.
// 你上傳你寫的函數後，PDOGS 會把你上傳的程式碼貼在這裡，然後編譯