// CommentView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "CommentView.h"


// CCommentView

IMPLEMENT_DYNCREATE(CCommentView, CView)

CCommentView::CCommentView()
{
	m_commentSourceCode = NULL;
}

CCommentView::~CCommentView()
{
}

BEGIN_MESSAGE_MAP(CCommentView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCommentView 그리기입니다.

void CCommentView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CCommentView 진단입니다.

#ifdef _DEBUG
void CCommentView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCommentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCommentView 메시지 처리기입니다.


int CCommentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CRect cr;
	GetClientRect(&cr);

	m_codeRichEdit.Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | 
						  ES_READONLY | WS_VSCROLL | WS_HSCROLL,
						  cr, this, IDC_CODERICHEDIT);

	//m_codeRichEdit.SetEventMask(m_codeRichEdit.GetEventMask() | ENM_UPDATE);

	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = CFE_PROTECTED;
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cf.yHeight = 200;
	cf.crTextColor = RGB(0, 0, 0);
	cf.bCharSet = HANGEUL_CHARSET;
	m_codeRichEdit.SetDefaultCharFormat(cf);

	m_codeRichEdit.SendMessage(EM_SETMARGINS, EC_LEFTMARGIN, 35 & 0xFFFF);
	return 0;
}


void CCommentView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect cr;
	GetClientRect(&cr);

	m_codeRichEdit.MoveWindow(&cr, 1);
}

void CCommentView::SetCommentSourceCode(LPTSTR sourceCode)
{
	// 예외처리 필요 NULL인지 아닌지.
	m_commentSourceCode = sourceCode;

	m_codeRichEdit.SetWindowTextW(m_commentSourceCode);
}

LPWSTR CCommentView::GetCommentSourceCode()
{
	int length = m_codeRichEdit.GetTextLength();

	delete[] m_commentSourceCode;
	m_commentSourceCode = NULL;

	m_commentSourceCode = new WCHAR[length + 1];
	m_codeRichEdit.GetWindowTextW(m_commentSourceCode, length * 2 + 1);

	return m_commentSourceCode;
}

void CCommentView::PrintSourceCode(CString sourceCode)
{
	m_codeRichEdit.SetWindowTextW(sourceCode);
}

void CCommentView::ScrollEditor(int lineNumber)
{
	m_codeRichEdit.ScrollEditor(lineNumber);
}

void CCommentView::ClearViewEdit()
{
	m_codeRichEdit.SetWindowTextW(L"");
}