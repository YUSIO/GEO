
// GEODlg.h: 头文件
//

#pragma once


// CGEODlg 对话框
class CGEODlg : public CDialogEx
{
// 构造
public:
	CGEODlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString La1;
	CString Lo1;
	CString La2;
	CString Lo2;
	CString an1;
	CString an2;
	CString D;
	CString T;
	afx_msg void OnBnClickedButton1();
	void OnOK();
	BOOL PreTranslateMessage(MSG* pMsg);
};
