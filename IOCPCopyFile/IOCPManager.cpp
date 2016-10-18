// IOCPManager.cpp: implementation of the CIOCPManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCPCopyFile.h"
#include "IOCPManager.h"
#include <process.h>

#define  EXIT_CODE (0)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIOCPManager::CIOCPManager()
{
	m_hIOCompletionPort = INVALID_HANDLE_VALUE;
	m_phWorkThreads = NULL;
	m_nWorkerCount = 0;

	m_nCurCopyCount = 0;
	m_nCopyCount = 0;
}

CIOCPManager::~CIOCPManager()
{
	Stop();
}


void CIOCPManager::Init()
{
	InitIOCP();
}

void CIOCPManager::BeginCopy()
{
	m_nCurCopyCount = 0;
	m_nCopyCount = 0;
}

bool CIOCPManager::AddCopyItem(const char* lpSrcFilePath,const char* lpDestFilePath)
{
	CWriteFileManager* pWriteFile = new CWriteFileManager();
	if (!pWriteFile->OpenFile(lpDestFilePath,m_hIOCompletionPort))
	{
		delete pWriteFile;
		return false;
	}

	CReadFileManager* pReadFile = new CReadFileManager(pWriteFile);
	if (!pReadFile->OpenFile(lpSrcFilePath,m_hIOCompletionPort))
	{
		delete pReadFile;
		delete pWriteFile;
		return false;
	}

	pReadFile->ReadData();

	return true;
}

void CIOCPManager::EndCopy(long lCopyNum)
{
	m_nCopyCount = lCopyNum;
}

void CIOCPManager::Stop()
{
	if (INVALID_HANDLE_VALUE != m_hIOCompletionPort)
	{
		int i;
		for (i=0;i<m_nWorkerCount;++i)
			PostQueuedCompletionStatus(m_hIOCompletionPort,0,DWORD(EXIT_CODE),NULL);
		WaitForMultipleObjects(m_nWorkerCount,m_phWorkThreads,TRUE,m_nWorkerCount*1000);
		
		for (i=0;i<m_nWorkerCount;++i)
			CloseHandle(m_phWorkThreads[i]);
		
		delete [] m_phWorkThreads;
	}

}

void CIOCPManager::InitIOCP()
{
	if ( INVALID_HANDLE_VALUE == m_hIOCompletionPort)
	{
		m_hIOCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0 );
		m_nWorkerCount = 5;
		
		m_phWorkThreads = new HANDLE[m_nWorkerCount];
		
		for (int i=0;i<m_nWorkerCount;++i)
			m_phWorkThreads[i] = (HANDLE)_beginthreadex(NULL,0,NotifiActionCompleteThread,this,0,NULL); 
	}
}

int	CIOCPManager::GetNoOfProcessors()
{
	SYSTEM_INFO si;
	
	GetSystemInfo(&si);
	
	return si.dwNumberOfProcessors;
}

UINT __stdcall CIOCPManager::NotifiActionCompleteThread(LPVOID	lpParam)
{
	CIOCPManager*			pThis = (CIOCPManager*) lpParam;
	OVERLAPPED*				pOverlapped = NULL;
	DWORD					dwBytesTransfered = 0;
	void*					hKey = NULL;
	BOOL					bReturn;
	ContextInfo*			pIoContext;

	char csLogInfo[100]={0};
	
	while (1)
	{
		bReturn = GetQueuedCompletionStatus(pThis->m_hIOCompletionPort,
			&dwBytesTransfered,
			(ULONG*)&hKey,
			&pOverlapped,
			INFINITE);

		if ( EXIT_CODE==hKey)
		{
			break;
		}
		if(NULL == pOverlapped )  
		{  
			DWORD dwErr = GetLastError();
			continue;  
		} 
		else
		{			
			pIoContext = CONTAINING_RECORD(pOverlapped, ContextInfo, overlapped);
			
			if(FILE_ACTION_TYPE_READ == pIoContext->bType)
			{
				CReadFileManager* pReadFile = (CReadFileManager*)hKey;
				pIoContext->dwDataLen = dwBytesTransfered;
				pReadFile->WriteData(pIoContext);
				
				if (dwBytesTransfered)
					pReadFile->ReadData(dwBytesTransfered);
				else
				{
					delete pReadFile;
				}
			}
			else if (FILE_ACTION_TYPE_WRITE == pIoContext->bType)
			{
// 				sprintf(csLogInfo,"delete info = 0x%x",pIoContext->lpData);
// 				s_trace.infor(csLogInfo,strlen(csLogInfo)+1);
				
				if (pIoContext->lpData)
					tc_deletearray(pIoContext->lpData);
				tc_deletearray(pIoContext);

				CWriteFileManager* pWriteFile = (CWriteFileManager*)hKey;
				if (dwBytesTransfered)
				{	
					pWriteFile->WriteNextData();
				}
				else
				{
					delete pWriteFile;
					InterlockedIncrement(&pThis->m_nCurCopyCount);
					if (pThis->m_nCopyCount&&pThis->m_nCurCopyCount==pThis->m_nCopyCount)
					{
						::MessageBox(NULL,"Copy complete!",NULL,0);
					}
				}
			}
			else
			{

				CWriteFileManager* pWriteFile = (CWriteFileManager*)hKey;
				pWriteFile->WriteNextData();
			}
		}
	}
	return 0;
}