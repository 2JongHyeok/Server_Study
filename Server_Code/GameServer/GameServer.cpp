﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

// [1][2][3][][][][][][][][][][][]
vector<int32> v;

// Mutal Exclusive ( 상호베타적 )
mutex m;

// RAII ( Resource Acquisition is Initialization )
template<typename T>
class LockGuard
{
public:
	LockGuard(T& m)
	{
		_mutex = &m;
		_mutex->lock();
	}

	~LockGuard()
	{
		_mutex->unlock();
	}
private:
	T* _mutex;
};

void Push()
{
	for (int32 i = 0; i < 10000; ++i)
	{
		// 자물쇠 잠그기
		LockGuard<std::mutex> lockGuard(m);
		//m.lock();

		v.push_back(i);
		
		// 자물쇠 풀기
		//m.unlock();
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}