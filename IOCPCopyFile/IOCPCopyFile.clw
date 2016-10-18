; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIOCPCopyFileDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IOCPCopyFile.h"

ClassCount=3
Class1=CIOCPCopyFileApp
Class2=CIOCPCopyFileDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IOCPCOPYFILE_DIALOG

[CLS:CIOCPCopyFileApp]
Type=0
HeaderFile=IOCPCopyFile.h
ImplementationFile=IOCPCopyFile.cpp
Filter=N

[CLS:CIOCPCopyFileDlg]
Type=0
HeaderFile=IOCPCopyFileDlg.h
ImplementationFile=IOCPCopyFileDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CIOCPCopyFileDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=IOCPCopyFileDlg.h
ImplementationFile=IOCPCopyFileDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IOCPCOPYFILE_DIALOG]
Type=1
Class=CIOCPCopyFileDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_SrcPath,edit,1350631552
Control3=IDC_BUTTON_SeletSrc,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_DestPath,edit,1350631552
Control6=IDC_BUTTON_SelectDest,button,1342242816
Control7=IDC_BUTTON_Begin,button,1342242816

