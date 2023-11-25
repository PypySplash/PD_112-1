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
        Item(const Item& other) { // Copy constructor for Item
	        name = new char[strlen(other.name) + 1];
	        strcpy(name, other.name);
	        materialCost = other.materialCost;
	    }
	   
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

        Product(const Product& other);
	    bool operator<(const Product& other) const;
	    Item* operator[](int index) const;

        bool isInFrontOf(const Product& prod, int criterion);
        void addItem(Item* itemPtr);
        void removeItem(int index);
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

// Corrected Copy Constructor
Product::Product(const Product& other) {
    // Copy name
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);

    // Copy other non-pointer members
    this->price = other.price;
    this->laborCost = other.laborCost;
    this->salesQty = other.salesQty;
    this->overallCost = other.overallCost;
    this->itemCnt = other.itemCnt;
    this->currentItemIdx = other.currentItemIdx;

    // Allocate memory for the copy of the itemList
    this->itemList = new Item*[this->itemCnt];

    // Perform a deep copy of the itemList
    for(int i = 0; i < other.itemCnt; ++i) {
        if(other.itemList[i] != nullptr) {
            this->itemList[i] = new Item(*other.itemList[i]);
        } else {
            this->itemList[i] = nullptr;
        }
    }
}

bool Product::operator<(const Product& other) const { // Overloading '<' operator
    return (this->price - this->overallCost) * salesQty < (other.price - other.overallCost) * other.salesQty;
}

Item* Product::operator[](int index) const { // Overloading '[]' operator
    if(index < 0 || index >= itemCnt) {
        char* emptyName = new char[501];
        emptyName[0] = '\0';
        return new Item(emptyName, 0); // Return a virtual item if index is out of bounds
    }
    return itemList[index];
}


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
    // if there are no more empty space in this->itemList,
    // re-allocate this->itemList with size of (this->itemCnt + 1).
    // copy all the previous entries, and add the new item to the last entry.
    if (this->currentItemIdx > this->itemCnt - 1) {
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
        for (int i = 0; i < this->itemCnt-1; i++) {
            this->itemList[i] = tmpList[i];
        }
        delete[] tmpList;
        tmpList = nullptr;
        // assign the new item.
        this->itemList[itemCnt-1] = itemPtr;
        this->overallCost += itemPtr->getMaterialCost();
    }
    // Add an item to the product[currentItemIdx],
    // And update the overallCost of that item
    else {
        this->itemList[currentItemIdx] = itemPtr;
        this->overallCost += itemPtr->getMaterialCost();
    }
    this->currentItemIdx++;
}

void Product::removeItem(int index) {
    // Check if the index is valid
    if (index < 0 || index >= currentItemIdx) {
        // Invalid index, handle the error as appropriate
        cout << "Index out of bounds." << endl;
        return;
    }
    // Reduce the overall cost by the cost of the item being removed
    if (itemList[index] != nullptr) { // Check if there is an item at the index
        overallCost -= itemList[index]->getMaterialCost();
        delete itemList[index]; // Free the memory of the item
    }
    // Shift items down from the point of removal
    for (int i = index; i < currentItemIdx - 1; i++) {
        itemList[i] = itemList[i + 1];
    }
    itemList[currentItemIdx - 1] = nullptr; // Set the last item to null after shifting
    currentItemIdx--; // Decrement the count of current items
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
    // Need to cin.get() to skip the endl character
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
        // Need to cin.get() to skip the ennl character
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
        // Need to cin.get() to skip the endl character
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
        // Load input until endl to obtain the name of the item
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
    // Need to cin.get() to skip the endl character
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
    
    // testing the copy constructor
    Product newProduct(*products[1]);
    newProduct.addItem(items[1]);
    cout <<  products[1]->getName() << endl;
    cout <<  products[1]->calculateProfit() << endl;
    cout << newProduct.getName() << endl;
    cout << newProduct.calculateProfit() << endl;

    // testing the "<" operator overloading
    if (*products[0] < *products[1]) {
        cout << products[0]->getName() << " is less profitable than " << products[1]->getName() << endl;
    } else {
        cout << products[0]->getName() << " is more profitable or equally profitable as " << products[1]->getName() << endl;
    }

    // testing the "[]" operator overloading
    Item* secondItemOfFirstProduct = (*products[0])[1];
    cout << secondItemOfFirstProduct->getName() << endl;
    cout << secondItemOfFirstProduct->getMaterialCost() << endl;
    
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
