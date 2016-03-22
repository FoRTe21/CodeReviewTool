// LineSearch.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "LineSearch.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CLineSearch 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLineSearch, CDialogEx)

CLineSearch::CLineSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINESEARCH, pParent)
{

}

CLineSearch::~CLineSearch()
{
}

void CLineSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURRENTLINE, m_currentLine);
}


BEGIN_MESSAGE_MAP(CLineSearch, CDialogEx)
	ON_BN_CLICKED(IDC_PREVLINEBUTTON, &CLineSearch::OnBnClickedPrevlinebutton)
	ON_BN_CLICKED(IDC_NEXTLINEBUTTON, &CLineSearch::OnBnClickedNextlinebutton)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLineSearch 메시지 처리기입니다.



void CLineSearch::OnBnClickedPrevlinebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();

	int line = mf->ScrollSourceCodeEditor(CMD_DECREASE);
	//SetTextOnEdit(line);
}


void CLineSearch::OnBnClickedNextlinebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();

	int line = mf->ScrollSourceCodeEditor(CMD_INCREASE);
	//SetTextOnEdit(line);
}


void CLineSearch::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CLineSearch::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	DestroyWindow();
	CDialogEx::OnClose();
}

void CLineSearch::SetTextOnEdit(int number)
{
	CString windowText;
	windowText.Format(L"%d", number);
	m_currentLine.SetWindowTextW(windowText);
	//m_currentLine.SetDlgItemInt(number, false);
}