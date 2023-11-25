#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

// criteria
const int CRI_PRICE = 1;
const int CRI_COST = 2;
const int CRI_GROSS = 3;
const int CRI_QTY = 4;
const int CRI_REVENUE = 5;
const int CRI_PROFIT = 6;

const int MAX_NAME_LEN = 100;
const int MAX_INFO_LEN = 200;
const int MAX_PRODUCT_CNT = 100;

class Product
{
private:
    char* name;
    int price;
    int cost;
    int salesQty;
    int gross;     // There is no need to store gross, revenue, profit since it's redundent.
    int revenue;   // These variables are only stored to speed up the operation.
    int profit;    // You can adopt different solutions depending on the situation.
    void updateInfo();
public:
    Product(char* name, int price, int cost, int salesQty);
    ~Product();
    Product(const Product& p);
    int getProfit() const;
    void print() const;
    bool isInFrontOf(const Product& p, int criterion) const;
};

// constructor
Product::Product(char* name, int price, int cost, int salesQty)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->price = price;
    this->cost = cost;
    this->salesQty = salesQty;
    this->updateInfo();
}

// constructor for Product
Product::Product(const Product& p)
{
    this->name = new char[strlen(p.name) + 1];
    strcpy(this->name, p.name);
    this->price = p.price;
    this->cost = p.cost;
    this->salesQty = p.salesQty;
    this->updateInfo();
}

// destructor
Product::~Product()
{
    delete [] this->name;
}

// update info for other criteria
void Product::updateInfo()
{
    this->gross = this->price - this->cost;
    this->revenue = this->price * this->salesQty;
    this->profit = this->gross * this->salesQty;
}

// get profit
int Product::getProfit() const
{
    return this->profit;
}

// print all info
void Product::print() const
{
    cout << this->name << ' ' << this->price << ' ' << this->cost << ' ' << this->salesQty << ' '
         << this->gross << ' ' << this->revenue << ' ' << this->profit << ' ' << '\n';
}

// if a->isInFrontOf(p, c) == True, product a should be sorted in front of product p
bool Product::isInFrontOf(const Product& p, int criterion) const
{
    bool nameIsInFrontOf = strcmp(this->name, p.name) < 0; 
    switch(criterion)
    {
        case CRI_PRICE:
            return (this->price > p.price) || (this->price == p.price && nameIsInFrontOf);
        case CRI_COST:
            return (this->cost > p.cost) || (this->cost == p.cost && nameIsInFrontOf);
        case CRI_GROSS:
            return (this->gross > p.gross) || (this->gross == p.gross && nameIsInFrontOf);
        case CRI_QTY:
            return (this->salesQty > p.salesQty) || (this->salesQty == p.salesQty && nameIsInFrontOf);
        case CRI_REVENUE:
            return (this->revenue > p.revenue) || (this->revenue == p.revenue && nameIsInFrontOf);
        case CRI_PROFIT:
            return (this->profit > p.profit) || (this->profit == p.profit && nameIsInFrontOf);
    }
}

void swapPointer(Product*& ptrA, Product*& ptrB);
void sortProduct(Product** products, int productCnt, int criterion);
int firstKProfitSum(Product** products, int k);

int main()
{
    Product* products[MAX_PRODUCT_CNT];
    int productCnt = 0;
    
    char info[MAX_INFO_LEN] = {0};
    // read in data and construct objects
    while(cin.getline(info, MAX_INFO_LEN))
    {
        if(strchr(info, ',') == nullptr)  // the last line
            break;
        // separate by ',' into two part
        char* name = strtok(info, ",");
        int price = atoi(strtok(nullptr, " "));
        int cost = atoi(strtok(nullptr, " "));
        int salesQty = atoi(strtok(nullptr, " "));
        products[productCnt] = new Product(name, price, cost, salesQty);
        productCnt++;
    }
    
    int criterion = atoi(strtok(info, " "));
    int k = atoi(strtok(nullptr, " ")); 
    
    sortProduct(products, productCnt, criterion);
    cout << firstKProfitSum(products, k); 
    
    for(int i = 0; i < productCnt; i++)
        delete products[i];  // not delete [] products[i];
    return 0;
}

// swap two pointer
void swapPointer(Product*& ptrA, Product*& ptrB)
{
    Product* temp = ptrA;
    ptrA = ptrB;
    ptrB = temp;
}

// sort product according to criterion
void sortProduct(Product** products, int productCnt, int criterion)
{
    // sort the products according to criterion desecendingly; just a bubble sort
    for(int i = productCnt - 1; i > 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            if(products[j + 1]->isInFrontOf(*products[j], criterion))
                swapPointer(products[j], products[j + 1]);
        }
    }
    return;
}

// sum profit of first k products
int firstKProfitSum(Product** products, int k)
{
    int profitSum = 0;
    for(int i = 0; i < k; i++)
        profitSum += products[i]->getProfit();
    return profitSum;
}
