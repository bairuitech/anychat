/**
 *	AnyChat Platform SDK Include file
 */

#if !defined(GV_SDK_DEFINE__)
#define GV_SDK_DEFINE__


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <sys/times.h>
#include <wchar.h>
#include <stdint.h>


typedef unsigned int UINT;
typedef double DOUBLE;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef short   SHORT;
typedef unsigned int DWORD;
typedef unsigned int SOCKET;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
typedef char CHAR;
typedef unsigned char UCHAR;
typedef char TCHAR;
typedef wchar_t WCHAR;
typedef char* PCHAR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef int INT;
typedef long    BOOL;

#define LPDWORD DWORD*
#define HWND    void*
#define HDC     DWORD
#define CALLBACK
#define FAR
#define VOID    void
#define LPVOID  void*
#define LPBYTE  unsigned char*
#define LPCHAR  char*
#define LPCSTR  const char*
#define LPCTSTR const char*
#define TRUE    1
#define FALSE   0
#define WPARAM  DWORD
#define LPARAM  DWORD


typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
}BITMAPINFOHEADER,*LPBITMAPINFOHEADER;

typedef struct tagWAVEFORMATEX{
  WORD  wFormatTag;
  WORD  nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD  nBlockAlign;
  WORD  wBitsPerSample;
  WORD  cbSize;
}WAVEFORMATEX,*LPWAVEFORMATEX;


#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))




//摄像头状态定义
#define GV_CAMERA_STATE_NULL	0				///< 没有摄像头
#define GV_CAMERA_STATE_NORMAL	1				///< 有摄像头但没有打开
#define GV_CAMERA_STATE_OPEN	2				///< 摄像头已打开

// Mic活动状态定义
#define GV_AUDIO_STATE_NULL		0				///< 没有安装声卡
#define GV_AUDIO_STATE_NORMAL	1				///< 有声卡，但没有打开Mic
#define GV_AUDIO_STATE_OPEN		2				///< Mic已打开

// 客户端聊天模式定义
#define GV_CHATMODE_PUBLIC		0				///< 公聊模式
#define GV_CHATMODE_PRIVATE		1				///< 私聊模式，接收不到其它用户的语音和视频数据，仅能接收到自己私聊对象的语音和视频数据，文字消息不受模式影响


#endif // !defined(GV_SDK_DEFINE__)
