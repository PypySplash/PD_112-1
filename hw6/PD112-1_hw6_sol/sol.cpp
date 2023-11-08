#include <iostream>
#include <cstring>
using namespace std;

// template is used to generate generic code which can work with different data types
// without having to rewrite it for each specific type.
template <typename T>
struct Node { // node is the element for linked list
    T* data;
    struct Node* next;
    struct Node* prev;
    Node() {    // constructor of struct Node, initialize all pointers to null pointer
        data = nullptr;
        next = nullptr;
        prev = nullptr;
    }
    ~Node() {   // destructor of struct Node, point all pointers to null pointer
        next = nullptr;
        prev = nullptr;
        data = nullptr;
    }
};

typedef Node<struct Station> StatNode;  // use typedef to create alias for Node<struct Station>

template <typename T>
struct List { // use linked list to implement an dynamic array with uncertain length
    T* head;
    T* tail;
    T* cursor;
    List() { // constructor of struct List, initialize all pointers to null pointer
        head = nullptr;
        tail = nullptr;
        cursor = nullptr;
    }
    ~List() { // destructor of struct List, release all nodes and free all pointers
        T* tmp;
        cursor = head;
        while (cursor != nullptr) {
            tmp = cursor->next;
            delete cursor;
            cursor = tmp;
        }
        head = nullptr;
        tail = nullptr;
        cursor = nullptr;
    }
};

typedef List<StatNode> StatList; // use typedef to create alias for List<StatNode>

typedef struct Station {
    int id;                 // record identifier for convienience
    int capacity;           // station capacity
    int benefit;            // record total benefit created by this station, it is the sum of (number of car * car fee) for each car type in this station
    StatList* distGroups;   // record list of 3 distance groups
    int* groupBenefit;      // record total value created by neighber station, it is the sum of (number of car * car fee) for each car type in same distance group
    void appendStatNode(struct Station* station, int distance); // append a new station to specific groups depending on distance
    void appendToStatList(struct Station* station, int list);   // append a new station to the groups
    Station() {             // constructor of struct Station, initialize all variables
        id = 0;
        capacity = 0;
        benefit = 0;
        distGroups = new StatList[3];
        groupBenefit = new int[3];
        for (int i = 0; i < 4; i++) {
            groupBenefit[i] = 0;
        }
    }
    ~Station(){             // destructor of struct List, release all dynamic arrays
        delete [] distGroups;
        distGroups = nullptr;
        delete [] groupBenefit;
        groupBenefit = nullptr;
    }
} Station;

typedef struct CarType {
    int fee;                    // cartype fee
    int num;                    // number of car has not been used
    double* utilizationRate;    // utilization rate for each station 
    int* carCount;              // number of car for each station
    CarType(){                  // constructor of struct CarType, initialize all variables
        fee = 0;
        num = 0;
        utilizationRate = nullptr;
        carCount = nullptr;
    }
    ~CarType(){                 // destructor of struct CarType, release all dynamic arrays
        delete [] utilizationRate;
        utilizationRate = nullptr;
        delete [] carCount;
        carCount = nullptr;
    }
} CarType;

void taAlgorithm(Station* stations, CarType* carTypes, int statNum, int typeNum, double* declineRates);
double updateValue(Station &station, CarType &carType, double oriValue, double* declineRates);
void updateInformation(Station &station, CarType* carTypes, double* declineRates, int carTypeId, int typeNum);
void calEffectCarType(CarType* carTypes, double declineRate, int stationID, int typeNum);

void printResult(CarType* carTypes, int typeNum, int statNum);

int main() {
    int typeNum = 0, statNum = 0, distance = 0;
    double* declineRates = new double[4];
    cin >> typeNum >> statNum;
    for (int i = 0; i < 4; i++) {
        cin >> declineRates[i];
    }
    Station* stations = new Station[statNum];
    CarType* carTypes = new CarType[typeNum];
    for (int i = 0; i < typeNum; i++) {
        cin >> carTypes[i].fee;
    }
    for (int i = 0; i < typeNum; i++) {
        cin >> carTypes[i].num;
    }
    for (int i = 0; i < statNum; i++) {
        cin >> stations[i].capacity;
        stations[i].id = i;
    }
    for (int i = 0; i < typeNum; i++) {
        carTypes[i].utilizationRate = new double[statNum];
        carTypes[i].carCount = new int[statNum];
        for (int j = 0; j < statNum; j++) {
            cin >> carTypes[i].utilizationRate[j];
            carTypes[i].carCount[j] = 0;
        }
    }
    for (int i = 0; i < statNum; i++) {
        for (int j = 0; j < statNum; j++) {
            cin >> distance;
            stations[i].appendStatNode(&stations[j], distance);
        }
    }
    taAlgorithm(stations, carTypes, statNum, typeNum, declineRates);
    printResult(carTypes, typeNum, statNum);

    // delete all dynamic arrays
    delete [] declineRates;
    delete [] stations;
    delete [] carTypes;
    declineRates = nullptr;
    stations = nullptr;
    carTypes = nullptr;
}

