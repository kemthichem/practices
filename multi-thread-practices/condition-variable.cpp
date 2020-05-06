#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
bool isStart = false;

void printNumber(int n)
{
   std::unique_lock<std::mutex> l(m);
   if (!isStart)
      cv.wait(l);
   std::cout << "Number is :" << n << std::endl;
}

void go()
{
   std::unique_lock<std::mutex> l(m);
   isStart = true;
   cv.notify_all();
}

int main()
{

   std::thread threadArr[10];
   
   for (int i = 0; i < 10; ++i)
   {
      threadArr[i] = std::thread(printNumber, i);
   }

   std::cout << "Start thread go conditions" << std::endl;
   go();

   for (size_t i = 0; i < 10; i++)
   {
      threadArr[i].join();
   }

   return 0;
}
