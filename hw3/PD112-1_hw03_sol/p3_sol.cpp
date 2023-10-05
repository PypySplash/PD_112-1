#include <iostream>
using namespace std;

const int MAX_ITEM_CNT = 100;
const int MAX_SOLUTION_CNT = 10;

int greedy(const int capacity, const int itemCnt, const int weight[], const int value[], int selected[], int ret[]);

int main() {
    int itemCnt = 0, capacity = 0, totalValue = 0;
    cin >> itemCnt >> capacity;
    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    int selected[MAX_ITEM_CNT] = {0};
    int ret[MAX_ITEM_CNT] = {0};
    for (int i = 0; i < itemCnt; i++) 
        cin >> weight[i];
    for (int i = 0; i < itemCnt; i++) 
        cin >> value[i];
    totalValue = greedy(capacity, itemCnt, weight, value, selected, ret);
    if (totalValue == 0){
        cout << ";0";
        return 0;
    }
    cout << ret[0];
    for (int i = 1; ret[i] >= 0 && i < itemCnt; i++) {
        cout << "," << ret[i];
    }
    cout << ";" << totalValue;
}

int greedy(const int capacity, const int itemCnt, const int weight[], const int value[], int selected[], int ret[]) {
    int targetItemIdx = 0, targetItemValue = 0, totalWeight = 0, totalValue = 0;
    // Find the target item to put into knapsack for each round.
    for (int i = 0; i < itemCnt; i++) {
        targetItemIdx = -1;
        targetItemValue = 0;
        // Find the target item by checking each item's weight and value, and whether the item is already in the knapsack.
        for (int j = 0; j < itemCnt; j++) {
            if (!selected[j] && totalWeight + weight[j] <= capacity && value[j] > targetItemValue){
                targetItemIdx = j;
                targetItemValue = value[j];
            }
        }
        // If find the target item then add it to the knapsack and go to the next round, else return.
        if (targetItemIdx >= 0){
            selected[targetItemIdx] = 1;
            ret[i] = targetItemIdx + 1;
            totalValue += value[targetItemIdx];
            totalWeight += weight[targetItemIdx];
        } else {
            ret[i] = -1;
            break;
        }
    }
    return totalValue;
}