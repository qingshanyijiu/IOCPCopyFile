// ReadFileManger.cpp: implementation of the CReadFileManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCPCopyFile.h"
#include "ReadFileManger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadFileManager::CReadFileManager(CWriteFileManager* pWriteObject)
	:m_writeObject(pWriteObject)
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_dwOffset = 0;
}

CReadFileManager::~CReadFileManager()
{
	CloseFile();
}

bool  CReadFileManager::OpenFile(const char* lpFilePath,HANDLE hIocpHandle)
{
	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		m_hFile = ::CreateFile(lpFilePath,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);

		if (INVALID_HANDLE_VALUE == m_hFile)
			return false;
		
		if(hIocpHandle != CreateIoCompletionPort(m_hFile, hIocpHandle, (ULONG)this, 0 ))
			return false;
	}

	return true;
}

void CReadFileManager::WriteData(PContextInfo pContext)
{
	 m_writeObject->PushWriteData(pContext);
}

bool CReadFileManager::ReadData(DWORD dwOffset/*=0*/)
{
	bool bRet = false;

	PContextInfo pContext = (PContextInfo)tc_newarray(sizeof(ContextInfo));
	memset(pContext,0,sizeof(ContextInfo));
	m_dwOffset += dwOffset;
	pContext->overlapped.Offset = m_dwOffset;
	pContext->bType = FILE_ACTION_TYPE_READ;
	pContext->lpData = (unsigned char*)tc_newarray(MAX_DATA_LEN);
	pContext->dwDataLen = MAX_DATA_LEN;

	if(!ReadFile(m_hFile,pContext->lpData,MAX_DATA_LEN,NULL,&pContext->overlapped))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			bRet = true;
		}
	}

	return bRet;
}

bool CReadFileManager::SeekFile(int iMove)
{
	return SetFilePointer(m_hFile,iMove,NULL,FILE_CURRENT)?true:false;
}

bool	 CReadFileManager::CloseFile()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	return true;
}