// assetDlg.h : header file
//

#pragma once
#include "afxwin.h"

#define LOC_COUNT 23					// ������ ������� Locations
static wchar_t* Locations[] = {L"���",
	L"����",
	L"������� ����������",
	L"��� ��������",
	L"��� ����",
	L"��� �����",
	L"��� �����",
	L"��� ����-������",
	L"��� ��������",
	L"��� ���-�����",
	L"��� �����������",
	L"��� ������",
	L"��� ������� �����",
	L"��� �������������",
	L"��� ����",
	L"��� ���������",
	L"��� ��������-�������������",
	L"��� ��������",
	L"��� �����",
	L"��� ����������",
	L"��� �����",
	L"��� ���������",
	L"��� ����"};

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
