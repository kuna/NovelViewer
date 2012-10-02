// NovelViewer10.h : main header file for the NOVELVIEWER10 application
//

#if !defined(AFX_NOVELVIEWER10_H__7CF0C7D6_B805_4985_971D_C29F3CA75972__INCLUDED_)
#define AFX_NOVELVIEWER10_H__7CF0C7D6_B805_4985_971D_C29F3CA75972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNovelViewer10App:
// See NovelViewer10.cpp for the implementation of this class
//

class CNovelViewer10App : public CWinApp
{
public:
	CNovelViewer10App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelViewer10App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNovelViewer10App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELVIEWER10_H__7CF0C7D6_B805_4985_971D_C29F3CA75972__INCLUDED_)
