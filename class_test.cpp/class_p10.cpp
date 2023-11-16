#include <iostream>
using namespace std;

// ============================================
// Classes (p. 10)

class MyVector
{
private:
  int n; 
  int* m; 
public:
  void init(int dim); 
  void print(); 
};

int main()
{
  MyVector v;
  v.init(5); // OK!
  delete [] v.m;
  return 0;
}

void MyVector::init(int dim)
{
  n = dim;
  m = new int[n]; 
  for(int i = 0; i < n; i++)
    m[i] = 0;
}
void MyVector::print()
{
  cout << "(";
  for(int i = 0; i < n - 1; i++)
    cout << m[i] << ", ";
  cout << m[n-1] << ")\n";
}