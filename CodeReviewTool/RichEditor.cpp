// RichEditor.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "RichEditor.h"


// CRichEditor

IMPLEMENT_DYNAMIC(CRichEditor, CRichEditCtrl)

CRichEditor::CRichEditor()
	: m_gabFromUpperBound(4),
	m_bHighlightingLine(false),
	m_gpToken(NULL),
	m_lightBlue(Gdiplus::Color(50,0,0,255))
{
	Gdiplus::GdiplusStartupInput m_gpsi;
	Gdiplus::GdiplusStartup(&m_gpToken, &m_gpsi, NULL);
}

CRichEditor::~CRichEditor()
{
	if (m_gpToken != NULL)
	{
		Gdiplus::GdiplusShutdown(m_gpToken);
	}
}


BEGIN_MESSAGE_MAP(CRichEditor, CRichEditCtrl)
	ON_WM_PAINT()
//	ON_WM_CREATE()
//	ON_WM_SIZE()
END_MESSAGE_MAP()



// CRichEditor 메시지 처리기입니다.




void CRichEditor::OnPaint()
{
	
	SendMessage(EM_SETMARGINS, EC_LEFTMARGIN, 35 & 0xFFFF);

	CRichEditCtrl::OnPaint();

	CDC* pDC = GetDC();
	PrintLineNumber(pDC);
	ReleaseDC(pDC);
}

void CRichEditor::PrintLineNumber(CDC* hdc)
{
	Gdiplus::Graphics graphics(*hdc);
	m_highlightingColor = m_lightBlue;
	Gdiplus::SolidBrush highlighting(m_highlightingColor);

	HBRUSH B = CreateSolidBrush(RGB(0, 0, 0));
	int firstVisibleLine = this->GetFirstVisibleLine();
	int lineCount = this->SendMessage(EM_GETLINECOUNT, 0, 0);

	if (lineCount <= 1)
	{
		return ;
	}
	int len = (int)this->SendMessage(EM_LINELENGTH, 0, 0);
	int secondLineIndex = len + 1;

	POINT point1;
	POINT point2;

	this->SendMessage(EM_POSFROMCHAR, (WPARAM)&point1, secondLineIndex);
	this->SendMessage(EM_POSFROMCHAR, (WPARAM)&point2, 0);

	int lineHeight = point1.y - point2.y;

	CRect cr;
	GetRect(&cr);
	cr.right = 35 & 0xFFFF;
	int posibleVisibleLineCount = lineHeight == 0 ? 1 : (cr.Height() / lineHeight);
	
	CString text;
	for (int i = 0; i < posibleVisibleLineCount && i < lineCount; i++)
	{
		text.Format(L"%d", (firstVisibleLine + i + 1));
		TextOut(*hdc, 0, (i * lineHeight), (LPCWSTR)text, text.GetLength());
	}
	if (m_bHighlightingLine == true)
	{
		CRect rt;
		GetClientRect(&rt);
		Gdiplus::Rect temporaryDrawRect = m_highlightingLineRect;
		temporaryDrawRect.Width = rt.right;
		graphics.FillRectangle(&highlighting, temporaryDrawRect);
	}
}

void CRichEditor::ScrollEditor(int lineNumber)
{
	int firstVisibleLine = GetFirstVisibleLine();
	
	int distance = lineNumber - firstVisibleLine;
	LineScroll(distance - m_gabFromUpperBound, 0);

	int len = (int)this->SendMessage(EM_LINELENGTH, 0, 0);
	int secondLineIndex = len + 1;
	
	POINT point1;
	POINT point2;

	this->SendMessage(EM_POSFROMCHAR, (WPARAM)&point1, secondLineIndex);
	this->SendMessage(EM_POSFROMCHAR, (WPARAM)&point2, 0);

	int lineHeight = point1.y - point2.y;

	CRect rect;
	GetClientRect(&rect);

	rect.top = lineHeight * (lineNumber - GetFirstVisibleLine() - 1);
	rect.bottom = rect.top + lineHeight;

	m_highlightingLineRect.X = rect.left;
	m_highlightingLineRect.Y = rect.top;

	m_highlightingLineRect.Width = rect.right;
	m_highlightingLineRect.Height = lineHeight;

	m_bHighlightingLine = true;

	InvalidateRect(rect, false);

}