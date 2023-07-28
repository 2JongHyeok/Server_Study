#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>

void HelloThread()
{
    cout << "Hello Thread" << endl;
}

int main()
{
    std::thread t(HelloThread);

    cout << "Hello Main" << endl;
    
    t.join();   // main 쓰레드가 t쓰레드가 끝날때 까지 기다려주는 코드
}