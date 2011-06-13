// macgetDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_)
#define AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iprtrmib.h>		//GetIFTable API

/////////////////////////////////////////////////////////////////////////////
// CMacgetDlg �_�C�A���O

typedef DWORD (WINAPI *p_GetIfTable)
(
  PMIB_IFTABLE pIfTable,  // buffer for interface table 
  PULONG pdwSize,         // size of buffer
  BOOL bOrder             // sort the table by index?
);


class CMacgetDlg : public CDialog
{
// �\�z
public:
	CMacgetDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

	HINSTANCE		m_hDll;			//DLL���C�u�������g
	p_GetIfTable	GetIfTable;


// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMacgetDlg)
	enum { IDD = IDD_MACGET_DIALOG };
	CString	m_Edit;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMacgetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MACGETDLG_H__B28484A8_562A_4973_9242_BEEE242A6490__INCLUDED_)
