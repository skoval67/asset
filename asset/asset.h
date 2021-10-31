// asset.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

//#define _WIN32_WINNT 0x0600

#include "resource.h"		// main symbols

// CassetApp:
// See asset.cpp for the implementation of this class
//

class CassetApp : public CWinApp
{
public:
	CassetApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CassetApp theApp;