// WriteFileManager.h: interface for the CWriteFileManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRITEFILEMANAGER_H__4B33A343_A7FF_4F50_B7F7_84CC37E3A798__INCLUDED_)
#define AFX_WRITEFILEMANAGER_H__4B33A343_A7FF_4F50_B7F7_84CC37E3A798__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CriticalLock.h"
#include <list>
using namespace std;

#define  MAX_DATA_LEN			(1024)

#define  FILE_ACTION_TYPE_READ		(0)
#define  FILE_ACTION_TYPE_WRITE		(1)
#define  FILE_ACTION_TYPE_NOTIFY	(2)

typedef struct tagContextInfo
{
	OVERLAPPED		overlapped;
	BYTE			bType;
	DWORD			dwDataLen;
	unsigned char*	lpData;
}ContextInfo,*PContextInfo;


class CWriteFileManager  
{
public:
	CWriteFileManager();
	virtual ~CWriteFileManager();

	bool	OpenFile(const char* lpFilePath,HANDLE hIocpHandle);
	bool	CloseFile();
	void	PushWriteData(PContextInfo pContext);
	void	WriteNextData();

private:
	bool	WriteData(PContextInfo pContext);
	bool	WriteEmptyData();
	
private:
	HANDLE						m_hFile;
	CCriticalLock				m_lock;
	list<PContextInfo>			m_dataInfoList;
	ContextInfo					m_notifyContext;
	volatile	bool			m_bIsBegin;
	volatile	bool			m_bIsEmpty;
	HANDLE						m_hSemp;
};

#endif // !defined(AFX_WRITEFILEMANAGER_H__4B33A343_A7FF_4F50_B7F7_84CC37E3A798__INCLUDED_)
