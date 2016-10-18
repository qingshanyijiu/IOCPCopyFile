// CopyFile.cpp: implementation of the CCopyFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOCPCopyFile.h"
#include "CopyFile.h"
#include <imagehlp.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma comment(lib,"imagehlp.lib")

CCopyFile::CCopyFile()
{
	m_nCount = 0;
}

CCopyFile::~CCopyFile()
{
	m_IOCPManager.Stop();
}


void CCopyFile::Init()
{
	m_IOCPManager.Init();
}



void CCopyFile::BeginCopy(const char* lpSrcPath,const char* lpDestPath)
{
	DWORD dwAttr = ::GetFileAttributes(lpSrcPath);  //得到文件属性
	
	m_nCount = 0;
	m_IOCPManager.BeginCopy();
	
	if (0xFFFFFFFF == dwAttr)    // 文件或目录不存在
		return;
	else if (dwAttr&FILE_ATTRIBUTE_DIRECTORY)  // 如果是目录
	{
		string strDestPath = lpDestPath;
		if ('\\'!=strDestPath.at(strDestPath.length()-1)&&'/'!=strDestPath.at(strDestPath.length()-1))
			strDestPath += '\\';

		RecCopyFile(lpSrcPath,strDestPath.c_str());
	} 
	else
	{
		string strSrcName,strDestPath(lpDestPath);
		GetFileName(lpSrcPath,strSrcName);

		if ('\\'!=strDestPath.at(strDestPath.length()-1)&&'/'!=strDestPath.at(strDestPath.length()-1))
		{
			strDestPath += '\\';
			MakeSureDirectoryPathExists(strDestPath.c_str());
		}

		strDestPath += strSrcName.c_str();

		
		if(m_IOCPManager.AddCopyItem(lpSrcPath,strDestPath.c_str()))
			++m_nCount;
	}

	m_IOCPManager.EndCopy(m_nCount);
}

void CCopyFile::GetFileName(const char* lpFilePath,string& strFileName)
{
	string strFilePath = lpFilePath;

	int iPos = strFilePath.rfind('\\');
	if (string::npos == iPos)
		iPos = strFilePath.rfind('/');

	if(string::npos != iPos)
		strFileName = strFilePath.substr(iPos+1,strFilePath.length()-iPos-1);
	else
		strFileName = strFilePath;

}

void CCopyFile::RecCopyFile(const char* lpSrcPath,const char* lpDestPath)
{
	string strFind = lpSrcPath,strDestName;
	CFileFind fileFind;

	MakeSureDirectoryPathExists(lpDestPath);

	strFind += "\\*";
	BOOL bFound = fileFind.FindFile(strFind.c_str());

	while(bFound)
	{
		bFound = fileFind.FindNextFile();
		if (!fileFind.IsDots())
		{
			strDestName = lpDestPath;
			strDestName += fileFind.GetFileName().operator LPCTSTR();

			if (fileFind.IsDirectory())
			{
				strDestName += '\\';
				RecCopyFile(fileFind.GetFilePath().operator LPCTSTR(),strDestName.c_str());
			}
			else
			{
				if(m_IOCPManager.AddCopyItem(fileFind.GetFilePath().operator LPCTSTR(),strDestName.c_str()))
					++m_nCount;
			}
		}
	}
}