// LineSearch.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CodeReviewTool.h"
#include "LineSearch.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CLineSearch ��ȭ �����Դϴ�.

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


// CLineSearch �޽��� ó�����Դϴ�.



void CLineSearch::OnBnClickedPrevlinebutton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();

	int line = mf->ScrollSourceCodeEditor(CDataProcessing::CMD_DECREASE);
	//SetTextOnEdit(line);
}


void CLineSearch::OnBnClickedNextlinebutton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* mf = (CMainFrame*)AfxGetMainWnd();

	int line = mf->ScrollSourceCodeEditor(CDataProcessing::CMD_INCREASE);
	//SetTextOnEdit(line);
}


void CLineSearch::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;
	CDialogEx::PostNcDestroy();
}


void CLineSearch::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//DestroyWindow();
	//CDialogEx::OnClose();
}

void CLineSearch::SetTextOnEdit(int number)
{
	CString windowText;
	windowText.Format(L"%d", number);
	m_currentLine.SetWindowTextW(windowText);
}