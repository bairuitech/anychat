#if !defined(BR_ANYCHAT_SERVER_TYPEDEF_H__INCLUDE_)
#define BR_ANYCHAT_SERVER_TYPEDEF_H__INCLUDE_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



typedef unsigned int DWORD;
typedef char CHAR;
typedef char TCHAR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef int INT;
typedef long    BOOL;
typedef unsigned char BYTE;


#define LPDWORD DWORD*
#define CALLBACK __stdcall
#define VOID    void
#define LPVOID  void*
#define LPBYTE  unsigned char*
#define LPCHAR  char*
#define LPCSTR  const char*
#define LPCTSTR const char*
#define TRUE    1
#define FALSE   0



#endif //BR_ANYCHAT_SERVER_TYPEDEF_H__INCLUDE_
