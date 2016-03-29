#pragma once
#include "afxwin.h"
#include <list>
// CFileListView ��ȭ �����Դϴ�.

class CReviewData;

class CFileListView : public CDialogEx
{
	DECLARE_DYNAMIC(CFileListView)
protected:
	std::list<CReviewData> m_reviews;
	std::list<CString> m_revisions;

	CListBox m_revisionListBox;
	CListBox m_fileNameListBox;

public:
	CFileListView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileListView();

	
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
	void InitListControls(std::list<CString> revisions, std::list<CReviewData> reviews);

	void ClearFileNameLB();
	void ClearRevisionLB();
	void ViewFileListByIndex(int index);
	virtual void PostNcDestroy();

public:

	void MakeWindow(CWnd* parentWindow, std::list<CString> revisions, std::list<CReviewData> reviews);
	afx_msg void OnClose();
	afx_msg void OnLbnSelchangeRevision();
	afx_msg void OnLbnDblclkCodefile();
};