void printResult(CarType* carTypes, int typeNum, int statNum) {
    for (int i = 0; i < typeNum; i++) {
        for (int j = 0; j < statNum; j++) {
            if (j == 0) {
                cout << carTypes[i].carCount[j];
            } else {
                cout << "," << carTypes[i].carCount[j];
            }
        }
        if (i != typeNum - 1) {
            cout << endl;
        }
    }
}

void Station::appendStatNode(struct Station* station, int distance) { // group by distance
    if ( distance >= 1 && distance <= 300 ) {
        appendToStatList(station, 0);
    } else if ( distance >= 301 && distance <= 500 ) {
        appendToStatList(station, 1);
    } else if ( distance >= 501 && distance <= 1000 ) {
        appendToStatList(station, 2);
    }
}

void Station::appendToStatList(struct Station* station, int list){  // append a new node to the list
    StatNode* newStatNode = new StatNode;
    newStatNode->data = station;
    if (distGroups[list].head == nullptr) {
        distGroups[list].head = newStatNode;
    } else {
        distGroups[list].tail->next = newStatNode;
        newStatNode->prev = distGroups[list].tail;
    }
    distGroups[list].tail = newStatNode;
}

void taAlgorithm(Station* stations, CarType* carTypes, int statNum, int typeNum, double* declineRates) {
    double maxValue = 0, value = 0, newValue = 0;
    int targetCarType = 0, targetStation = 0;
    while (true) {
        for (int i = 0; i < statNum; i++) { // for each station
            for (int j = 0; j < typeNum; j++) { // for each type
                if (stations[i].capacity > 0 && carTypes[j].num > 0) { // if this station and this type both are available
                    newValue = updateValue(stations[i], carTypes[j], value, declineRates);  // put one car in station and calculate the new value
                    if (newValue > maxValue) {  // if update the max value, record the target station and target type
                        maxValue = newValue;
                        targetStation = i;
                        targetCarType = j;
                    }
                }
            }
        }
        if (maxValue == value) { // if value doesn't change
            break;
        } else {
            stations[targetStation].capacity --; // station capacity -1
            carTypes[targetCarType].num --; // number of car -1
            carTypes[targetCarType].carCount[targetStation] ++; // the number of car in target station + 1
            updateInformation(stations[targetStation], carTypes, declineRates, targetCarType, typeNum); // update utilization rate and benefit
            value = maxValue;
        }
    }
}

double updateValue(Station &station, CarType &carType, double oriValue, double* declineRates) {
    oriValue += carType.utilizationRate[station.id] * carType.fee; // increased value caused by new car
    oriValue -= declineRates[0] * station.benefit; // decreased value caused by new car in current station
    for (int i = 0; i < 3; i++) { // decreased value caused by new car in three type of distance group
        oriValue -= declineRates[i+1] * station.groupBenefit[i]; // all the car type in same distance will decrease the same rate of benefit
    }
    return oriValue;
}

void updateInformation(Station &station, CarType* carTypes, double* declineRates, int carTypeId, int typeNum) {
    calEffectCarType(carTypes, declineRates[0], station.id, typeNum); // update the car type's utilization rate in this station
    station.benefit += carTypes[carTypeId].fee; // update benefit of this station
    for (int i = 0; i < 3; i++) {
        station.distGroups[i].cursor = station.distGroups[i].head;
        while (station.distGroups[i].cursor != nullptr) {
            calEffectCarType(carTypes, declineRates[i+1], station.distGroups[i].cursor->data->id, typeNum); // update the car type's utilization rate in three type of distance group
            station.distGroups[i].cursor->data->groupBenefit[i] += carTypes[carTypeId].fee; // update benefit for three type of distance group
            station.distGroups[i].cursor = station.distGroups[i].cursor->next;
        }
    }
}

void calEffectCarType(CarType* carTypes, double declineRate, int stationID, int typeNum) {
    for (int i = 0; i < typeNum; i++) { // update all utilization rate for each car type
        carTypes[i].utilizationRate[stationID] = carTypes[i].utilizationRate[stationID] - declineRate;
    }
}