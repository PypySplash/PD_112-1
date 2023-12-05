#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

// Page 5
class Entity
{
// private:
protected:
  string id;
  bool isOn; 
  bool isSer; // means nothing if isOn == false
  double lon;
  double lat;
public:
  Entity(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Entity::print()
{
  cout << this->id << ": " << this->isOn << " " << this->isSer
       << " (" << this->lon << ", " << this->lat << ")" << endl;
}

// Page 7
// int main()
// {
//   Entity a("5HE-313", true, true, 0, 0);
//   a.print();
//   return 0;
// }

// Page 8

class Car : public Entity  // 繼承
{
private:
public:
  Car(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
  : Entity(id, isOn, isSer, lon, lat)  // 指定呼叫 parents 的 constructor（重要！！！！
//   : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Car::print()  // 總之就是要完成一個print，內容是什麼可以自己修改
{
    cout <<  this->id << ",";
    if (this->isOn == true)
    {
        if (this->isSer == true)
        {
            cout << "isSer";
        }

    }
}
// Page 10

// class Car : public Entity
// {
// private:
// public:
//   Car(string id, bool isOn, bool isSer, double lon, double lat);
// //   void print(); 
// };

// Page 11 

// int main()
// {
//   Car* cars[20000] = {0};
//   int carCnt = 0;
//   cars[0] = new Car("5HE-313", true, true, 0, 0);
//   carCnt++;
//   cars[1] = new Car("LPA-039", true, false, 1, 1);  
//   carCnt++;
//   for(int i = 0; i < carCnt; i++)
//     cars[i]->print();

//   return 0;
// }

class CarArray
{
private:
  int capacity; // initialize it to 20000; may change later
  int cnt;
//   Car* cars; 
  Car** carPtr;
public:
  CarArray();
  // CarArray(const CarArray& ca);  // not needed
  // operator=(const CarArray& ca); // in this problem
  ~CarArray();
  bool add(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

CarArray::CarArray()
{
  this->cnt = 0;
  this->capacity = 20000;
//   this->cars = new Car[this->capacity];
  this->carPtr = new Car*[this->capacity];
}

// CarArray::CarArray()
// {
//   this->cnt = 0;
//   this->capacity = 20000;
//   this->carPtr = new Car*[this->capacity];
// }

CarArray::~CarArray()
{
  for(int i = 0; i < this->cnt; i++)
    delete this->carPtr[i];
  delete [] this->carPtr;
}

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
    if (this->cnt < this->capacity)
    {
        this->carPtr[this->cnt] = new Car(id, isOn, isSer, lon, lat);
        this->cnt++;
        return true;
    }
    else return false;
}

void CarArray::print()
{

}

// int main()
// {
//   CarArray ca;
//   ca.add("5HE-313", true, true, 0, 0);
//   ca.add("LPA-039", true, false, 1, 1);  
//   ca.print();
  
//   return 0;
// }

class EntityArray
{
protected:
    int capacity;
    int cnt;
    Entity** entityPtr;
public:
    EntityArray();
    // EntityArray(const EntityArray& ea);
    // operator=(const EntityArray& ea);
    ~EntityArray();
    virtual bool add(string id, bool isOn, bool isSer, double lon, double lat) = 0;
    void print();
};
class CarArray : public EntityArray
{
private:
public:
    bool add(string id, bool isOn, bool isSer, double lon, double lat);
};

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
    if (this->cnt < this->capacity)
    {
        this->entityPtr[this->cnt] = new Car(id, isOn, isSer, lon, lat);
        this->cnt++;
        return true;
    }
    else return false;
}
