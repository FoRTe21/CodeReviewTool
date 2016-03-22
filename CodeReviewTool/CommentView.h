#pragma once

#define IDC_CODERICHEDIT 101
#define IDC_NUMRICHEDIT 102

#define LINELENGTH 30
// CCommentView 뷰입니다.
#include "RichEditor.h"

class CCommentView : public CView
{
	DECLARE_DYNCREATE(CCommentView)
protected:
	CRichEditor m_codeRichEdit;
	LPWSTR m_commentSourceCode;

protected:
	CCommentView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCommentView();
public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
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
	void SetCommentSourceCode(LPTSTR sourceCode);
	LPWSTR GetCommentSourceCode();
	void ClearViewEdit();

	void PrintSourceCode(CString sourceCode);

	void ScrollEditor(int lineNumber);
};

