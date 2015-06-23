#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

LPWSTR fromCharToLpwstr(const char* path)
{
    size_t requiredSize = 0;
    mbstowcs_s(&requiredSize, NULL, 0, path, 0);

    wchar_t* wcs = new wchar_t[requiredSize + 1];
    mbstowcs_s(&requiredSize, wcs, requiredSize + 1, path, requiredSize);
    return wcs;
}

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    // Set the folder for the binary file
    LPWSTR ptr = fromCharToLpwstr("bin\\yourBinary");
    
    //Set the folder for the Qt DLL's
    LPWSTR dllPath = fromCharToLpwstr("dlls\\");

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

//     Start the child process.
    if( !CreateProcess( NULL,   // No module name (use command line)
        ptr,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        exit(0);
    }

    // Wait until child process exits.
//    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles.

    if (pi.hProcess != nullptr) {
//        CloseHandle( pi.hProcess );
//        CloseHandle( pi.hThread );
    }

    if(ptr != nullptr) {
        delete ptr;
    }

    if(dllPath != nullptr){
        delete dllPath;
    }

    exit(0);
}
