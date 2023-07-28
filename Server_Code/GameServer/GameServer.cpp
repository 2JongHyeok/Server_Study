﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

atomic <int32> sum = 0;

void Add()
{
	for (int32 i = 0; i < 1'000'000; ++i)
	{
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 1'000'000; ++i)
	{
		sum--;
	}
}

int main()
{
	Add();
	Sub();
	cout << sum << endl;

	std::thread t1(Add);
	std::thread t2(Sub);
	t1.join();
	t2.join();
	cout << sum << endl;
}