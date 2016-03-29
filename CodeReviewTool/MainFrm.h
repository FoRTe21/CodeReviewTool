
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

	// ==== 나중에 필요할 경우를 대비해서 나둠 ==== //
	//CToolBar          m_wndToolBar;
	//CStatusBar        m_wndStatusBar;
	// =============================================//

	CSplitterWnd m_wndSplitter;
	CDataProcessing m_dataProcessor;
	CPreCodeView* m_ptPreView = NULL;
	CCommentView* m_ptCmtView = NULL;
	CFileListView* m_fileListViewWnd = NULL;
	CLineSearch* m_lineSearchWnd = NULL;

// 생성된 메시지 맵 함수
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


