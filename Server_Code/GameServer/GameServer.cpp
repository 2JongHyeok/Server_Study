#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <future>

int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100'000; ++i)
		sum += i;

	return sum;
}

int main()
{
	// 동기(synchronous) 실행
	//int64 sum = Calculate();
	//cout << sum << endl;

	// std::future
	{
		// 1) deferred -> lazy evaluation 지연해서 실행하세요
		// 2) async -> 별도의 쓰레드를 만들어서 실행하세요
		// 3) deferred | async -> 둘 중 알아서 골라주세요
		std::future<int64> future = std::async(std::launch::deferred, Calculate);
		
		// TODO
		
		int64 sum = future.get();	// 결과물이 이제서야 필요하다!
		
		class Knight
		{
		public:
			int64 GetHp() { return 100; }
		};
		Knight knight;
		std::future<int64> future2 = std::async(std::launch::async, &Knight::GetHp, knight);	// knight.GetHp()
	}
}