#include <iostream>
using namespace std;

// ============================================
// Classes (p. 14)

class MyVector
{
private:
  int n; 
  int* m; 
public:
  void init();
  void init(int dim); 
  void init(int dim, int value);  
  void print(); 
};

void MyVector::init() 
{
  n = 0;
  m = nullptr;
}
void MyVector::init(int dim) 
{
  init(dim, 0);
}
void MyVector::init(int dim, int value) 
{
  n = dim;
  m = new int[n]; 
  for(int i = 0; i < n; i++)
    m[i] = value;
}