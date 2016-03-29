#pragma once


// CCommentView ���Դϴ�.
#include "RichEditor.h"

class CCommentView : public CView
{
	DECLARE_DYNCREATE(CCommentView)
protected:
	
protected:
	CRichEditor m_codeRichEdit;

protected:
	CCommentView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCommentView();
public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	void PrintSourceCode(CString sourceCode);

	void ScrollEditor(int lineNumber);
};

