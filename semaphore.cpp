#include <stdio.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>


using namespace std;
bool shipment_available() {return true;}
class semaphore {
    int count;
    mutex m;
    condition_variable cv;
public:
    semaphore(int count)
    {
    	this->count = count;
    }

    void wait()
    {
    	unique_lock<mutex> lck(m);
    	cv.wait(lck, [=](){return (count > 0);});
    	--count;
    }

    void post()
    {
    	unique_lock<mutex> lck(m);
    	count++;
    	cv.notify_all();
    }

};

void printFirst()
{
	cout << "first " << endl;
}

void printSecond()
{
	cout << "second " << endl;
}

void printThird()
{
	cout << "third " << endl;
}


class Foo {
public:
    Foo(): s2(0), s1(0) {
        
    }

    semaphore s1;
    semaphore s2;

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        s1.post();
    }

    void second(function<void()> printSecond) {
        
        s1.wait();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        s2.post();
    }

    void third(function<void()> printThird) {
        
        s2.wait();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

void func(Foo* t, int index)
{
	if(0 == index)
	{
		t->first(printFirst);
	}
	else if(1 == index)
	{
		t->second(printSecond);
	}
	else
	{
		t->third(printThird);
	}
}


int main()
{
	Foo f;
    std::thread t1(func, &f, 0);
    std::thread t2(func, &f, 1);
    std::thread t3(func, &f, 2);


    t1.join();
    t2.join();
    t3.join();


    return 1;
}
