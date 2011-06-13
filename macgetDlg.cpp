// macgetDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "macget.h"
#include "macgetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacgetDlg ダイアログ

CMacgetDlg::CMacgetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacgetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMacgetDlg)
	m_Edit = _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMacgetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMacgetDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMacgetDlg, CDialog)
	//{{AFX_MSG_MAP(CMacgetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacgetDlg メッセージ ハンドラ

BOOL CMacgetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。


	m_hDll = LoadLibrary("iphlpapi.dll");
	if(m_hDll != NULL){
		GetIfTable = (p_GetIfTable)GetProcAddress(m_hDll,"GetIfTable");
		if(GetIfTable == NULL){
			AfxMessageBox("GetIfTableがありません");
			FreeLibrary(m_hDll);
			m_hDll = NULL;
		}
	}else{
		AfxMessageBox("iphlpapi.dllがありません");
	}
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CMacgetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CMacgetDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CMacgetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// IPHelperから取得。ただしwin95で動くかどうかわからへん。
void CMacgetDlg::OnButton1() 
{
	UpdateData();
	if(GetIfTable == NULL){
		m_Edit = "GetIfTable cannot work\r\n";
		UpdateData(FALSE);
		return;
	}
	// Get MAC address

    char Buf[1024];
    DWORD d=0;
	CString ostr;

    GetIfTable( NULL , &d, FALSE );
    PMIB_IFTABLE IfTable = (PMIB_IFTABLE)new char[d] ;

	if( IfTable ){
		if( GetIfTable( (PMIB_IFTABLE)IfTable,&d,FALSE) == NO_ERROR ){
		    for(int i=0;i< (int)IfTable->dwNumEntries;i++ ){
                wsprintf(Buf,"dwIndex 0x%8.8x",(int)IfTable->table[i].dwIndex);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwType %d",(int)IfTable->table[i].dwType);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwMtu %d",(int)IfTable->table[i].dwMtu);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwSpeed %d",(int)IfTable->table[i].dwSpeed);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwPhysAddrLen %d",(int)IfTable->table[i].dwPhysAddrLen);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"bPhysAddr %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x"
                    ,(unsigned char)IfTable->table[i].bPhysAddr[0]
                    ,(unsigned char)IfTable->table[i].bPhysAddr[1]
                    ,(unsigned char)IfTable->table[i].bPhysAddr[2]
                    ,(unsigned char)IfTable->table[i].bPhysAddr[3]
                    ,(unsigned char)IfTable->table[i].bPhysAddr[4]
                    ,(unsigned char)IfTable->table[i].bPhysAddr[5]
                    );
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwAdminStatus %d",(int)IfTable->table[i].dwAdminStatus);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOperStatus %d",(int)IfTable->table[i].dwOperStatus);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwLastChange %d",(int)IfTable->table[i].dwLastChange);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInOctets %d",(int)IfTable->table[i].dwInOctets);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInUcastPkts %d",(int)IfTable->table[i].dwInUcastPkts);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInNUcastPkts %d",(int)IfTable->table[i].dwInNUcastPkts);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInDiscards %d",(int)IfTable->table[i].dwInDiscards);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInErrors %d",(int)IfTable->table[i].dwInErrors);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwInUnknownProtos %d",(int)IfTable->table[i].dwInUnknownProtos);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutOctets %d",(int)IfTable->table[i].dwOutOctets);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutUcastPkts %d",(int)IfTable->table[i].dwOutUcastPkts);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutNUcastPkts %d",(int)IfTable->table[i].dwOutNUcastPkts);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutDiscards %d",(int)IfTable->table[i].dwOutDiscards);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutErrors %d",(int)IfTable->table[i].dwOutErrors);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwOutQLen %d",(int)IfTable->table[i].dwOutQLen);
				ostr += Buf;
				ostr += "\r\n";

                wsprintf(Buf,"dwDescrLen %d",(int)IfTable->table[i].dwDescrLen);
				ostr += Buf;
				ostr += "\r\n";

                IfTable->table[i].bDescr[IfTable->table[i].dwDescrLen]='\0';
                wsprintf(Buf,"bDescr %s",(int)IfTable->table[i].bDescr);
				ostr += Buf;
				ostr += "\r\n";

				ostr += "--------------------------------------------------------";
				ostr += "\r\n";

            }
        }
		delete [] IfTable;
	}
	m_Edit = ostr;
	UpdateData(FALSE);

}

#include <nb30.h>
typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER    NameBuff [30];
}ASTAT, * PASTAT;

ASTAT Adapter;

// Netbiosから取得。ただし、NETBIOSがインストールされていないとうごかへん。
void CMacgetDlg::OnButton2() 
{
	NCB Ncb;
	UCHAR uRetCode;
	char NetName[50];
	LANA_ENUM   lenum;
	int      i;

	CString ostr;
	UpdateData();

	memset( &Ncb, 0, sizeof(Ncb) );
	Ncb.ncb_command = NCBENUM;
	Ncb.ncb_buffer = (UCHAR *)&lenum;
	Ncb.ncb_length = sizeof(lenum);
	uRetCode = Netbios( &Ncb );
	ostr.Format("The NCBENUM return code is: 0x%x \r\n", uRetCode );
	m_Edit=ostr;

	for(i=0; i < lenum.length ;i++){
		memset( &Ncb, 0, sizeof(Ncb) );
		Ncb.ncb_command = NCBRESET;
		Ncb.ncb_lana_num = lenum.lana[i];

		uRetCode = Netbios( &Ncb );
		ostr.Format("The NCBRESET on LANA %d return code is: 0x%x \r\n",lenum.lana[i], uRetCode );
		m_Edit += ostr;

		memset( &Ncb, 0, sizeof (Ncb) );
		Ncb.ncb_command = NCBASTAT;
		Ncb.ncb_lana_num = lenum.lana[i];

		strcpy( (char*)Ncb.ncb_callname,  "*               " );
		Ncb.ncb_buffer = (unsigned char *) &Adapter;
		Ncb.ncb_length = sizeof(Adapter);

		uRetCode = Netbios( &Ncb );
		ostr.Format("The NCBASTAT on LANA %d return code is: 0x%x \r\n",lenum.lana[i], uRetCode );
		m_Edit += ostr;

		if ( uRetCode == 0 ){
			ostr.Format("The Ethernet Number on LANA %d is:%02x%02x%02x%02x%02x%02x\r\n",
				lenum.lana[i],
				Adapter.adapt.adapter_address[0],
				Adapter.adapt.adapter_address[1],
				Adapter.adapt.adapter_address[2],
				Adapter.adapt.adapter_address[3],
				Adapter.adapt.adapter_address[4],
				Adapter.adapt.adapter_address[5] 
			);
			m_Edit += ostr;
		}
		m_Edit += "--------------------------------------------------------\r\n";
	}
	UpdateData(FALSE);

}
