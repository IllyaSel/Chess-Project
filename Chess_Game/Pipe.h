#pragma once
#include <iostream>
#include <Windows.h>

#define BUFFER_SIZE 1024

class Pipe
{
private:
	HANDLE _hPipe;
	LPTSTR _strPipeName;
public:
	Pipe() { _strPipeName = (LPTSTR)TEXT("\\\\.\\pipe\\chessPipe"); }

	bool connect();
	bool sendMessageToGraphics(char* msg);
	std::string getMessageFromGraphics();

	void close() { CloseHandle(_hPipe); }
};

