// ReadFileManger.h: interface for the CReadFileManger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READFILEMANGER_H__982DC84C_4160_4AAE_9EBC_FBC4E1D37A3C__INCLUDED_)
#define AFX_READFILEMANGER_H__982DC84C_4160_4AAE_9EBC_FBC4E1D37A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WriteFileManager.h"

class CReadFileManager  
{
public:
	CReadFileManager(CWriteFileManager* pWriteObject);
	virtual ~CReadFileManager();

	bool    OpenFile(const char* lpFilePath,HANDLE hIocpHandle);
	void	WriteData(PContextInfo pContext);
	bool	ReadData(DWORD dwOffset=0);
	bool	CloseFile();
	bool	SeekFile(int iMove);


private:
	HANDLE				m_hFile;
	CWriteFileManager*	m_writeObject;
	DWORD				m_dwOffset;
};

#endif // !defined(AFX_READFILEMANGER_H__982DC84C_4160_4AAE_9EBC_FBC4E1D37A3C__INCLUDED_)
