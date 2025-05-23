﻿
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "CProcess.h"
#include <chrono>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/enry:WinMainCRTStartup /subsystem:console")
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CMFCApplication1Dlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CMFCApplication1Dlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAkE_PATTEN, &CMFCApplication1Dlg::OnBnClickedBtnMakePatten)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CMFCApplication1Dlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CMFCApplication1Dlg::OnBnClickedBtnThread)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_CDlgImage, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void CMFCApplication1Dlg::OnBnClickedBtnDlg()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}

void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	if(m_pDlgImage) delete m_pDlgImage;
	if(m_pDlgImgResult) delete m_pDlgImgResult;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
using namespace std;
void  CMFCApplication1Dlg::callFunc(int n)
{
	int nData = n;
	cout << nData << endl;
}

void CMFCApplication1Dlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char* )m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);
	for (int k = 0; k < MAX_POINT;k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%0xff;
	}
	int nIndex = 0;
	for (int j = 0;j < nHeight;j++) {
		for (int i = 0;i < nWidth;i++) {
			if (fm[j * nPitch + i] > 100)
			{
				if (m_pDlgImgResult->m_nDataCount < MAX_POINT)
				{
					/*cout << nIndex << ":" << i << "," << j << endl;*/
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			}
		}
	}
	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();
}

void CMFCApplication1Dlg::OnBnClickedBtnProcess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CProcess process;

	auto start = std::chrono::system_clock::now();
	int nRet = process.getStarInfo(&m_pDlgImage->m_image,100);
	auto end = std::chrono::system_clock::now();
	auto millisec = std::chrono::duration_cast < std::chrono::milliseconds > (end - start);
	cout << nRet << "\t" << millisec.count() << "ms" << endl;
}

void CMFCApplication1Dlg::OnBnClickedBtnMakePatten()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);
	
	CRect rect(100, 100, 200, 200);
	for (int j = rect.top;j < rect.bottom;j++) {
		for (int i = rect.left;i < rect.right;i++) {
			fm[j * nPitch + i] = rand()%0xff;
		}
	}
	m_pDlgImage->Invalidate();
}

void CMFCApplication1Dlg::OnBnClickedBtnGetData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 0x80;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top;j < rect.bottom;j++) {
		for (int i = rect.left;i < rect.right;i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;
}
#include <thread>
using namespace chrono;
void threadProcess(CWnd* pParent,CRect rect)
{
	CMFCApplication1Dlg* pWnd = (CMFCApplication1Dlg*)pParent;
	int nRet = pWnd->processImg(rect);

	cout << "th0 : " << nRet << endl;
}
void CMFCApplication1Dlg::OnBnClickedBtnThread()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto start = system_clock::now();

	int nImgSize = 4090 * 4;
	CRect rect(0, 0, nImgSize, nImgSize);
	CRect rt[4];
	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(nImgSize*(k%2), nImgSize * int(k / 2));
	}
	// 위와 동일하다.
	//rt[0].SetRect(0,0, nImgSize, nImgSize);
	//rt[1].SetRect(nImgSize, 0, nImgSize*2, nImgSize);
	//rt[2].SetRect(0, nImgSize, nImgSize, nImgSize*2);
	//rt[3].SetRect(nImgSize, nImgSize, nImgSize*2, nImgSize*2);
	thread _thread0(threadProcess, this, rt[0]);
	_thread0.join();
	//thread _thread0(threadProcess, this, rt[1]);
	//thread _thread0(threadProcess, this, rt[2]);
	//thread _thread0(threadProcess, this, rt[3]);



	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "총 :" << millisec.count() << endl;
}
int CMFCApplication1Dlg::processImg(CRect rect)
{
	CProcess process;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, 0, rect);

	return nRet;
}
