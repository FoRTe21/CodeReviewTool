// PreCodeView.cpp : 구현 파일입니다.
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


// CPreCodeView 그리기입니다.

void CPreCodeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CPreCodeView 진단입니다.

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


// CPreCodeView 메시지 처리기입니다.


int CPreCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect cr;
	GetClientRect(&cr);

	m_codeRichEdit.MoveWindow(&cr, 1);
	
}

void CPreCodeView::PrintComments(CString comments)
{
	m_codeRichEdit.SetWindowTextW(comments);
}