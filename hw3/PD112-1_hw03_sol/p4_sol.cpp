#include <iostream>
using namespace std;

const int MAX_ITEM_CNT = 100;
const int MAX_ITEM_VALUE = 100;
const int MAX_SOLUTION_CNT = 10;

int greedy(const int capacity, const int itemCnt, const int weight[], const int value[], int selected[]);

int main() {
    int itemCnt = 0, capacity = 0;
    int totalValue = 0;
    cin >> itemCnt >> capacity;
    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    int selected[MAX_ITEM_CNT] = {0};
    bool first = true;
    for (int i = 0; i < itemCnt; i++) {
        cin >> weight[i];
    }
    for (int i = 0; i < itemCnt; i++) {
         cin >> value[i];
    }
    totalValue = greedy(capacity, itemCnt, weight, value, selected);
    for (int i = 0; i < itemCnt; i++){
        if (selected[i]) {
            if (first) {
                cout << i + 1;
                first = false;
            } else {
                cout << "," << i + 1;
            }
        }
    }
    cout << ";" << totalValue;
    return 0;
}

int greedy(const int capacity, const int itemCnt, const int weight[], const int value[], int selected[]){
    int targetItemIdx = 0, targetItemValue = 0;
    int totalValue = 0, totalWeight = 0;
    bool underCapacity = false;
    for (int i = 0; i < itemCnt; i++) {
        totalWeight += weight[i];
        totalValue += value[i];
        selected[i] = 1;
    }
    if (totalWeight <= capacity) {
        return totalValue;
    }
    // Find the target item to remove from the knapsack for each round.
    while(true){
        targetItemIdx = -1;
        targetItemValue = MAX_ITEM_VALUE + 1;
        // Check whether it is exist an item that makes the knapsack be able to contain the rest item by removed it.
        for (int i = 0; i < itemCnt; i++){
            if (selected[i] && totalWeight - weight[i] <= capacity){
                targetItemIdx = i;
                targetItemValue = value[i];
                underCapacity = true;
                break;
            }
        }
        // If not exist, find the minimum value in the knapsack.
        if (targetItemIdx == -1){
            for (int i = 0; i < itemCnt; i++){
                if (selected[i] && value[i] < targetItemValue){
                    targetItemIdx = i;
                    targetItemValue = value[i];
                }
            }
        } else { // If exist, continue to find the minimum value in the knapsack which also makes the knapsack be able to contain the rest item by removed it.
            for (int i = targetItemIdx + 1; i < itemCnt; i++){
                if (selected[i] && totalWeight - weight[i] <= capacity && value[i] < targetItemValue){
                    targetItemIdx = i;
                    targetItemValue = value[i];
                }
            }
        }
        selected[targetItemIdx] = 0;
        totalValue -= value[targetItemIdx];
        totalWeight -= weight[targetItemIdx];
        if (underCapacity) {
            break;
        }
    }
    return totalValue;
}