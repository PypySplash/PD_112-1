#include <iostream>
using namespace std;

// This is the prototype of the function to be completed
void checkCorrectness(int stationNum, int initPass, int maxPass, const int** passenger, int& wrongStationID, int& wrongType);

int main(){
    int stationNum = 0, initPass = 0, maxPass = 0;
    int** passenger = new int*[2];

    int wrongStationID = 0;
    int wrongType = 0;

    cin >> stationNum >> initPass >> maxPass;
    passenger[0] = new int[stationNum - 1];
    passenger[1] = new int[stationNum - 1];

    for(int i = 0; i < stationNum - 1; i++){
        cin >> passenger[0][i];
    }
    for(int i = 0; i < stationNum - 1; i++){
        cin >> passenger[1][i];
    }
    
    checkCorrectness(stationNum, initPass, maxPass, const_cast<const int**>(passenger), wrongStationID, wrongType);

    if(wrongStationID == 0){
        cout << wrongStationID;
    }
    else{
        if(wrongType == 1){
            cout << wrongStationID << ",N";
        }
        else if(wrongType == 2){
            cout << wrongStationID << ",C";
        }
        else if(wrongType == 3){
            cout << wrongStationID << ",B";
        }
    }
    
    delete[] passenger[0];
    delete[] passenger[1];
    passenger[0] = passenger[1] = nullptr;
    delete[] passenger;
    passenger = nullptr;
    
    return 0;
}

void checkCorrectness(int stationNum, int initPass, int maxPass, const int** passenger, int& wrongStationID, int& wrongType)
{
    int countN = 0, countC = 0;

    for (int i = 0; i < stationNum - 1; i++)
    {
        initPass -= passenger[1][i];
        if (initPass < 0)
            countN++;

        initPass += passenger[0][i];
        if (initPass > maxPass)
            countC++;
        
        if (countC != 0 || countN != 0)
        {
            wrongStationID = i + 1;
            break;
        }
    }

    if (countN != 0)
        wrongType = 1;
    if (countC != 0) {
        wrongType = 2;
        if (countN != 0)
            wrongType = 3;
    }
}

// Your codes will be copied and pasted here