// FileListView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "FileListView.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CFileListView 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFileListView, CDialogEx)

CFileListView::CFileListView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILESELECT, pParent),
	m_reviews(NULL),
	m_revisions(NULL)
{

}

CFileListView::~CFileListView()
{
}

void CFileListView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REVISION, m_revisionListBox);
	DDX_Control(pDX, IDC_CODEFILE, m_fileNameListBox);
}

BEGIN_MESSAGE_MAP(CFileListView, CDialogEx)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_REVISION, &CFileListView::OnLbnSelchangeRevision)
	ON_LBN_DBLCLK(IDC_CODEFILE, &CFileListView::OnLbnDblclkCodefile)
END_MESSAGE_MAP()


// CFileListView 메시지 처리기입니다.


void CFileListView::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();

	mf->CloseFileListView();
	delete this;
	CDialogEx::PostNcDestroy();
}


void CFileListView::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DestroyWindow();
	//CDialogEx::OnClose();
}

void CFileListView::ViewFileListByIndex(int index)
{
	CString rivision;

	m_revisionListBox.GetText(index, rivision);
	for (auto iter = m_reviews->begin(); iter != m_reviews->end(); iter++)
	{
		if (rivision.CompareNoCase(iter->GetRevision()) == 0)
		{
			m_fileNameListBox.AddString(iter->GetFilePath());
		}
	}
}

void CFileListView::OnLbnSelchangeRevision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString rivision;

	m_revisionListBox.GetText(m_revisionListBox.GetCurSel(), rivision);
	ClearFileNameLB();
	ViewFileListByIndex(m_revisionListBox.GetCurSel());
}


void CFileListView::ClearFileNameLB()
{
	m_fileNameListBox.ResetContent();
}

void CFileListView::ClearRevisionLB()
{
	m_revisionListBox.ResetContent();
}

void CFileListView::OnLbnDblclkCodefile()
{
	CString filepath;
	
	m_fileNameListBox.GetText(m_fileNameListBox.GetCurSel(), filepath);
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();
	mf->PrintAllTextDataOnEditCtrl(filepath);
	mf->ScrollSourceCodeEditor(CDataProcessing::CMD_INIT);
}

void CFileListView::InitListControls(std::list<CString>* revisions, std::list<CReviewData>* reviews)
{
	m_revisions = revisions;

	for (auto iter = m_revisions->begin(); iter != m_revisions->end(); iter++)
	{
		m_revisionListBox.AddString(*iter);
	}

	m_revisionListBox.SetCurSel(0);

	m_reviews = reviews;
	ViewFileListByIndex(0);
}

void CFileListView::MakeWindow(CWnd* parentWindow, std::list<CString>* revisions, std::list<CReviewData>* reviews)
{
	Create(IDD_FILESELECT, parentWindow);
	InitListControls(revisions, reviews);
	ShowWindow(SW_SHOW);
}