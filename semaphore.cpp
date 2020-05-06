#include <stdio.h>
#include <iostream>
#include <mutex>
#include <condition_varaiable>


using namespace std;

class semaphore {
    unsigned int count;
    mutex m;
    condition_varaiable cv;
    semaphore(unsigned int count)
    {
    }

    


}



int main()
{
    cout << "hello world";
    return 1;
}
