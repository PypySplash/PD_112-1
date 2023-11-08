#include <iostream>
#include <cstring>
using namespace std;

const int LEN = 102;

class Product
{
private :
    // char* name;
    // int price ;
    // int cost;
    // int salesQty ;
public :
    // n: name , p: price , c: cost , sq: sales quantity
    char* name;
    int price;
    int cost;
    int salesQty ;
    Product (char* n, int p, int c, int sq);
    ~ Product ();
    bool isInFrontOf(const Product& prod , int criterion);
    void addSales(int quantitiy);
};
// you may define more members by yourselves

Product::Product(char* n, int p, int c, int sq)
{
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    price = p;
    cost = c;
    salesQty = sq;
}
Product::~Product() {
    delete [] name;
}

void Product::addSales(int quantity) {  // 當輸入有 "S" 時，用來新增銷售量
    this->salesQty += quantity;
}
bool Product::isInFrontOf(const Product &prod, int criterion)
{
    switch(criterion)
    {
        case 1:
            if (this->price > prod.price) 
                return true;
            else if (this->price == prod.price)
                // strcmp(this->name, prod.name) < 0 表示如果 this->name 字典順序上小於 prod.name，則返回 true。
                return strcmp(this->name, prod.name) < 0;
            break;
        case 2:
            if (this->cost > prod.cost) 
                return true;
            else if (this->cost == prod.cost)
                return strcmp(this->name, prod.name) < 0;
            break;
        case 3:  // 毛利 = price - cost
            if ((this->price - this->cost) > (prod.price - prod.cost)) 
                return true;
            else if ((this->price - this->cost) == (prod.price - prod.cost))
                return strcmp(this->name, prod.name) < 0;
            break;
        case 4:
            if (this->salesQty > prod.salesQty) 
                return true;
            else if (this->salesQty == prod.salesQty)
                return strcmp(this->name, prod.name) < 0;
            break;
        case 5:  // 總營收 = price * salesQty
            if ((this->price * this->salesQty) > (prod.price * prod.salesQty)) 
                return true;
            else if ((this->price * this->salesQty) == (prod.price * prod.salesQty))
                return strcmp(this->name, prod.name) < 0;
            break;
        case 6:  // 總利潤 = 毛利 * salesQty = (price - cost) * salesQty
            if ((this->price - this->cost) * this->salesQty > (prod.price - prod.cost) * prod.salesQty) 
                return true;
            else if ((this->price - this->cost) * this->salesQty == (prod.price - prod.cost) * prod.salesQty)
                return strcmp(this->name, prod.name) < 0;
            break;
    }
    return false;  // 如果當前物件不應該排在傳入的物件之前，則返回 false
}

void swapPtr(Product*& p1, Product*& p2)  // 與其換地址，不如換指針
{
    Product* temp = p1;
    p1 = p2;
    p2 = temp;
}

int main()
{
    int productCnt = 0, sales = 0, searchCnt = 0, sortingCondition = 0, formerNum = 0;
    cin >> productCnt >> sales >> searchCnt;
    cin.ignore();  // 忽略換行符號
    Product** products = new Product*[productCnt];
    int tempSearchCnt = searchCnt;  // 因為等等在 while 迴圈 searchCnt 會 -- ，故創一個 tempSearchCnt 來代替 searchCnt 做 --

    for (int i = 0; i < productCnt; i++)
    {
        char tempName[LEN];
        int price = 0, cost = 0, salesQty = 0;
        cin.getline(tempName, LEN, ',');
        cin >> price >> cost >> salesQty;
        cin.ignore();  // 忽略換行符號

        char* name = new char[strlen(tempName) + 1];
        strcpy(name, tempName);

        products[i] = new Product(name, price, cost, salesQty);
    }

    int sumArray[searchCnt];
    int index = 0;
    while (sales > 0 || tempSearchCnt > 0)  // 創建完 product 後，輸入含有 "S" 或 "T" 的資訊，直到 S, T 的數量歸零
    {
        char commandType;
        cin >> commandType;

        if (commandType == 'S')
        {
            cin.ignore();
            char productName[LEN];
            int addSalesQty = 0;
            cin.get(productName, LEN, ','); // 讀取商品名稱直到逗號
            cin.ignore(); // 忽略逗號
            
            cin >> addSalesQty;

            // ...找到對應的商品並更新其銷售數量...
            for (int i = 0; i < productCnt; i++) 
            {
                if (strcmp(products[i]->name, productName) == 0) 
                {
                    products[i]->addSales(addSalesQty);
                    break; // 找到商品後跳出循環
                }
            }
            sales--;
        }
        else if (commandType == 'T') 
        {
            cin >> sortingCondition >> formerNum;
            // 參考講義上的 bubble sort，之後也可以改進為 insertion sort, merge sort 等等增加效率
            for (int i = 0; i < productCnt; i++)
            {
                for (int j = 0; j < productCnt - i - 1; j++)
                {
                    if (!(products[j]->isInFrontOf(*products[j + 1], sortingCondition)))  // 若為 False 則交換
                        swapPtr(products[j], products[j + 1]);
                }
            }

            // ...根據指定的條件排序並輸出前k個商品的相關數據...
            int sum = 0;
            for (int i = 0; i < formerNum; i++) {
                sum += (products[i]->price - products[i]->cost) * products[i]->salesQty;
            }
            
            tempSearchCnt--;

            sumArray[index] = sum;  // 將最後需要輸出的資訊存在這
            index++;
        }
    }

    for (int i = 0; i < searchCnt; i++)
    {
        cout << sumArray[i];
        if (i != searchCnt - 1) cout << ",";
    }
    
    for (int i = 0; i < productCnt; i++) {
        delete products[i];
    }
    delete [] products;
}
