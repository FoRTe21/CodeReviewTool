#pragma once

#include <gdiplus.h>

// CRichEditor
class CRichEditor : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditor)
protected:
	enum CONTROLID { IDC_CODERICHEDIT = 101 };

public:
	CRichEditor();
	virtual ~CRichEditor();

protected:
	const Gdiplus::Color m_lightBlue = Gdiplus::Color(50,0,0,255);
	const int m_gabFromUpperBound = 4;
	const int m_richEditLeftMargin = 35;
	bool m_bHighlightingLine = false;

	Gdiplus::Rect m_highlightingLineRect;
	Gdiplus::Color m_highlightingColor = m_lightBlue;

	int GetOneLineHeight();

protected:
	void PrintAllData(CDC* ptrDC);
	void PrintLineNumber(CDC* ptrDC);
	void DrawHighlightRectangle(Gdiplus::Graphics& graphics);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	void CreateRichEditor(CRect richEditorRect, CWnd* parentView);
	
	void ScrollEditor(int lineNumber);
};


