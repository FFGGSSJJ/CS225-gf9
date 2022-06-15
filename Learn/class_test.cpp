#include <stdio.h>
#include <iostream>
using namespace std;

class ParentClass {
public:
    int a, b;
    ParentClass();
    ParentClass(int x, int y): a(x), b(y) {}
    int memfunc (int x, int y) {
        cout << "the numbers are " << x << " and " << y << "\n";
        return 0;
    }
};

class ChildClass:public ParentClass{
public:
    int a, b;
    ChildClass(int x): a(x) {
        b = x*x;
    }
    
};

int main(){
    ParentClass a(10,10);
    ChildClass b(10);
    a.memfunc(1, 2);
    //b.memfunc(1);
    //printf("the object are %d and %d\n", a.a, a.b);
}