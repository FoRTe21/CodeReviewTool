// CommentView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "CommentView.h"


// CCommentView

IMPLEMENT_DYNCREATE(CCommentView, CView)

CCommentView::CCommentView() 
{
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

	long mask = m_codeRichEdit.GetEventMask();
	m_codeRichEdit.SetEventMask(mask |= ENM_CHANGE);

	//reconfigure CSyntaxColorizer's default keyword groupings	
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

void CCommentView::PrintSourceCode(CString sourceCode)
{
	m_sourceCode = sourceCode;
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

BOOL CCommentView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	/*if (LOWORD(wParam) == IDC_CODERICHEDIT)
	{
		MSGFILTER *mf = (MSGFILTER*)lParam;
		switch (mf->msg)
		{
		case WM_COMMAND:
		{
			switch (HIWORD(mf->wParam))
			{
			case EN_CHANGE:
			{
				int len = m_codeRichEdit.LineLength();
				int start = m_codeRichEdit.LineIndex();

				//call the colorizer
				m_syntaxColorizer.Colorize(start, start + len, &m_codeRichEdit);
				break;
			}
			}
		}
		}
	}*/
	return CView::OnNotify(wParam, lParam, pResult);
}
