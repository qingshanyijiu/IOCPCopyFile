// IOCPCopyFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOCPCopyFile.h"
#include "IOCPCopyFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOCPCopyFileDlg dialog

CIOCPCopyFileDlg::CIOCPCopyFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIOCPCopyFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIOCPCopyFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIOCPCopyFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIOCPCopyFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIOCPCopyFileDlg, CDialog)
	//{{AFX_MSG_MAP(CIOCPCopyFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SeletSrc, OnBUTTONSeletSrc)
	ON_BN_CLICKED(IDC_BUTTON_SelectDest, OnBUTTONSelectDest)
	ON_BN_CLICKED(IDC_BUTTON_Begin, OnBUTTONBegin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOCPCopyFileDlg message handlers

BOOL CIOCPCopyFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	SetDlgItemText(IDC_EDIT_SrcPath,"D:\\TestCopy\\Src\\");
	SetDlgItemText(IDC_EDIT_DestPath,"D:\\TestCopy\\Dest\\");
	m_copyFile.Init();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIOCPCopyFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIOCPCopyFileDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIOCPCopyFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIOCPCopyFileDlg::OnBUTTONSeletSrc() 
{
	// TODO: Add your control notification handler code here
	CString sFolderPath;
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	
	LPITEMIDLIST pidl = NULL;
	bi.pidlRoot = pidl;//初始化制定的root目录很不容易，
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "拷贝源目录:";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	//bi.ulFlags = BIF_EDITBOX;//浏览对话框中包含一个编辑控件，用户可以键入项目名字。
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN|BIF_BROWSEINCLUDEFILES;
	
	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//取得文件夹路径到Buffer里
		sFolderPath = Buffer;//将路径保存在一个CString对象里
	}
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	//释放内存
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	
	if (!sFolderPath.IsEmpty())
		SetDlgItemText(IDC_EDIT_SrcPath,sFolderPath);
	
}

void CIOCPCopyFileDlg::OnBUTTONSelectDest() 
{
	// TODO: Add your control notification handler code here
	CString sFolderPath;
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	
	LPITEMIDLIST pidl = NULL;
	bi.pidlRoot = pidl;//初始化制定的root目录很不容易，
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = "拷贝目标目录:";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	//bi.ulFlags = BIF_EDITBOX;//浏览对话框中包含一个编辑控件，用户可以键入项目名字。
	bi.ulFlags = BIF_RETURNONLYFSDIRS;//只返回文件夹，否则确定为灰。
	
	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//取得文件夹路径到Buffer里
		sFolderPath = Buffer;//将路径保存在一个CString对象里
	}
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return;
	//释放内存
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	
	if (!sFolderPath.IsEmpty())
		SetDlgItemText(IDC_EDIT_DestPath,sFolderPath);
}

void CIOCPCopyFileDlg::OnBUTTONBegin() 
{
	// TODO: Add your control notification handler code here

	//m_iocp.Start("E:\\KT-K3-2.0.9.1.iso","D:\\TestCopy\\1.iso");
	//m_iocp.Start("D:\\TestCopy\\Src\\1.txt","D:\\TestCopy\\1.txt");

	CString strSrcPath,strDestPath;
	GetDlgItemText(IDC_EDIT_SrcPath,strSrcPath);
	GetDlgItemText(IDC_EDIT_DestPath,strDestPath);

	m_copyFile.BeginCopy(strSrcPath.operator LPCTSTR(),strDestPath.operator LPCTSTR());
	
}
