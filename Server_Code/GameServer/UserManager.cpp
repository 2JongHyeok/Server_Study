#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave()
{
	// userLock
	// 쓰레드 1 (1차 Lock)
	lock_guard<mutex> guard(_mutex); // 락 걸어라, 그리고 이 함수가 끝나면 락 풀어라

	// accountLock
	Account* account =  AccountManager::instance()->GetAccount(100);

	// TODO
}