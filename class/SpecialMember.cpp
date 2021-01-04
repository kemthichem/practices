#include <iostream>

using namespace std;
class A
{
public:
    int data;
    A() : data(0)
    {
        cout << "A's constructor called" << endl;
    }

    A(const A& a)
    {
        cout << "A's copy constructor called" << endl;
        data = a.data;
    }
    //A(const A&& a) = delete;
    // {
    //     cout << "A's move constructor called" << endl;
    // }

    ~A()
    {
        cout << "A's destructor called" << endl;
    }
};

A func()
{
    A a;
    return a;
}

int main()
{
    //A a;
    //a.data = 1;
    A b = func();
    cout << b.data << endl;

    return 1;
}