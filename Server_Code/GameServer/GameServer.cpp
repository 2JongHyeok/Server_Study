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
    
    int32 count = t.hardware_concurrency();   // CPU 코어 개수를 추출하는 함수
    auto id = t.get_id();     // 쓰레드마다 주어지는 id 확인
    t.detach();     // std::thread 객체에서 실제 쓰레드를 분리
    t.joinable();   // t 객체가 살아있는지 아닌지 확인하기 위한 코드
    // ex)
    // if (t.joinavle())
    //    t.join();
    t.join();   // main 쓰레드가 t쓰레드가 끝날때 까지 기다려주는 코드
}