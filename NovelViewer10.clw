; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNovelViewerSetting
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NovelViewer10.h"

ClassCount=6
Class1=CNovelViewer10App
Class2=CNovelViewer10Dlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_NOVELVIEWER10_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_SETTINGS
Class4=CNovelViewerSetting
Resource4=IDD_EDIT
Class5=CNovelViewerEdit
Resource5=IDD_ABOUTBOX
Class6=CNovelViewerFind
Resource6=IDD_SEARCH

[CLS:CNovelViewer10App]
Type=0
HeaderFile=NovelViewer10.h
ImplementationFile=NovelViewer10.cpp
Filter=N

[CLS:CNovelViewer10Dlg]
Type=0
HeaderFile=NovelViewer10Dlg.h
ImplementationFile=NovelViewer10Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CNovelViewer10Dlg

[CLS:CAboutDlg]
Type=0
HeaderFile=NovelViewer10Dlg.h
ImplementationFile=NovelViewer10Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NOVELVIEWER10_DIALOG]
Type=1
Class=CNovelViewer10Dlg
ControlCount=0

[DLG:IDD_SETTINGS]
Type=1
Class=CNovelViewerSetting
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_BUTTON3,button,1342242816
Control7=IDC_COMBO1,combobox,1344339971
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT1,edit,1350639744
Control12=IDC_EDIT2,edit,1350639744
Control13=IDC_EDIT3,edit,1350639744
Control14=IDC_CHECK1,button,1342242819
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT4,edit,1350639744
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT5,edit,1350639744
Control19=IDC_BUTTON4,button,1342242816
Control20=IDC_COMBO2,combobox,1344339971

[CLS:CNovelViewerSetting]
Type=0
HeaderFile=NovelViewerSetting.h
ImplementationFile=NovelViewerSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO2
VirtualFilter=dWC

[DLG:IDD_EDIT]
Type=1
Class=CNovelViewerEdit
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1353781444
Control4=IDC_STATIC,static,1342308352

[CLS:CNovelViewerEdit]
Type=0
HeaderFile=NovelViewerEdit.h
ImplementationFile=NovelViewerEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNovelViewerEdit

[DLG:IDD_SEARCH]
Type=1
Class=CNovelViewerFind
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[CLS:CNovelViewerFind]
Type=0
HeaderFile=NovelViewerFind.h
ImplementationFile=NovelViewerFind.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNovelViewerFind

