#pragma once
#include "afxwin.h"


// CLineSearch 대화 상자입니다.

class CLineSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CLineSearch)
protected:
	CEdit m_currentLine;

public:
	CLineSearch(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLineSearch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINESEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SetTextOnEdit(int number);

	afx_msg void OnBnClickedPrevlinebutton();
	afx_msg void OnBnClickedNextlinebutton();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
