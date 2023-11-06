#include "Pipe.h"

bool Pipe::serve()
{
    _hPipe = CreateNamedPipe(_strPipeName,                  // Pipe name
        PIPE_ACCESS_DUPLEX,                                 // Read and write access
        PIPE_TYPE_BYTE |                                    // Pipe type (byte-oriented)
        PIPE_READMODE_BYTE |                                // Read mode (byte-oriented)
        PIPE_WAIT,                                          // Pipe's behavior (wait for data)
        1,                                                  // Maximum instances number
        BUFFER_SIZE,                                        // Output buffer size
        BUFFER_SIZE,                                        // Input buffer size
        NMPWAIT_USE_DEFAULT_WAIT,                           // Default client timeout
        NULL);                                              // Default security attributes

    while (!ConnectNamedPipe(_hPipe, NULL)) // waiting for connection
    {
    }

    while (true) { // server pipe always working
        if (_strMsgToLogic == "quit")
            return true;

        if (_hPipe != INVALID_HANDLE_VALUE)
        {

            while (_strMsgToLogic == "") { Sleep(500); }

            if (!sendMessageToLogics(&_strMsgToLogic[0]))
                std::cerr << "Pipe fail, closing.." << std::endl;
            else {
                _strMsgToLogic.clear();
                _strMsgFromLogic = getMessageFromLogics();
            }
        }
    }
    
}

bool Pipe::sendMessageToLogics(char* arg_msg)
{
    char* lchRequest = arg_msg;
    DWORD lcbBytesWritten, lcbRequestBytes;

    lcbRequestBytes = sizeof(TCHAR) * (strlen((lchRequest)) + 1);

    BOOL lResult = WriteFile(			// Write to the pipe.
        _hPipe,						// Handle of the pipe
        lchRequest,					// Message to be written
        lcbRequestBytes,				// Number of bytes to write
        &lcbBytesWritten,			// Number of bytes written
        NULL);						// Not overlapped 

    if (!lResult || lcbRequestBytes != lcbBytesWritten)
    {
        std::cerr << "WriteFile failed error: " << GetLastError() << std::endl;
        return false;
    }

    std::cout << "Sending " << lcbRequestBytes << " bytes as Message: " << lchRequest << std::endl;

    return true;
}

std::string Pipe::getMessageFromLogics()
{
    DWORD lcbBytesRead;
    DWORD lcbReplyBytes;
    char lReply[BUFFER_SIZE];

    lcbReplyBytes = sizeof(char) * BUFFER_SIZE;

    BOOL bResult = ReadFile(	// Read from the pipe.
        _hPipe,					// Handle of the pipe
        lReply,				    // Buffer to receive the reply
        lcbReplyBytes,			// Size of buffer 
        &lcbBytesRead,			// Number of bytes read 
        NULL);					// Not overlapped 

    if (!bResult && GetLastError() != ERROR_MORE_DATA)
    {
        std::cerr << "ReadFile failed error: " << GetLastError() << std::endl;
        return "";
    }
    std::cout << "Recieving " << lcbReplyBytes << " bytes as Message: " << lReply << std::endl;

    return lReply;
}
