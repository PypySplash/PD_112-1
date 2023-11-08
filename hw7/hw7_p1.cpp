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
    cin >> productCnt ;
    Product** products = new Product*[productCnt];
    
    for (int i = 0; i < productCnt; i++)
    {
        char tempName[LEN];
        int price = 0, cost = 0, salesQty = 0;
        cin.getline(tempName, LEN, ',');
        cin >> price >> cost >> salesQty;

        char* name = new char[strlen(tempName) + 1];
        strcpy(name, tempName);

        products[i] = new Product(name, price, cost, salesQty);
    }
    cin >> y >> k;

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
        // cout << products[i]->name << ",";
        // cout << products[i]->price << ",";
        // cout << products[i]->cost << ",";
        // cout << products[i]->salesQty << ",";
    cout << sum;
    
    for (int i = 0; i < productCnt; i++) {
        delete products[i];
    }
    delete [] products;
}
