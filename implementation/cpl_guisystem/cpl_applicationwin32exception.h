#ifndef __CPL_APPLICATIONWIN32EXECEPTIONHANDLER_H__
#define __CPL_APPLICATIONWIN32EXECEPTIONHANDLER_H__

class cpl_ApplicationWin32ExceptionHandler {
private:
    // entry point where control comes on an unhandled exception
    static LONG WINAPI MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo );

    // where report info is extracted and generated 
    static void GenerateExceptionReport( PEXCEPTION_POINTERS pExceptionInfo );

    // Helper functions
    static LPTSTR GetExceptionString( DWORD dwCode );
    static BOOL GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset );
    static void IntelStackWalk( PCONTEXT pContext );
    static int __cdecl _tprintf(const TCHAR * format, ...);

    // Variables used by the class
    static TCHAR m_szLogFileName[MAX_PATH];
    static LPTOP_LEVEL_EXCEPTION_FILTER m_previousFilter;
    static HANDLE m_hReportFile;

public:    
    cpl_ApplicationWin32ExceptionHandler( );
    ~cpl_ApplicationWin32ExceptionHandler( );

    void SetLogFileName( PTSTR pszLogFileName );
};

extern cpl_ApplicationWin32ExceptionHandler g_ExceptionHandler;   //  global instance of class

#endif //__CPL_APPLICATIONWIN32EXECEPTIONHANDLER_H__
