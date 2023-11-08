#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
using namespace std;

const int LEN = 117;

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
    int price ;
    int cost;
    int salesQty ;
    Product (char* n, int p, int c, int sq);
    ~ Product ();
    bool isInFrontOf ( const Product & prod , int criterion );
};
// you may define more members by yourselves

Product::Product(char* n, int p, int c, int sq)
{
    name = new char[strlen(n)];
    strcpy(name, n);
    price = p;
    cost = c;
    salesQty = sq;
}
Product::~Product() {
    delete [] name;
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

void swapPtr(Product*& p1, Product*& p2)
{
    Product* temp = p1;
    p1 = p2;
    p2 = temp;
}

int main()
{
    int productCnt = 0, y = 0, k = 0;
    char line[LEN];
    Product** products = new Product*[LEN]; // 假設產品數量不會超過 LEN

    // 循環讀取產品資訊，直到讀到的行沒有逗號為止
    while (cin.getline(line, LEN)) {
        // 檢查該行是否有逗號，來判斷是否為產品資訊
        if (strchr(line, ',') == NULL) {
            // 分析 y 和 k
            sscanf(line, "%d %d", &y, &k);
            break;
        }

        char* name = strtok(line, ",");
        int price = atoi(strtok(NULL, " "));
        int cost = atoi(strtok(NULL, " "));
        int salesQty = atoi(strtok(NULL, " "));
        products[productCnt++] = new Product(strdup(name), price, cost, salesQty);
    }

    for (int i = 0; i < productCnt; i++)
    {
        for (int j = 0; j < productCnt - i - 1; j++)
        {
            if (!(products[j]->isInFrontOf(*products[j + 1], y)))  // 若為 False 則交換
                swapPtr(products[j], products[j + 1]);
        }
    }
    int sum = 0;
    for (int i = 0; i < k; i++)
        sum += (products[i]->price - products[i]->cost) * products[i]->salesQty;
    cout << sum;
    
    for (int i = 0; i < productCnt; i++) {
        delete products[i];
    }
    delete [] products;
}
