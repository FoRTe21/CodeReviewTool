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
	: CDialogEx(IDD_FILESELECT, pParent)
{

}

CFileListView::~CFileListView()
{
}

void CFileListView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REVISION, m_revisionLB);
	DDX_Control(pDX, IDC_CODEFILE, m_fileNameLB);
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
	int count = 0;
	CMainFrame* mf;
	mf = (CMainFrame*)AfxGetMainWnd();

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

void CFileListView::InitRevisions(std::list<CString>* revisions)
{
	std::list<CString>::iterator iter;
	m_revisions = revisions;
	
	for (iter = m_revisions->begin(); iter != m_revisions->end(); iter++)
	{
		m_revisionLB.AddString(*iter);
	}

	m_revisionLB.SetCurSel(0);
}

void CFileListView::InitReviews(std::list<CReviewData>* reviews)
{
	m_reviews = reviews;
	ViewFileListByIndex(0);
}

void CFileListView::ViewFileListByIndex(int index)
{
	CString rivision;
	std::list<CReviewData>::iterator iter;

	m_revisionLB.GetText(index, rivision);
	for (iter = m_reviews->begin(); iter != m_reviews->end(); iter++)
	{
		if (rivision.CompareNoCase(iter->GetRevision()) == 0)
		{
			m_fileNameLB.AddString(iter->GetFilePath());
		}
	}
}

void CFileListView::OnLbnSelchangeRevision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString rivision;

	m_revisionLB.GetText(m_revisionLB.GetCurSel(), rivision);
	ClearFileNameLB();
	ViewFileListByIndex(m_revisionLB.GetCurSel());
}


void CFileListView::ClearFileNameLB()
{
	m_fileNameLB.ResetContent();
}

void CFileListView::ClearRevisionLB()
{
	m_revisionLB.ResetContent();
}

void CFileListView::OnLbnDblclkCodefile()
{
	CString filepath;
	CMainFrame* mf;
	
	m_fileNameLB.GetText(m_fileNameLB.GetCurSel(), filepath);
	mf = (CMainFrame*)AfxGetMainWnd();
	mf->PrintReview(filepath);
	mf->PrintSourceCode(filepath);
}