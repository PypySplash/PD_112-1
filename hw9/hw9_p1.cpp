#include <iostream>
#include <cstring>
using namespace std;
const int LEN = 102;



class Item 
{
private:
    char* name;
    int materialCost;
public:
    // n: name, mc: material cost
    Item(char* n, int mc);
    Item(const Item& item);  // header of copy constructor
    ~Item();
    char* getName() {
        return this->name;
    }
    int getMaterialCost() {
        return this->materialCost;
    }
    const Item& operator=(const Item& item);  // header of assignment operator
};
Item::Item(char* n, int mc)
{
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    materialCost = mc;
}
Item::Item(const Item& item)  // copy constructor
{
    name = new char[strlen(item.name) + 1];
    strcpy(name, item.name);
    materialCost = item.materialCost;
}
Item::~Item() {
    delete [] name;
    name = nullptr;
}
const Item& Item::operator=(const Item& item)  // assignment operator
{
    if (this != &item) // 檢查自我賦值
    {
        delete[] name; // 刪除舊的記憶體
        name = new char[strlen(item.name) + 1];
        strcpy(name, item.name);
        materialCost = item.materialCost;
    }
    return *this;
}



class Product
{
private:
    char* name;
    int price;
    int laborCost;
    int salesQty;
    int itemCnt;
    int index;
    int totalCost;
    Item** itemList;
public:
    // Product();
    Product(char* name, int price, int laborCost, 
            int salesQty, int itemCnt);
    Product(const Product& other);  // header of copy constructor
    ~Product();
    const void operator=(const Product& prod);  // header of assignment operator
    // Product(const Product& other);
    bool operator<(const Product& other) const;
    Item* operator[](int index) const;
    bool isInFrontOf(const Product& prod, int criterion);
    void addItem(Item* itemPtr);
    char* getName() {
        return this->name;
    }
    int getPrice() {
        return this->price;
    }
    int getLaborCost() {
        return this->laborCost;
    }
    int getSalesQty() {
        return this->salesQty;
    }
    int getItemCnt() {
        return this->itemCnt;
    }
    Item** getItemList() {
        return this->itemList;
    }
    int getTotalCost() {
        return this->totalCost;
    }
    int calculateProfit() {
        // Profit = Sales Quantity * (Price - Overall Cost)
        int result = this->salesQty * (this->price - this->totalCost);
        return result;
    }
};
// you may define more members by yourselves
Product::Product(char* n, int p, int lc, int sq, int ic)
{
    // 在 Product 的 constructor 中應該初始化 itemList 為一個存有 itemCnt 個 Item* 的動態陣列
    itemList = new Item* [ic];  // 記得這裡不需要再次聲明 Item**，直接賦值即可
    // 並且將這些指向 Item 的指標都先指向 nullptr
    for (int i = 0; i < ic; i++) {
        this->itemList[i] = nullptr;
    }

    name = new char[strlen(n) + 1];
    strcpy(name, n);
    price = p;
    laborCost = lc;
    salesQty = sq;
    itemCnt = ic;
    totalCost = lc;
    index = 0;
}
Product::~Product() {
    delete [] this->name;
    this->name = nullptr;
    delete[] this->itemList; // 最後刪除 itemList 陣列
    this->itemList = nullptr;
}
const void Product::operator=(const Product& prod)  // assignment operator
{
    if (this != &prod) // 檢查自我賦值
    {
        delete[] name; // 刪除舊的 name
        name = new char[strlen(prod.name) + 1];
        strcpy(name, prod.name);

        // for (int i = 0; i < itemCnt; i++) { // 先刪除舊的 itemList
        //     delete itemList[i];
        // }
        delete[] itemList; // 刪除 itemList 本身

        price = prod.price;
        laborCost = prod.laborCost;
        salesQty = prod.salesQty;
        itemCnt = prod.itemCnt;
        itemList = new Item*[itemCnt]; // 重新分配空間
        for (int i = 0; i < itemCnt; i++) {
            itemList[i] = prod.itemList[i];
        }
    }
}

Product::Product(const Product& other)  // copy constructor
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    this->price = other.price;
    this->laborCost = other.laborCost;
    this->salesQty = other.salesQty;
    this->itemCnt = other.itemCnt;
    this->index = other.index;
    this->totalCost = other.totalCost;
    itemList = new Item* [itemCnt];
    for (int i = 0; i < itemCnt; i++) {
        // itemList[i] = other.itemList[i];
        itemList[i] = new Item(*other.itemList[i]); // 深拷貝
    }
}
bool Product::operator<(const Product& other) const
{
    if ((this->price - this->totalCost) * this->salesQty < (other.price - other.totalCost) * other.salesQty) return true;
    else return false;
}

Item* Product::operator[](int index) const
{
    // if (index < 0 || index >= this->itemCnt) 
    // {
    //     exit(1);
        // return nullptr;
        // return new Item("\n", 0);
    // }
    return itemList[index];
}

bool Product::isInFrontOf(const Product &prod, int criterion)
{
    switch(criterion)  // 以下的 laborCost 要記得加上 materialCost!!!
    {
        case 1:
            if (this->price > prod.price) 
                return true;
            else if (this->price == prod.price)
                // strcmp(this->name, prod.name) < 0 表示如果 this->name 字典順序上小於 prod.name，則返回 true。
                return strcmp(this->name, prod.name) < 0;
            break;
        case 2:
            if (this->totalCost > prod.totalCost) 
                return true;
            else if (this->totalCost == prod.totalCost)
                return strcmp(this->name, prod.name) < 0;
            break;
        case 3:  // 毛利 = price - totalCost
            if ((this->price - this->totalCost) > (prod.price - prod.totalCost)) 
                return true;
            else if ((this->price - this->totalCost) == (prod.price - prod.totalCost))
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
        case 6:  // 總利潤 = 毛利 * salesQty = (price - totalCost) * salesQty
            if ((this->price - this->totalCost) * this->salesQty > (prod.price - prod.totalCost) * prod.salesQty) 
                return true;
            else if ((this->price - this->totalCost) * this->salesQty == (prod.price - prod.totalCost) * prod.salesQty)
                return strcmp(this->name, prod.name) < 0;
            break;
    }
    return false;  // 如果當前物件不應該排在傳入的物件之前，則返回 false
}

