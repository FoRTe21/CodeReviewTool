// PreCodeView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "PreCodeView.h"


// CPreCodeView

IMPLEMENT_DYNCREATE(CPreCodeView, CView)

CPreCodeView::CPreCodeView()
{
}

CPreCodeView::~CPreCodeView()
{
}

BEGIN_MESSAGE_MAP(CPreCodeView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPreCodeView �׸����Դϴ�.

void CPreCodeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CPreCodeView �����Դϴ�.

#ifdef _DEBUG
void CPreCodeView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreCodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreCodeView �޽��� ó�����Դϴ�.


int CPreCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CRect cr;
	GetClientRect(&cr);
	m_codeRichEdit.Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_READONLY,
							cr, this, IDC_REVIEWRICHEDIT);

	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = CFE_PROTECTED;
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cf.yHeight = 200;
	cf.crTextColor = RGB(0, 0, 0);
	cf.bCharSet = HANGEUL_CHARSET;
	m_codeRichEdit.SetDefaultCharFormat(cf);

	return 0;
}


void CPreCodeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect cr;
	GetClientRect(&cr);

	m_codeRichEdit.MoveWindow(&cr, 1);
	
}

void CPreCodeView::PrintComments(CString comments)
{
	m_codeRichEdit.SetWindowTextW(comments);
}