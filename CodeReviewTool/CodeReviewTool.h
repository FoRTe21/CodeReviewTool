
// CodeReviewTool.h : CodeReviewTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

// CCodeReviewToolApp:
// �� Ŭ������ ������ ���ؼ��� CodeReviewTool.cpp�� �����Ͻʽÿ�.
//

class CCodeReviewToolApp : public CWinApp
{
protected:
	ULONG_PTR m_gpToken;
public:
	CCodeReviewToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCodeReviewToolApp theApp;
