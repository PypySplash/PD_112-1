#include <iostream>
using namespace std;
const int MAX_ITEM_CNT = 100;
const int MAX_VALUE = 100;

int main()
{
    int n = 0, B = 0;
    cin >> n >> B;

    int weight[MAX_ITEM_CNT] = {0};
    int value[MAX_ITEM_CNT] = {0};
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    for (int i = 0; i < n; i++)
        cin >> value[i];

    // 初始化 x[1] = x[2] = ... = x[n] = 1
    bool* x = new bool [n];
    for (int i = 0; i < n; i++)
        x[i] = 1;

    int weightCount = 0, valueCount = 0;
    for (int i = 0; i < n; i++)
    {
        weightCount += weight[i];
        valueCount += value[i];
    }

    // if 沒超重 return x
    if (weightCount <= B)
    {
        for (int i = 0; i < n; i++)
        {
            cout << i + 1;
            if (i + 1 != n)
                cout << ",";
        }
        cout << ";" << valueCount;
    }

    while(true)
    {
        // 令 K 為所有還沒被選，且選取之後不會超過耐重度上限的所有物品之集合
        int K[MAX_ITEM_CNT] = {0};
        for (int i = 0; i < n; i++)
        {
            if (weightCount - weight[i] <= B && x[i] == 1)
                K[i] = i;
        }

        int sumK = 0;
        for (int i = 0; i < n; i++)
            sumK += K[i];

        int minValue = MAX_VALUE + 1, minIndex = 0;
        if (sumK == 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (minValue > value[i] && x[i] == 1)
                {
                    minValue = value[i];
                    minIndex = i;
                }
            }

            x[minIndex] = 0;
            weightCount -= weight[minIndex];
            valueCount -= value[minIndex];
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (minValue > value[i] && x[i] == 1 && (weightCount - weight[i] <= B))
                {
                    minValue = value[i];
                    minIndex = i;
                }
            }
            x[minIndex] = 0;
            weightCount -= weight[minIndex];
            valueCount -= value[minIndex];
            break;
        }
    }
    int* temp = new int [n];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (x[i] != 0)
        {
            temp[count] = i + 1;
            count++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (temp[i] != 0)
        {
            if (i != 0)
                cout << ",";
            cout << temp[i];
        }
    }
    cout << ";" << valueCount << "\n";

    delete [] x;
    x = nullptr;
    delete [] temp;
    temp = nullptr;

    return 0;
}

// 初始化 x[1] = x[2] = ... = x[n] = 1
// if(沒超重)
//   return x
// while(true)
// {
//   令 K 為所有還沒被移除且移除後能使總重量不超過耐重度上限的所有物品之集合
//   if(K 是空集合)
//   {
//     從所有還沒被移除的物品中挑出價值最低的物品 i，若平手則為編號最小的
//     令 x[i] = 0
//   }
//   else 
//   {
//     從 K 中挑出價值最低的物品 i，若平手則為編號最小的
//     令 x[i] = 0
//     break
//   }
// }
// return x