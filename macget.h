// macget.h : MACGET アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MACGET_H__BE28F2E4_E1C5_4771_A383_813E43C02552__INCLUDED_)
#define AFX_MACGET_H__BE28F2E4_E1C5_4771_A383_813E43C02552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMacgetApp:
// このクラスの動作の定義に関しては macget.cpp ファイルを参照してください。
//

class CMacgetApp : public CWinApp
{
public:
	CMacgetApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMacgetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMacgetApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MACGET_H__BE28F2E4_E1C5_4771_A383_813E43C02552__INCLUDED_)
