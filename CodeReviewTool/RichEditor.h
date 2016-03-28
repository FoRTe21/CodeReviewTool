#pragma once

#include <gdiplus.h>

// CRichEditor
class CRichEditor : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditor)

public:
	CRichEditor();
	virtual ~CRichEditor();

protected:
	const Gdiplus::Color m_lightBlue;
	const int m_gabFromUpperBound;
	bool m_bHighlightingLine;
	int m_vScrollWidth;

	Gdiplus::Rect m_highlightingLineRect;
	Gdiplus::Color m_highlightingColor;

	ULONG_PTR m_gpToken;



protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	void PrintLineNumber(CDC* dc);
	void ScrollEditor(int lineNumber);
};


