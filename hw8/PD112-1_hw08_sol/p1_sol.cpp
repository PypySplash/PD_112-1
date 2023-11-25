#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Item {
    private:
        char* name;
        int materialCost;
    public:
        Item(char* n, int mc) {
            this->name = new char[501];
            strcpy(this->name, n);
            this->materialCost = mc;
        }
        ~Item(){
            delete[] this->name;
            this->name = nullptr;
        }
        const Item& operator=(const Item& i);
        void setName(char* n) {
            strcpy(this->name, n);
        }
        char* getName() {
            return this->name;
        }
        int getMaterialCost() {
            return this->materialCost;
        }
};

const Item& Item::operator=(const Item& i) {
    if(this != &i) {
        delete [] this->name;
        this->name = new char[501];
        strcpy(this->name, i.name);
        this->materialCost = i.materialCost;     
    }
    return *this;
}

class Product {
    private:
        char* name;
        int price;
        int laborCost;
        int salesQty;
        int itemCnt;
        int overallCost;
        int currentItemIdx;
        Item** itemList;
    public:
        Product(char* name, int price, int laborCost, int salesQty, int itemCnt) {
            this->name = new char[501];
            strcpy(this->name, name);
            this->price = price;
            this->laborCost = laborCost;
            this->salesQty = salesQty;
            this->itemCnt = itemCnt;
            this->itemList = new Item*[itemCnt];
            for(int i = 0; i < itemCnt; i++) {
                this->itemList[i] = nullptr;
            }
            this->overallCost = laborCost;
            this->currentItemIdx = 0;
        }
        ~Product() {
            delete[] this->itemList;
            this->itemList = nullptr;
            delete[] this->name;
            this->name = nullptr;
        }
        const Product& operator=(const Product& p);
        bool isInFrontOf(const Product& prod, int criterion);
        void addItem(Item* itemPtr);
        int calculateProfit();
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
        int getOverallCost() {
            return this->overallCost;
        }
};


bool Product::isInFrontOf(const Product& p, int criterion) {
    // Compare the products according to the criterion
    // Break the tie by comparing the name of the products
    switch (criterion) {
        case 1:
            if(this->price == p.price) return strcmp(this->name, p.name) < 0;
            return this->price > p.price;
        case 2:
            if(this->overallCost == p.overallCost) return strcmp(this->name, p.name) < 0;
            return this->overallCost > p.overallCost;
        case 3:
            if(this->price-this->overallCost == p.price-p.overallCost) return strcmp(this->name, p.name) < 0;
            return this->price-this->overallCost > p.price-p.overallCost;
        case 4:
            if(this->salesQty == p.salesQty) return strcmp(this->name, p.name) < 0;
            return this->salesQty > p.salesQty;
        case 5:
            if(this->salesQty*this->price == p.salesQty*p.price) return strcmp(this->name, p.name) < 0;
            return this->salesQty*this->price > p.salesQty*p.price;
        case 6:
            if(this->salesQty*(this->price-this->overallCost) == p.salesQty*(p.price-p.overallCost)) return strcmp(this->name, p.name) < 0;
            return this->salesQty*(this->price-this->overallCost) > p.salesQty*(p.price-p.overallCost);
        default:
            break;
    }
}

int Product::calculateProfit() {
    // Profit = Sales Quantity * (Price - Overall Cost)
    int result = this->salesQty*(this->price-this->overallCost);
    return result;
}

// The assignment operator of Product
const Product& Product::operator=(const Product& p) {
    if(this != &p) {
        delete [] this->name;
        this->name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        this->price = p.price;
        this->laborCost = p.laborCost;
        this->overallCost = p.overallCost;
        this->salesQty = p.salesQty;
        
        delete [] this->itemList;
        this->itemCnt = p.itemCnt;
        this->itemList = new Item*[this->itemCnt];
        for(int i = 0; i < this->itemCnt; i++)
            this->itemList[i] = p.itemList[i];
    }
    return *this;
}

void Product::addItem(Item* itemPtr) {
    // Add an item to the product[currentItemIdx], and currentIdx++
    // And update the overallCost of that item
    this->itemList[currentItemIdx++] = itemPtr;
    this->overallCost += itemPtr->getMaterialCost();
}

void sortProducts(Product** products, int n, int criterion) {
    // Sort the products according to the criterion
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(!products[j]->isInFrontOf(*products[j+1], criterion)) {
                swap(products[j], products[j+1]);
            }
        }
    }
}

int main() {
    int productCnt = 0, itemTotalCnt = 0, relationships = 0;
    // Input the number of products, items, and relationships
    // Need to cin.get() to skip the '\n' character
    cin >> productCnt >> itemTotalCnt >> relationships;
    cin.get();
    // Arrays of pointers for products and items
    Product** products = new Product*[productCnt];
    Item** items = new Item*[itemTotalCnt];
    // Coping with products
    for(int i = 0; i < productCnt; i++) {
        // Load input until ',' to obtain the name of the product  
        char productName[501];
        cin.getline(productName, 501, ',');
        int productArgs[4] = {0}, argIdx = 0;
        // Input the price, labor cost, sales quantity, and item count of the product
        // Need to cin.get() to skip the '\n' character
        cin >> productArgs[0] >> productArgs[1] >> productArgs[2] >> productArgs[3];
        cin.get();
        // New a Product object and store it in the array
        products[i] = new Product(productName, productArgs[0], productArgs[1], productArgs[2], productArgs[3]);
    }
    // Coping with items
    for(int i = 0; i < itemTotalCnt; i++) {
        // Load input until ',' to obtain the name of the item
        char itemName[501];
        cin.getline(itemName, 501, ',');
        // Input the material cost of the item
        // Need to cin.get() to skip the '\n' character
        int materialCost = 0;
        cin >> materialCost;
        cin.get();
        // New an Item object and store it in the array
        items[i] = new Item(itemName, materialCost);
    }
    // Coping with relationships
    for(int i = 0; i < relationships; i++) {
        // Load input until ',' to obtain the name of the product
        char productName[501];
        cin.getline(productName, 501, ',');
        // Load input until '\n' to obtain the name of the item
        char itemName[501];
        cin.getline(itemName, 501);
        int targetProduct = -1, targetItem = -1;
        for(int j = 0; j < productCnt; j++) {
            // Find the target product in products array
            if(strcmp(products[j]->getName(), productName) == 0) {
                targetProduct = j;
                break;
            }
        }
        for(int k = 0; k < itemTotalCnt; k++) {
            // Find the target item in items array
            if(strcmp(items[k]->getName(), itemName) == 0) {
                targetItem = k;
                break;
            }
        }
        // Add the target item to the target product->itemList
        products[targetProduct]->addItem(items[targetItem]);
    }
    int criterion = 0, queryCnt = 0;
    // Input the criterion and the number of queries
    // Need to cin.get() to skip the '\n' character
    cin >> criterion >> queryCnt;
    cin.get();
    // Sort the products according to the criterion
    sortProducts(products, productCnt, criterion);
    // Calculate the sum of the first k products' profits
    int ans = 0;
    for(int i = 0; i < queryCnt; i++) {
        ans += products[i]->calculateProfit();
    }
    cout << ans << endl;
    // Delete the products and items
    // Need to set the pointers to nullptr after deleting
    for(int i = 0; i < productCnt; i++) {
        delete products[i];
        products[i] = nullptr;
    }
    delete[] products;
    products = nullptr;
    for(int i = 0; i < itemTotalCnt; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    delete[] items;
    items = nullptr;
    return 0;
}