void Product::addItem(Item* itemPtr)
{
    // if there are no more empty space in this->itemList,
    // re-allocate this->itemList with size of (this->itemCnt + 1).
    // copy all the previous entries, and add the new item to the last entry.
    if (this->index > this->itemCnt - 1) {
        // make a copy of the current this->itemList
        Item** tmpList = new Item*[this->itemCnt];
        for (int i = 0; i < this->itemCnt; i++) {
            tmpList[i] = this->itemList[i];
        }
        // delete and re-allocate this->itemList,
        // assign the previous items.
        delete [] this->itemList;
        this->itemCnt++;
        this->itemList = new Item*[this->itemCnt];
        for (int i = 0; i < this->itemCnt - 1; i++) {
            this->itemList[i] = tmpList[i];
        }
        delete[] tmpList;
        tmpList = nullptr;
        // assign the new item.
        this->itemList[itemCnt - 1] = itemPtr;
        this->totalCost += itemPtr->getMaterialCost();
    }
    // Add an item to the product[index],
    // And update the totalCost of that item
    else {
        this->itemList[index] = itemPtr;
        this->totalCost += itemPtr->getMaterialCost();
    }
    this->index++;
}

void swapPtr(Product*& p1, Product*& p2)
{
    Product* temp = p1;
    p1 = p2;
    p2 = temp;
}

int main()
{
    int productCnt = 0, itemTotalCnt = 0, relationships = 0;
    cin >> productCnt >> itemTotalCnt >> relationships;
    cin.ignore();
    Product** products = new Product*[productCnt];
    Item** items = new Item*[itemTotalCnt];
    
    for (int i = 0; i < productCnt; i++)
    {
        char inputName1[LEN];
        int price = 0, laborCost = 0, salesQty = 0, itemCnt = 0;
        cin.getline(inputName1, LEN, ',');
        cin >> price >> laborCost >> salesQty >> itemCnt;
        cin.ignore();  // 忽略換行符號
        
        char* productName = new char[strlen(inputName1) + 1];
        strcpy(productName, inputName1);

        products[i] = new Product(productName, price, laborCost, salesQty, itemCnt);
    }

    for (int i = 0; i < itemTotalCnt; i++)
    {
        char inputName2[LEN];
        int materialCost = 0;
        cin.getline(inputName2, LEN, ',');
        cin >> materialCost;
        cin.ignore();

        char* itemName = new char[strlen(inputName2) + 1];
        strcpy(itemName, inputName2);
        items[i] = new Item(itemName, materialCost);
    }
    
    for (int i = 0; i < relationships; i++)
    {
        char inputName3[LEN], inputName4[LEN];
        cin.getline(inputName3, LEN, ',');
        cin.getline(inputName4, LEN, '\n');

        char* productName2 = new char[strlen(inputName3) + 1];
        strcpy(productName2, inputName3);

        char* itemName2 = new char[strlen(inputName4) + 1];
        strcpy(itemName2, inputName4);

        for (int j = 0; j < productCnt; j++)
        {
            if (strcmp(productName2, products[j]->getName()) == 0)
            {
                for (int k = 0; k < itemTotalCnt; k++)
                {
                    if (strcmp(itemName2, items[k]->getName()) == 0)
                    {
                        products[j]->addItem(items[k]);
                        // products[j]->laborCost += items[k]->materialCost;
                        break;
                    }
                }
                break;
            }
        }
    }
    int y = 0, k = 0;
    cin >> y >> k;

    for (int i = 0; i < productCnt - 1; i++)
    {
        for (int j = 0; j < productCnt - i - 1; j++)
        {
            if (!(products[j]->isInFrontOf(*products[j + 1], y)))  // 若為 False 則交換
                swapPtr(products[j], products[j + 1]);
        }
    }
    int sum = 0;
    for (int i = 0; i < k; i++)
        sum += products[i]->calculateProfit();
        // sum += (products[i]->price - products[i]->laborCost) * products[i]->salesQty;
    cout << sum << endl;
    // testing the copy constructor
    Product newProduct(*products[1]);
    newProduct.addItem(items[1]);
    cout << products[1]->getName() << "\n";
    cout << products[1]->calculateProfit() << "\n";
    cout << newProduct.getName() << "\n";
    cout << newProduct.calculateProfit() << "\n";

    // testing the "<" operator overloading
    if(*products[0] < *products[1]) {
        cout << products[0]->getName() << " is less profitable than " 
             << products[1]->getName() << "\n";
    } 
    else {
        cout << products[0]->getName() << " is no less profitable than " 
             << products[1]->getName() << "\n";
    }

    // testing the "[]" operator overloading
    Item* secondItemOfFirstProduct = (*products[0])[1];
    cout << secondItemOfFirstProduct->getName() << "\n";
    cout << secondItemOfFirstProduct->getMaterialCost() << "\n";

    // Delete the products and items
    // Need to set the pointers to nullptr after deleting
    for (int i = 0; i < productCnt; i++) {
        delete products[i];
        products[i] = nullptr;
    }
    for (int i = 0; i < itemTotalCnt; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    delete [] products;
    products = nullptr;
    delete [] items;
    items = nullptr;
    return 0;
}
