// RichEditor.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "RichEditor.h"


// CRichEditor

IMPLEMENT_DYNAMIC(CRichEditor, CRichEditCtrl)

CRichEditor::CRichEditor()
{
	
}

CRichEditor::~CRichEditor()
{
	
}


BEGIN_MESSAGE_MAP(CRichEditor, CRichEditCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CRichEditor 메시지 처리기입니다.

void CRichEditor::CreateRichEditor(CRect richEditorRect, CWnd* parentView)
{
	Create(WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE |
		ES_READONLY | WS_VSCROLL | WS_HSCROLL,
		richEditorRect, parentView, IDC_CODERICHEDIT);

	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = CFE_PROTECTED;
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cf.yHeight = 200;
	cf.crTextColor = RGB(0, 0, 0);
	cf.bCharSet = HANGEUL_CHARSET;
	SetDefaultCharFormat(cf);


}


void CRichEditor::OnPaint()
{
	
	SendMessage(EM_SETMARGINS, EC_LEFTMARGIN, m_richEditLeftMargin);

	CRichEditCtrl::OnPaint();

	CDC* pDC = GetDC();
	PrintAllData(pDC);
	ReleaseDC(pDC);
}

void CRichEditor::PrintAllData(CDC* ptrDC)
{
	Gdiplus::Graphics graphics(*ptrDC);
	PrintLineNumber(ptrDC);
	DrawHighlightRectangle(graphics);
	graphics.ReleaseHDC(*ptrDC);
}

void CRichEditor::ScrollEditor(int lineNumber)
{
	int firstVisibleLine = GetFirstVisibleLine();
	
	int distance = lineNumber - firstVisibleLine;
	LineScroll(distance - m_gabFromUpperBound, 0);

	int lineHeight = GetOneLineHeight();

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

int CRichEditor::GetOneLineHeight()
{
	int len = static_cast<int>(SendMessage(EM_LINELENGTH, 0, 0));
	int secondLineIndex = len + 1;

	POINT point1 = { 0 };
	POINT point2 = { 0 };

	SendMessage(EM_POSFROMCHAR, (WPARAM)&point1, secondLineIndex);
	SendMessage(EM_POSFROMCHAR, (WPARAM)&point2, 0);

	return (point1.y - point2.y);

}

void CRichEditor::PrintLineNumber(CDC* ptrDC)
{
	int firstVisibleLine = GetFirstVisibleLine();
	int lineCount = SendMessage(EM_GETLINECOUNT, 0, 0);

	if (lineCount <= 1)
	{
		return;
	}

	int lineHeight = GetOneLineHeight();

	CRect cr;
	GetRect(&cr);
	cr.right = m_richEditLeftMargin;
	int posibleVisibleLineCount = lineHeight == 0 ? 1 : (cr.Height() / lineHeight);

	CString text;
	for (int i = 0; i < posibleVisibleLineCount && i < lineCount; i++)
	{
		text.Format(L"%d", (firstVisibleLine + i + 1));
		TextOut(*ptrDC, 0, (i * lineHeight), (LPCWSTR)text, text.GetLength());
	}
}

void CRichEditor::DrawHighlightRectangle(Gdiplus::Graphics& graphics)
{
	Gdiplus::SolidBrush highlighting(m_highlightingColor);

	if (m_bHighlightingLine == true)
	{
		CRect rt;
		GetClientRect(&rt);
		Gdiplus::Rect temporaryDrawRect = m_highlightingLineRect;
		temporaryDrawRect.Width = rt.right;
		graphics.FillRectangle(&highlighting, temporaryDrawRect);
	}
}