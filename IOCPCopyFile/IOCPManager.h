// IOCPManager.h: interface for the CIOCPManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCPMANAGER_H__A1CBAFDC_A379_4148_B1A2_C3075B78B51F__INCLUDED_)
#define AFX_IOCPMANAGER_H__A1CBAFDC_A379_4148_B1A2_C3075B78B51F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReadFileManger.h"
#include "WriteFileManager.h"

class CIOCPManager  
{
public:
	CIOCPManager();
	virtual ~CIOCPManager();

	void Init();
	void BeginCopy();
	bool AddCopyItem(const char* lpSrcFilePath,const char* lpDestFilePath);
	void EndCopy(long lCopyNum);
	void Stop(); 

private:
	void InitIOCP();
	int	 GetNoOfProcessors();

	static UINT __stdcall NotifiActionCompleteThread(LPVOID	lpParam);


private:
	HANDLE		m_hIOCompletionPort;
	HANDLE*		m_phWorkThreads;
	int			m_nWorkerCount;

private:
	long		m_nCurCopyCount;
	long		m_nCopyCount;
};

#endif // !defined(AFX_IOCPMANAGER_H__A1CBAFDC_A379_4148_B1A2_C3075B78B51F__INCLUDED_)
