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





// ============================================
// Classes (p. 21)

int main()
{
  MyVector v1(1);
  MyVector v2(3, 8);
  v1.print(); // (0)
  v2.print(); // (8, 8, 8)
  return 0;
}





// ============================================
// Classes (p. 23)

class A
{
public:
  A() { cout << "A\n"; }
  ~A() { cout << "a\n"; }
};
class B
{
private:
  A a;
public:
  B() { cout << "B\n"; }
  ~B() { cout << "b\n"; }
};

int main()
{
  B b;
  return 0;
}





// ============================================
// Classes (p. 34)

class A
{
private:
  static int count;
public:
  A() { A::count++; }
  static int getCount() 
  { return A::count; }
};

int A::count = 0;

int main()
{
  A a1, a2, a3;
  cout << A::getCount() << "\n"; // 3
  return 0;
}





// ============================================
// Classes (p. 35)

class A
{
private:
  static int count;
public:
  A() { A::count++; }
  ~A() { A::count--; }
  static int getCount() 
  { return A::count; }
};

int A::count = 0;

int main()
{
  if(true)
    A a1, a2, a3;
  cout << A::getCount() << "\n"; // 0
  return 0;
}





// ============================================
// Classes (p. 43)

MyVector sum
  (MyVector v1, MyVector v2, MyVector v3)
{
  // assume that their dimensions are identical
  int n = v1.getN(); 
  int* sov = new int[n];
  for(int i = 0; i < n; i++) 
    sov[i] = v1.getM(i) + v2.getM(i) + v3.getM(i);
  MyVector sumOfVec(n, sov); 
  return sumOfVec; 
}

int MyVector::getN() 
{ return n; }
int MyVector::getM(int i) 
{ return m[i]; }
MyVector::MyVector
  (int d, int v[])
{
  n = d;
  m = new int[d]; 
  for(int i = 0; i < n; i++)
    m[i] = v[i];
}





// ============================================
// Classes (p. 44)

MyVector sum(MyVector* v1, MyVector* v2, MyVector* v3)
{
  // assume that their dimensions are identical
  int n = v1->getN(); 
  int* sov = new int[n];
  for(int i = 0; i < n; i++) 
    sov[i] = v1->getM(i) + v2->getM(i) + v3->getM(i);
  MyVector sumOfVec(n, sov); 
  return sumOfVec; 
}





// ============================================
// Classes (p. 45)

MyVector cenGrav(MyVector& v1, MyVector& v2, MyVector& v3)
{
  // assume that their dimensions are identical
  int n = v1.getN(); 
  int* sov = new int[n];
  for(int i = 0; i < n; i++) 
    sov[i] = v1.getM(i) + v2.getM(i) + v3.getM(i);
  MyVector sumOfVec(n, sov); 
  return sumOfVec; 
}





// ============================================
// Classes (p. 47)

class A
{
private:
  int i;
public:
  A() { cout << "A"; }
};
void f(A a1, A a2, A a3)
{
  A a4;
}

int main()
{
  A a1, a2, a3; // AAA
  cout << "\n===\n";
  f(a1, a2, a3); // A
  return 0;
}





// ============================================
// Classes (p. 48)

int main()
{
  A a1, a2, a3; // AAA
  cout << "\n===\n"; 
  A a4 = a1; // nothing!
  return 0;
}





// ============================================
// Classes (p. 50)

class A
{
private:
  int i;
public:
  A() { cout << "A"; }
  A(const A& a) { cout << "a"; }
};

void f(A a1, A a2, A a3)
{
  A a4;
}
int main()
{
  A a1, a2, a3; // AAA
  cout << "\n===\n";
  f(a1, a2, a3); // aaaA
  return 0;
}





// ============================================
// Classes (p. 52)

MyVector::MyVector(const MyVector& v)
{
  n = v.n;
  m = new int[n]; // deep copy
  for(int i = 0; i < n; i++)
    m[i] = v.m[i];
}