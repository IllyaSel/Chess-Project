#include "Pipe.h"

bool Pipe::connect()
{
    _hPipe = CreateFile(_strPipeName,       // Pipe name
        GENERIC_READ | GENERIC_WRITE,       // Read and write access
        0,                                  // No sharing
        NULL,                               // Default security atributes
        OPEN_EXISTING,                      // Open existing pipe
        0,                                  // Default attributes
        NULL                                // No template file
    );

    if (_hPipe != INVALID_HANDLE_VALUE) // If pipe handle is valid
        return true;

    if (GetLastError() != ERROR_PIPE_BUSY   // Exit if an error other than ERROR_PIPE_BUSY occurs
        ||
        !WaitNamedPipe(_strPipeName, 5000)) // All pipe instances are busy, wait for 5 seconds
    {
        std::cerr << "Unnable to open pipe " << _strPipeName <<
            " error: " << GetLastError() << std::endl;
        return false;
    }

    std::cout << "Pipe " << _strPipeName << " connected successfully" << std::endl;
    return true;
}


bool Pipe::sendMessageToGraphics(char* arg_msg)
{
    char* lRequest = arg_msg;
    DWORD lcbBytesWritten, lcbRequestBytes;

    lcbRequestBytes = sizeof(TCHAR) * (strlen((lRequest)) + 1);

    BOOL lResult = WriteFile(		// Write to the pipe.
        _hPipe,						// Handle of the pipe
        lRequest,					// Message to be written
        lcbRequestBytes,		    // Number of bytes to write
        &lcbBytesWritten,			// Number of bytes written
        NULL);						// Not overlapped 

    if (!lResult || lcbRequestBytes != lcbBytesWritten)
    {
        std::cerr << "WriteFile failed error: " << GetLastError() << std::endl;
        return false;
    }

    std::cout << "Sending " << lcbRequestBytes << " bytes as Message: " << lRequest << std::endl;

    return true;
}


std::string Pipe::getMessageFromGraphics()
{
    DWORD lcbBytesRead;
    DWORD lcbReplyBytes;
    char lReply[BUFFER_SIZE];

    lcbReplyBytes = sizeof(char) * BUFFER_SIZE;

    BOOL lResult = ReadFile(	// Read from the pipe.
        _hPipe,					// Handle of the pipe
        lReply,				    // Buffer to receive the reply
        lcbReplyBytes,			// Size of buffer 
        &lcbBytesRead,			// Number of bytes read 
        NULL);					// Not overlapped 

    if (!lResult && GetLastError() != ERROR_MORE_DATA)
    {
        std::cerr << "ReadFile failed error: " << GetLastError() << std::endl;
        return "";
    }
    std::cout << "Recieving " << lcbReplyBytes << " bytes as Message: " << lReply << std::endl;

    return lReply;
}
