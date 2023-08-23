#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <future>
#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


int main()
{

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;


	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr; // Ipv4;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // < 니가 알아서 해줘
	serverAddr.sin_port = ::htons(7777);    // 80 : HTTP

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Bind ErrorCode : " << errCode << endl;
		return 0;
	}

	if (::listen(listenSocket, 10) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Bind ErrorCode : " << errCode << endl;
		return 0;
	}


	// ----------------------------------------

	while (true)
	{
	   SOCKADDR_IN clientAddr; // IPv4
	   ::memset(&serverAddr, 0, sizeof(serverAddr));
	   int32 addLen = sizeof(clientAddr);

	   SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addLen);
	   if (clientSocket == INVALID_SOCKET)
	   {
		   int32 errCode = ::WSAGetLastError();
		   cout << "Bind ErrorCode : " << errCode << endl;
		   return 0;
	   }

	   // 손님 입장!
	   char ipAddress[16];
	   ::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
	   cout << "Client Connected! IP = " << ipAddress << endl;

	   // TODO
	   while (true)
	   {
		   char recvBuffer[1000];

		   this_thread::sleep_for(1s);
		   
		   int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		   if (recvLen <= 0)
		   {
			   int32 errCode = ::WSAGetLastError();
			   cout << "Bind ErrorCode : " << errCode << endl;
			   return 0;
		   }

		   cout << "Recv Data! Data = " << recvBuffer << endl;
		   cout << "Recv Len! Data = " << recvLen << endl;

		  /* int32 resultCode = ::send(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		   if (resultCode == SOCKET_ERROR)
		   {
			   int32 errCode = ::WSAGetLastError();
			   cout << "Connect ErrorCode : " << errCode << endl;
			   return 0;
		   }*/
	   }
	}
	
	// ----------------------------------------


	// 윈속 종료
	::WSACleanup();
}
