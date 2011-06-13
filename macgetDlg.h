// macgetDlg.h : ヘッダー ファイル
//

#if !defined(AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_)
#define AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iprtrmib.h>		//GetIFTable API

/////////////////////////////////////////////////////////////////////////////
// CMacgetDlg ダイアログ

typedef DWORD (WINAPI *p_GetIfTable)
(
  PMIB_IFTABLE pIfTable,  // buffer for interface table 
  PULONG pdwSize,         // size of buffer
  BOOL bOrder             // sort the table by index?
);


class CMacgetDlg : public CDialog
{
// 構築
public:
	CMacgetDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

	HINSTANCE		m_hDll;			//DLLライブラリ自身
	p_GetIfTable	GetIfTable;


// ダイアログ データ
	//{{AFX_DATA(CMacgetDlg)
	enum { IDD = IDD_MACGET_DIALOG };
	CString	m_Edit;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMacgetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMacgetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_)
