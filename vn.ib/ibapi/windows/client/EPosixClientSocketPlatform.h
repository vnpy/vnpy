/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef eposixclientsocketcommon_def
#define eposixclientsocketcommon_def

#ifdef _WIN32

	// Windows
	// includes
	#include <WinSock2.h>
	#include <time.h>

	// defines
	#if _MSC_VER < 1700
	#define EISCONN WSAEISCONN
	#define EWOULDBLOCK WSAEWOULDBLOCK
	#define ECONNREFUSED WSAECONNREFUSED
	#else
	#pragma comment(lib, "ws2_32.lib")
	#endif

	// helpers
	inline bool SocketsInit( void) {
		WSADATA data;
		return ( !WSAStartup( MAKEWORD(2, 2), &data));
	};
	inline bool SocketsDestroy() { return ( !WSACleanup()); };
	inline int SocketClose(int sockfd) { return closesocket( sockfd); };

	inline bool SetSocketNonBlocking(int sockfd) { 
		unsigned long mode = 1;
		return ( ioctlsocket( sockfd, FIONBIO, &mode) == 0);
	};

#else
	// LINUX
	// includes

	#include <arpa/inet.h>
	#include <netdb.h>
	#include <errno.h>
	#include <sys/select.h>
	#include <sys/fcntl.h>
	#include <unistd.h>

	// helpers
	inline bool SocketsInit() { return true; };
	inline bool SocketsDestroy() { return true; };
	inline int SocketClose(int sockfd) { return close( sockfd); };

	inline bool SetSocketNonBlocking(int sockfd) { 
		// get socket flags
		int flags = fcntl(sockfd, F_GETFL);
		if (flags == -1)
			return false;

		// set non-blocking mode
		return ( fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == 0);
	};

#endif

#endif
