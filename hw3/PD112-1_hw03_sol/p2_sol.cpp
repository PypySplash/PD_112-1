#include <iostream>
using namespace std;

const int MAX_ITEM_CNT = 100;
const int MAX_SOLUTION_CNT = 10;

void solutionValidation(int itemCnt, int capacity, int solution, const int weight[], const int value[], int ret[]);

int main() {
    int itemCnt = 0, capacity = 0, solution = 0;
    cin >> itemCnt >> capacity >> solution;
    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    int ret[2] = {0};
    for (int i = 0; i < itemCnt; i++) 
        cin >> weight[i];
    for (int i = 0; i < itemCnt; i++) 
        cin >> value[i];
    solutionValidation(itemCnt, capacity, solution, weight, value, ret);
    cout << ret[0] << "," << ret[1];
}

void solutionValidation(int itemCnt, int capacity, int solution, const int weight[], const int value[], int ret[]){
    int totalNum = 0, currTotalWeight = 0, currTotalValue = 0, maxValue = 0;
    int objNum = 0, currIdx = 0;
    // For each solution
    for (int i = 0; i < solution; i++) {
        currTotalValue = 0;
        currTotalWeight = 0;
        cin >> objNum;
        // Calculate total weight and value for each solution
        for (int j = 0; j < objNum; j++) {
            cin >> currIdx;
            currTotalValue += value[currIdx - 1];
            currTotalWeight += weight[currIdx - 1];
        }
        // Check if the solution is valid or not
        if (currTotalWeight <= capacity) {
            totalNum += 1;
            if (currTotalValue > maxValue) {
                maxValue = currTotalValue;
            }
        }
    }
    ret[0] = totalNum;
    ret[1] = maxValue;
}