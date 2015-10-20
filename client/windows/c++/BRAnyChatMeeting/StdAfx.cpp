// stdafx.cpp : source file that includes just the standard includes
//	BRAnyChatMeeting.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



/**
 *	判断文件是否存在
 *	@param strFilePath 需要判断的文件路径
 *	@return 文件存在返回TRUE，否则返回FALSE
 */
BOOL IsFileExist(LPCTSTR lpFilePath)
{
	BOOL bExist = FALSE;
#ifdef WIN32
	HANDLE hFile = CreateFile( lpFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}
#else
    bExist = access(lpFilePath, R_OK) == 0;
#endif
	return bExist;
}