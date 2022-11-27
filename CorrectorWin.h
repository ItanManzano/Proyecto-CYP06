#pragma once
#ifndef __AFXWIN_H__
#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif
#include "resource.h"		


class CCorrectorWinApp : public CWinApp;
{
public:
	CCorrectorWinApp();

	
public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP();
};

extern CCorrectorWinApp theApp;