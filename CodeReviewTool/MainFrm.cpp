
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
ON_WM_SIZE()
ON_COMMAND(ID_FILEOPEN, &CMainFrame::OnFileopen)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	m_dataProcessor.InitDataProcessor();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// �������� Ŭ���̾�Ʈ ������ �����ϴ� �並 ����ϴ�.

	// FoRTe21 : ���߿� �ʿ��� ��츦 ����ؼ� �ڵ带 ���ܵӴϴ�. 

/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	*/
	/*if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	*/
	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		CString errorStr;
		errorStr.Format(L"ȭ�� ���� ���� - error : %d", GetLastError());
		::AfxMessageBox(errorStr, 0, 0);
		return false;
	}
	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CPreCodeView), CSize(cr.Width() / 2, cr.Height()), pContext))
	{
		CString errorStr;
		errorStr.Format(L"���� �ؽ�Ʈ â ���� ���� - error : %d", GetLastError());
		::AfxMessageBox(errorStr, 0, 0);
		return false;
	}

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCommentView), CSize(cr.Width() / 2, cr.Height()), pContext))
	{
		CString errorStr;
		errorStr.Format(L"�ҽ��ڵ� �ؽ�Ʈ â ���� ���� - error : %d", GetLastError());
		::AfxMessageBox(errorStr, 0, 0);
		return false;
	}
	
	m_ptPreView = (CPreCodeView*)m_wndSplitter.GetPane(0, 0);
	m_ptCmtView = (CCommentView*)m_wndSplitter.GetPane(0, 1);

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CRect cr;
	GetClientRect(&cr);
	
	m_wndSplitter.SetColumnInfo(0, cx / 2, 0);
	m_wndSplitter.SetColumnInfo(1, cx / 2, 0);

	m_wndSplitter.RecalcLayout();
	// �ڿ������� ����â �����Ǵ� ���� ���Ŀ� ����.
}

void CMainFrame::OnFileopen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OPENFILENAME ofn;
	WCHAR lpStrFile[MAX_PATH] = L"";
	memset(&ofn, 0, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = L"��� ����(*.*)\0*.*\0";
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
	TextData textData;

	m_dataProcessor.GetReviewNCodeText(filepath, textData);
	m_ptPreView->PrintComments(textData.m_strComments);

	m_ptCmtView->PrintSourceCode(textData.m_strSourceCode);
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
	int lineNumber = m_dataProcessor.EditorScrollControl(command);

	m_lineSearchWnd->SetTextOnEdit(lineNumber);
	m_ptCmtView->ScrollEditor(lineNumber);

	return lineNumber;
}