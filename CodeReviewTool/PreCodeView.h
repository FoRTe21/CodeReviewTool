#pragma once

#define IDC_REVIEWRICHEDIT 100

// CPreCodeView ���Դϴ�.

class CPreCodeView : public CView
{
	DECLARE_DYNCREATE(CPreCodeView)
protected:
	CRichEditCtrl m_codeRichEdit;

protected:
	CPreCodeView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPreCodeView();

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
	void PrintComments(CString comments);
};


