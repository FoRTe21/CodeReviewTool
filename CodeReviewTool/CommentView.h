#pragma once

//#define IDC_CODERICHEDIT 101

// CCommentView ���Դϴ�.
#include "RichEditor.h"

class CCommentView : public CView
{
	DECLARE_DYNCREATE(CCommentView)
protected:
	enum CONTROLID{IDC_CODERICHEDIT = 101};
protected:
	CRichEditor m_codeRichEdit;
	CString m_sourceCode;

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
	void ClearViewEdit();

	void PrintSourceCode(CString sourceCode);

	void ScrollEditor(int lineNumber);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

