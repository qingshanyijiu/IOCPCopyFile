// IOCPCopyFile.h : main header file for the IOCPCOPYFILE application
//

#if !defined(AFX_IOCPCOPYFILE_H__D0177AA1_81CB_4A18_A0D2_DA2CD2FB7855__INCLUDED_)
#define AFX_IOCPCOPYFILE_H__D0177AA1_81CB_4A18_A0D2_DA2CD2FB7855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIOCPCopyFileApp:
// See IOCPCopyFile.cpp for the implementation of this class
//

class CIOCPCopyFileApp : public CWinApp
{
public:
	CIOCPCopyFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOCPCopyFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIOCPCopyFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCPCOPYFILE_H__D0177AA1_81CB_4A18_A0D2_DA2CD2FB7855__INCLUDED_)
