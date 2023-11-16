#include <iostream>
#include <cmath>
using namespace std;

const int ITEM_INFO_NUM = 4;

int calculateRevenue(int supply, int demand, int cost, int price);
int calculateRevenueWithExtraImport(int itemNum, const int** itemInfo, int extraImport, int toImport);

int main() {
    int itemNum = 0, extraImport = 0;
    cin >> itemNum >> extraImport;

    int revenue = 0;
    int** itemInfo = new int*[itemNum]();

    for (int i = 0; i < itemNum; i++) {
        itemInfo[i] = new int[ITEM_INFO_NUM](); // supply, demand, cost, price
        for (int j = 0; j < ITEM_INFO_NUM; j++)
            cin >> itemInfo[i][j];
        revenue += calculateRevenue(
            itemInfo[i][0],
            itemInfo[i][1],
            itemInfo[i][2],
            itemInfo[i][3]
        );
    }

    if (extraImport > 0) {
        for (int i = 0; i < itemNum; i++) {
            int extraRevenue = calculateRevenueWithExtraImport(
                itemNum, const_cast<const int**>(itemInfo), extraImport, i);
            if (extraRevenue > revenue)
                revenue = extraRevenue;
        }
    }

    cout << revenue;

    for (int i = 0; i < itemNum; i++) {
        delete[] itemInfo[i];
        itemInfo[i] = nullptr;
    }
    delete[] itemInfo;
    itemInfo = nullptr;
    
    return 0;
}

// calculate revenue of a specific item
int calculateRevenue(int supply, int demand, int cost, int price) {
    return price * min(supply, demand) - cost * supply;
}

// calculate revenue if we import extra items
int calculateRevenueWithExtraImport(int itemNum, const int** itemInfo, int extraImport, int toImport) {
    int revenue = 0;
    for (int i = 0; i < itemNum; i++) {
        int supply = itemInfo[i][0], demand = itemInfo[i][1], cost = itemInfo[i][2], price = itemInfo[i][3];
        
        if (toImport == i && demand > supply)
            revenue += calculateRevenue(
                supply + min(demand - supply, extraImport), demand, cost, price
            );
        else revenue += calculateRevenue(supply, demand, cost, price);
    }

    return revenue;
}