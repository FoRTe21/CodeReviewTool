#pragma once

#define IDC_REVIEWRICHEDIT 100

// CPreCodeView 뷰입니다.

class CPreCodeView : public CView
{
	DECLARE_DYNCREATE(CPreCodeView)
protected:
	CRichEditCtrl m_codeRichEdit;

protected:
	CPreCodeView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPreCodeView();

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
	void PrintComments(CString comments);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};


