#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

void AccountManager::ProcessLogin()
{
	// accountLock
	// 쓰레드 2 (1차 Lock)
	lock_guard<mutex> guard(_mutex);

	// userLock
	User* user = UserManager::instance()->GetUser(100);

	// TODO
} 