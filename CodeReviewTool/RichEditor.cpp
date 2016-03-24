// RichEditor.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "RichEditor.h"


// CRichEditor

IMPLEMENT_DYNAMIC(CRichEditor, CRichEditCtrl)

CRichEditor::CRichEditor() : m_gabFromUpperBound(4)
{

}

CRichEditor::~CRichEditor()
{
}


BEGIN_MESSAGE_MAP(CRichEditor, CRichEditCtrl)
	ON_WM_PAINT()
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

	POINT caretPosition1;
	POINT caretPosition2;

	caretPosition1 = point1;
	caretPosition2 = point2;

	int lineHeight = caretPosition1.y - caretPosition2.y;

	TEXTMETRIC tm;
	::GetTextMetrics(*hdc, &tm);
	CRect cr;
	this->GetRect(&cr);
	cr.right = 35 & 0xFFFF;
	int posibleVisibleLineCount = lineHeight == 0 ? 1 : (cr.Height() / lineHeight);
	
	CString text;
	for (int i = 0; i < posibleVisibleLineCount && i < lineCount; i++)
	{
		text.Format(L"%d", (firstVisibleLine + i + 1));
		TextOut(*hdc, 0, (i * lineHeight), (LPCWSTR)text, text.GetLength());
	}
}

void CRichEditor::ScrollEditor(int lineNumber)
{
	int firstVisibleLine = this->GetFirstVisibleLine();
	
	int distance = lineNumber - firstVisibleLine;
	LineScroll(distance - m_gabFromUpperBound, 0);

	int numberBegin = 0;

	int numberIndex = LineIndex(lineNumber);
	if ((numberBegin = numberIndex) != -1)
	{
		int numberEnd = numberBegin + LineLength(numberIndex);
		SetSel(numberBegin, numberEnd);
		
	}
}