#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE handle;

void Producer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		::SetEvent(handle);
		this_thread::sleep_for(10000ms);
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(handle, INFINITE);
		//::ResetEvent(handle); (만약 CreateEvent의 두번째 인자를 True로 바꾸면 이 코드로 직접 바꿔줘야함)
		// Non-Signal

		unique_lock<mutex> lock(m);
		if (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
	// 커널 오브젝트
	// Usage Count
	// Signal ( 파란불 ) / Non-Signal (빨간불) << bool
	// Auto / Manual << bool
	handle = ::CreateEvent(NULL/*보안속성*/, FALSE/*bManualReset*/, FALSE/*bInitialState*/, NULL);
	
	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);
}