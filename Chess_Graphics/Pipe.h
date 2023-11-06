#pragma once
#include <iostream>
#include <Windows.h>

#define BUFFER_SIZE 1024

class Pipe
{
private:
	HANDLE _hPipe;
	LPTSTR _strPipeName;

	std::string _strMsgToLogic;
	std::string _strMsgFromLogic;

public:
	Pipe() { _strPipeName = (LPTSTR)TEXT("\\\\.\\pipe\\chessPipe"); _strMsgFromLogic = ""; _strMsgToLogic = ""; }

	void setMessage(std::string msg) { _strMsgToLogic = msg; _strMsgFromLogic.clear(); } // sets message to logic
	std::string getMessage() { return _strMsgFromLogic; } // returns message from logic

	bool serve();
	bool sendMessageToLogics(char* msg);
	std::string getMessageFromLogics();

	void close() { DisconnectNamedPipe(_hPipe); CloseHandle(_hPipe); }
};

