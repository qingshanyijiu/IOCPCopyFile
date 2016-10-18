// WriteFileManager.cpp: implementation of the CWriteFileManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCPCopyFile.h"
#include "WriteFileManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteFileManager::CWriteFileManager()
{
	m_hFile = INVALID_HANDLE_VALUE;

	memset(&m_notifyContext,0,sizeof(ContextInfo));
	m_notifyContext.bType = FILE_ACTION_TYPE_NOTIFY;

	m_bIsBegin = false;
	m_bIsEmpty = false;

	m_hSemp = ::CreateSemaphore(NULL,0,1000,NULL);
}

CWriteFileManager::~CWriteFileManager()
{
	CloseFile();

	if (m_hSemp)
		CloseHandle(m_hSemp);
}


bool	CWriteFileManager::OpenFile(const char* lpFilePath,HANDLE hIocpHandle)
{
	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		m_hFile = ::CreateFile(lpFilePath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_FLAG_OVERLAPPED,
			NULL);
		
		if (INVALID_HANDLE_VALUE == m_hFile)
			return false;
		
		if(hIocpHandle != CreateIoCompletionPort(m_hFile, hIocpHandle, (ULONG)this, 0 ))//(ULONG)m_hFile
			return false;

		m_bIsBegin = false;
		m_bIsEmpty = false;
	}
	
	return true;
}

bool CWriteFileManager::WriteData(PContextInfo pContext)
{
	bool bRet = false;
	
	pContext->bType = FILE_ACTION_TYPE_WRITE;
	
	if (!WriteFile(m_hFile,pContext->lpData,pContext->dwDataLen,NULL,&pContext->overlapped))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			bRet = true;
		}
	}
	
	return bRet;
}

bool CWriteFileManager::WriteEmptyData()
{
	bool bRet = false;
	
	if (!WriteFile(m_hFile,m_notifyContext.lpData,m_notifyContext.dwDataLen,NULL,&m_notifyContext.overlapped))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			bRet = true;
		}
	}
	
	return bRet;
}

void CWriteFileManager::PushWriteData(PContextInfo pContext)
{
	if (false == m_bIsBegin)
	{
		m_bIsBegin = true;
		WriteData(pContext);
	}
	else
	{
		{
			CCriticalLock::CAutoLock lock(m_lock);
			m_dataInfoList.push_back(pContext);
		}
	
		if(!ReleaseSemaphore(m_hSemp,1,NULL))
		{
			do 
			{
				Sleep(1);
			} while (FALSE == ReleaseSemaphore(m_hSemp,1,NULL));
		}

		if (m_bIsEmpty)
		{
			WriteEmptyData();
		}
	}
}

void CWriteFileManager::WriteNextData()
{
	if (WAIT_OBJECT_0 == WaitForSingleObject(m_hSemp,0))
	{
		PContextInfo pContext = NULL;
		{
			CCriticalLock::CAutoLock lock(m_lock);
			pContext = m_dataInfoList.front();	
			m_dataInfoList.pop_front();
		}

		m_bIsEmpty = false;
		if (pContext)
			WriteData(pContext);
	}
	else
	{
		m_bIsEmpty = true;
	}
}

bool	CWriteFileManager::CloseFile()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
	
	return true;
}