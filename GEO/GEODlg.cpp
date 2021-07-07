
// GEODlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GEO.h"
#include "GEODlg.h"
#include "afxdialogex.h"
#include <cmath>
#define R 6378.155
#define	h 35786.045
#define	PI 3.1415926
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CGEODlg 对话框



CGEODlg::CGEODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GEO_DIALOG, pParent)
	, La1(_T("0"))
	, Lo1(_T("0"))
	, La2(_T("0"))
	, Lo2(_T("0"))
	, an1(_T("0"))
	, an2(_T("0"))
	, D(_T("0"))
	, T(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGEODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_La1, La1);
	DDX_Text(pDX, IDC_EDIT_Lo1, Lo1);
	DDX_Text(pDX, IDC_EDIT_La2, La2);
	DDX_Text(pDX, IDC_EDIT_Lo2, Lo2);
	DDX_Text(pDX, IDC_EDIT_an1, an1);
	DDX_Text(pDX, IDC_EDIT_an2, an2);
	DDX_Text(pDX, IDC_EDIT_D, D);
	DDX_Text(pDX, IDC_EDIT_T, T);
}

BEGIN_MESSAGE_MAP(CGEODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGEODlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGEODlg 消息处理程序

BOOL CGEODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGEODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGEODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGEODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGEODlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	double phi1, phi2, theta1, theta2;
	phi1 = _ttof(Lo1);//经度
	phi2 = _ttof(Lo2);
	theta1 = _ttof(La1);//纬度
	theta2 = _ttof(La2);
	double theta_phi = (phi2 - phi1)*(PI/180);//经度差
	double theta_theta = (theta1 - theta2) * (PI / 180);//纬度差
	double angle1 = atan((cos(theta_theta) * cos(theta_phi) - (R / (R + h))) / sqrt(1 - pow(cos(theta_theta) * cos(theta_phi), 2)))*(180/PI);
	double angle2;
	if (theta_phi == 0 && theta_theta == 0)
		angle2 = 0;
	else
		angle2 =atan(abs(tan(theta_phi)) / sin(theta_theta)) * (180 / PI);
	if (theta1 > 0)
	{
		if (theta_phi >0)
			angle2 = 180 - angle2;
		else if (theta_phi <= 0)
			angle2 = 180 + angle2;
	}
	if (theta1 < 0)
	{
		if (theta_phi < 0)
			angle2 = 360 - angle2;
	}
	double Dis = sqrt(pow(R, 2) + pow(R + h, 2) - 2 * R * (R + h) * cos(theta_theta) * cos(theta_phi));
	double time = Dis / 300000000.0;
	an1.Format(_T("%.3lf"), angle1);
	an2.Format(_T("%.3lf"), angle2);
	D.Format(_T("%.3lf"), Dis);
	T.Format(_T("%.3lf"), time);
	UpdateData(FALSE);
}
void CGEODlg::OnOK()
{
	OnBnClickedButton1();
}

BOOL CGEODlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_SPACE || pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


