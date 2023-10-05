#include <iostream>
using namespace std;
const int MAX_ITEM_CNT = 100;

// This is the prototype of the function that you should complete
void knapsack(int itemCnt, int capacity, const int weight[], const int value[], const bool bring[], int ret[]);

int main()
{
    int itemCnt = 0, capacity = 0;
    cin >> itemCnt >> capacity;
    
    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    bool bring[MAX_ITEM_CNT] = {0};
    int ret[2] = {0};

    for(int i = 0; i < itemCnt; i++)
        cin >> weight[i];
    for(int i = 0; i < itemCnt; i++)
        cin >> value[i];
    for(int i = 0; i < itemCnt; i++)
        cin >> bring[i];
    
    knapsack(itemCnt, capacity, weight, value, bring, ret);
    
    if(ret[0] == -1)
        cout << -1;
    else
        cout << ret[0] << "," << ret[1];
    
    return 0;
}

// PDOGS will copy and paste your codes here before compilation

void knapsack(int itemCnt, int capacity, const int weight[], const int value[], const bool bring[], int ret[]) {
    int totalWeight = 0, totalValue = 0;
    for (int i = 0; i < itemCnt; ++i) {
        if (bring[i]) { //Check whether the item is placed in the knapsack.
            totalWeight += weight[i];
            totalValue += value[i];
        }
    }
    if (totalWeight > capacity) { //If total weight exceed knapsack capacity, then ret[0] set to -1.
        ret[0] = -1;
    } else { //If total weight doesn't exceed knapsack capacity, then ret[0] set to total weight, ret[1] set to total value.
        ret[0] = totalWeight;
        ret[1] = totalValue;
    }
}