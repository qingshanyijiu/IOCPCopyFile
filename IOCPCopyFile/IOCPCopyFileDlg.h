// IOCPCopyFileDlg.h : header file
//

#if !defined(AFX_IOCPCOPYFILEDLG_H__F1CAFE36_F5BC_4B16_99DC_407F0FE5F9B0__INCLUDED_)
#define AFX_IOCPCOPYFILEDLG_H__F1CAFE36_F5BC_4B16_99DC_407F0FE5F9B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIOCPCopyFileDlg dialog

#include "CopyFile.h"

class CIOCPCopyFileDlg : public CDialog
{
// Construction
public:
	CIOCPCopyFileDlg(CWnd* pParent = NULL);	// standard constructor

private:
	
	CCopyFile		m_copyFile;

// Dialog Data
	//{{AFX_DATA(CIOCPCopyFileDlg)
	enum { IDD = IDD_IOCPCOPYFILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOCPCopyFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIOCPCopyFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONSeletSrc();
	afx_msg void OnBUTTONSelectDest();
	afx_msg void OnBUTTONBegin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCPCOPYFILEDLG_H__F1CAFE36_F5BC_4B16_99DC_407F0FE5F9B0__INCLUDED_)
