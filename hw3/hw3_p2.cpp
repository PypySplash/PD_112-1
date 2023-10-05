#include <iostream>
using namespace std;
const int MAX_ITEM_CNT = 100;

int main()
{
    int itemCnt = 0, capacity = 0, m = 0, q= 0;
    cin >> itemCnt >> capacity >> m;
    
    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    int** solution = new int* [m];  // 用動態記憶體配置，因為 input 的長度不一
    int ret[2] = {0};

    for(int i = 0; i < itemCnt; i++)
        cin >> weight[i];
    for(int i = 0; i < itemCnt; i++)
        cin >> value[i];
    for (int i = 0; i < m; i++) {
        cin >> q;
        solution[i] = new int[q + 1];  // q 也放入 array 裏面，故總共 q + 1 個
        solution[i][0] = q;
        for (int j = 1; j < q + 1; j++)
            cin >> solution[i][j];
    }

    int solutionCount = 0, maxValue = 0;

    for (int i = 0; i < m; i++) {

        int totalWeight = 0, totalValue = 0;

        for (int j = 1; j < solution[i][0] + 1; j++) {
            totalWeight += weight[solution[i][j] - 1];  // weight 之 index 從 0 開始
            totalValue += value[solution[i][j] - 1];
        }

        if (totalWeight <= capacity) {
            solutionCount++;
            if (maxValue < totalValue)
                maxValue = totalValue;
        }
    }

    ret[0] = solutionCount;
    ret[1] = maxValue;

    cout << ret[0] << "," << ret[1];
    
    delete [] solution;
    solution = nullptr;

    return 0;
}
