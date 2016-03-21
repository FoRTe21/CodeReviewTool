#pragma once


// CRichEditor

class CRichEditor : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditor)

public:
	CRichEditor();
	virtual ~CRichEditor();

protected:
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	void PrintLineNumber(CDC* dc);
};


