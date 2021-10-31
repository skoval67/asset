// assetDlg.h : header file
//

#pragma once
#include "afxwin.h"

#define LOC_COUNT 23					// размер массива Locations
static wchar_t* Locations[] = {L"РЦИ",
	L"ГРКЦ",
	L"Главное управление",
	L"РКЦ Агинское",
	L"РКЦ Акша",
	L"РКЦ Балей",
	L"РКЦ Борзя",
	L"РКЦ Верх-Усугли",
	L"РКЦ Нерчинск",
	L"РКЦ Газ-Завод",
	L"РКЦ Забайкальск",
	L"РКЦ Могоча",
	L"РКЦ Красный Чикой",
	L"РКЦ Краснокаменск",
	L"РКЦ Кыра",
	L"РКЦ Оловянная",
	L"РКЦ Петровск-Забайкальский",
	L"РКЦ Сретенск",
	L"РКЦ Хилок",
	L"РКЦ Чернышевск",
	L"РКЦ Шилка",
	L"РКЦ Карымское",
	L"РКЦ Чара"};

// CassetDlg dialog
class CassetDlg : public CDialog
{
// Construction
public:
	CassetDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASSET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString ComputerAsset;
	CString MonitorAsset;
	CString MonitorSerialNumber;
	CString Location;
	CString Office;

	wchar_t filename[255];
};
