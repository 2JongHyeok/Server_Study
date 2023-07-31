#pragma once
#include <mutex>

class User
{
	// 10000
};

class UserManager
{
public:
	static UserManager* instance()
	{
		static UserManager instance;
		return &instance;
	}

	User* GetUser(int32 id)
	{
		// 쓰레드 2 (2차 Lock)
		lock_guard<mutex> guard(_mutex);
		// 뭔가 갖고 옴
		return nullptr;
	}

	void ProcessSave();

private:
	mutex _mutex;
};

