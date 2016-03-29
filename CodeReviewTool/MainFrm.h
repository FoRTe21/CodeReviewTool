
// MainFrm.h : CMainFrame 클래스의 인터페이스
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

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	//CChildView    m_wndView;
	CSplitterWnd m_wndSplitter;
	CDataProcessing m_dataProcessor;
	CPreCodeView* m_ptPreView;
	CCommentView* m_ptCmtView;
	CFileListView* m_fileListViewWnd;
	CLineSearch* m_lineSearchWnd;

	LPWSTR m_preSourceCodeFileName;
	LPWSTR m_commentSourceCodeFileName;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSave();
	afx_msg void OnFileopen();

	void OpenFileListView();
	void OpenLineSearch();

	void CloseFileListView();
	void CloseLineSearch();

	int ScrollSourceCodeEditor(int command);
	void PrintAllTextDataOnEditCtrl(CString filepath);
};


