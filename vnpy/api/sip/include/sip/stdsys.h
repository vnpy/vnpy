#pragma once

#ifdef _WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS 1
#endif
#	pragma warning (disable : 4996)
#	pragma warning (disable : 4200)
#	ifndef _WIN32_WINNT
#		define _WIN32_WINNT 0x0600	//0x600=win7/2008
#	endif
#	include <process.h>
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#else
#	include <unistd.h>
#endif