#include <iostream>
using namespace std;

// ============================================
// Classes (p. 20)

class MyVector
{
private:
  int n; 
  int* m; 
public:
  MyVector();
  MyVector(int dim, int value = 0); 
  void print(); 
};

MyVector::MyVector()
{
  n = 0;
  m = nullptr;
}
MyVector::MyVector(int dim, int value)
{
  n = dim;
  m = new int[n]; 
  for(int i = 0; i < n; i++)
    m[i] = value;
}