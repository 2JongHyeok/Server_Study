#pragma once
#include <mutex>

class Account
{

};

class AccountManager
{
public:
	static AccountManager* instance()
	{
		static AccountManager instance;
		return &instance;
	}

	Account* GetAccount(int32 id)
	{
		// 쓰레드 1 위치
		// 쓰레드1 2차 Lock
		lock_guard<mutex> guard(_mutex); // 락 걸고 리턴하면 풀어라
		// 뭔가를 갖고옴
		return nullptr;
	}

	void ProcessLogin();

private:
	mutex _mutex;
	// map<int32, Account*> _accounts;
};

