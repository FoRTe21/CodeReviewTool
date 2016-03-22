
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "CodeReviewTool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
//	ON_WM_SIZE()
ON_WM_SIZE()
ON_COMMAND(ID_SAVE, &CMainFrame::OnSave)
ON_COMMAND(ID_FILEOPEN, &CMainFrame::OnFileopen)
//ON_WM_PAINT()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_ptPreView = NULL;
	m_ptCmtView = NULL;
	m_fileListViewWnd = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
/*	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}*/

/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	*/
	/*if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	*/
	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	//m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	/*if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
		*/
	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRect cr;
	GetClientRect(&cr);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		return false;
	}
	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CPreCodeView), CSize(cr.Width() / 2, cr.Height()), pContext))
	{
		return false;
	}

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCommentView), CSize(cr.Width() / 2, cr.Height()), pContext))
	{
		return false;
	}
	
	m_ptPreView = (CPreCodeView*)m_wndSplitter.GetPane(0, 0);
	m_ptCmtView = (CCommentView*)m_wndSplitter.GetPane(0, 1);

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect cr;
	GetClientRect(&cr);
	
	m_wndSplitter.SetColumnInfo(0, cx / 2, 0);
	m_wndSplitter.SetColumnInfo(1, cx / 2, 0);

	m_wndSplitter.RecalcLayout();
	// 자연스럽게 분할창 조절되는 것은 이후에 구현.
}


// Command line의 arguments를 받아옴

void CMainFrame::OnSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnFileopen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OPENFILENAME ofn;
	WCHAR lpStrFile[MAX_PATH] = L"";

	memset(&ofn, 0, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
	ofn.lpstrFile = lpStrFile;
	ofn.nMaxFile = MAX_PATH;

	GetOpenFileName(&ofn);

	if (m_dataProcessor.FillAllDataFromFile(lpStrFile) == false)
	{
		return;
	}
	
	OpenFileListView();
}

void CMainFrame::CloseFileListView()
{
	m_fileListViewWnd = NULL;
	CloseLineSearch();
}

void CMainFrame::OpenFileListView()
{
	if (m_fileListViewWnd != NULL)
	{
		m_fileListViewWnd->DestroyWindow();
		delete m_fileListViewWnd;
		m_fileListViewWnd = NULL;
	}

	m_fileListViewWnd = new CFileListView;
	m_fileListViewWnd->MakeWindow(this, m_dataProcessor.GetRivisions(), m_dataProcessor.GetReviews());
	OpenLineSearch();
}

void CMainFrame::PrintAllTextDataOnEditCtrl(CString filepath)
{
	CString review, sourceCode;

	m_dataProcessor.GetReviewNCodeText(filepath, &review, &sourceCode);
	m_ptPreView->PrintComments(review);

	m_ptCmtView->ClearViewEdit();
	m_ptCmtView->PrintSourceCode(sourceCode);
}

void CMainFrame::OpenLineSearch()
{
	m_lineSearchWnd = new CLineSearch;
	m_lineSearchWnd->Create(IDD_LINESEARCH, this);
	m_lineSearchWnd->ShowWindow(SW_SHOW);
}

void CMainFrame::CloseLineSearch()
{
	m_lineSearchWnd->PostNcDestroy();
	m_lineSearchWnd = NULL;
}

int CMainFrame::ScrollSourceCodeEditor(int command)
{
	int line = 0;
	switch (command)
	{
	case CMD_INCREASE:
	{
		line = m_dataProcessor.EditorScrollControl(command);
		break;
	}
	case CMD_DECREASE:
	{
		line = m_dataProcessor.EditorScrollControl(command);
		break;
	}
	case CMD_INIT:
	{
		line = m_dataProcessor.EditorScrollControl(command);
		break;
	}
	}

	m_lineSearchWnd->SetTextOnEdit(line);
	m_ptCmtView->ScrollEditor(line);

	return line;
}