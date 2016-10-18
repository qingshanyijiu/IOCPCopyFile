// CopyFile.h: interface for the CCopyFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPYFILE_H__4EFE508A_D390_4F99_A5B9_616F3B2FADAB__INCLUDED_)
#define AFX_COPYFILE_H__4EFE508A_D390_4F99_A5B9_616F3B2FADAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOCPManager.h"
#include <string>
using namespace std;

class CCopyFile  
{
public:
	CCopyFile();
	~CCopyFile();

	void Init();
	void BeginCopy(const char* lpSrcPath,const char* lpDestPath);

protected:
	void GetFileName(const char* lpFilePath,string& strFileName);
	void RecCopyFile(const char* lpSrcPath,const char* lpDestPath);

private:
	CIOCPManager	m_IOCPManager;
	long			m_nCount;
};

#endif // !defined(AFX_COPYFILE_H__4EFE508A_D390_4F99_A5B9_616F3B2FADAB__INCLUDED_)
