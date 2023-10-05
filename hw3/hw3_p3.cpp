#include <iostream>
using namespace std;
const int MAX_ITEM_CNT = 100;

int greedyalgorithm(int objectNumber, int weightCapacity, const int weight[], const int value[]);

int main() 
{
    int objectNumber = 0, weightCapacity = 0;
    cin >> objectNumber >> weightCapacity;

    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    for (int i = 0; i < objectNumber; i++)
        cin >> weight[i];
    for (int i = 0; i < objectNumber; i++)
        cin >> value[i];

    int valueCount = 0;
    valueCount = greedyalgorithm(objectNumber, weightCapacity, weight, value);

    cout << ";" << valueCount << "\n";
}

int greedyalgorithm(int objectNumber, int weightCapacity, const int weight[], const int value[])
{
    // 初始化 x[1] = x[2] = ... = x[n] = 0
    bool x[MAX_ITEM_CNT] = {0};

    int sumK = 0;
    int valueCount = 0;
    int weightCount = 0;
    int count = 0;

    while(true)
    {
        // 令 object set 為所有還沒被選且選取之後不會超過耐重度上限的所有物品之集合
        int objectSet[MAX_ITEM_CNT] = {0};
        for (int i = 0; i < objectNumber; i++) 
        {
            if (x[i] == 0 && (weightCount + weight[i]) <= weightCapacity)
                objectSet[i] = i;
        }

        // if object set 是空集合，break。
        int sumK = 0;
        for (int i = 0; i < objectNumber; i++)
            sumK += objectSet[i];
        
        if (sumK == 0)
            break;
        
        // else
        else
        {
            // 這邊只處理逗號的問題
            if (count != 0)
                cout << ",";
            count++;

            // 從 K 中挑出價值最高的物品 i，若平手則挑編號最小的
            int maxValue = 0, maxIndex = 0;
            for (int i = 0; i < objectNumber; i++) 
            {
                if (maxValue < value[i] && x[i] == 0 && (weightCount + weight[i] <= weightCapacity)) 
                {
                    maxValue = value[i];
                    maxIndex = i;
                }
            }

            // 令 x[i] = 1
            x[maxIndex] = 1;
            valueCount += value[maxIndex];
            weightCount += weight[maxIndex];
            cout << maxIndex + 1;
        }
    }   
    return valueCount;
}

// 初始化 x[1] = x[2] = ... = x[n] = 0
// 背包裡第 i 項物品，若還沒被選則為 0 ，若被選擇為將值改為 1
// while(true)
// {
//   令 K 為所有還沒被選且選取之後不會超過耐重度上限的所有物品之集合
     // 這裡選擇用 array 存
     // 並遍歷一次 array 看是否每個元素都是 0 來判斷 K 是否是空集合
//   if(K 是空集合)  
//     break
//   else 
//   {
//     從 K 中挑出價值最高的物品 i，若平手則挑編號最小的
//     令 x[i] = 1
//   }
// }
// return x