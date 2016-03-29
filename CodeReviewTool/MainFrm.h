
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "PreCodeView.h"
#include "CommentView.h"
#include "DataProcessing.h"
#include "FileListView.h"
#include "LineSearch.h"

#include "afxext.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.

	// ==== ���߿� �ʿ��� ��츦 ����ؼ� ���� ==== //
	//CToolBar          m_wndToolBar;
	//CStatusBar        m_wndStatusBar;
	// =============================================//

	CSplitterWnd m_wndSplitter;
	CDataProcessing m_dataProcessor;
	CPreCodeView* m_ptPreView = NULL;
	CCommentView* m_ptCmtView = NULL;
	CFileListView* m_fileListViewWnd = NULL;
	CLineSearch* m_lineSearchWnd = NULL;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	void OpenLineSearch();
	void CloseLineSearch();
public:

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileopen();

	void OpenFileListView();
	void CloseFileListView();

	int ScrollSourceCodeEditor(int command);
	void PrintAllTextDataOnEditCtrl(CString filepath);
};


