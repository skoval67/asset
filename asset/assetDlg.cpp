// assetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "asset.h"
#include "assetDlg.h"
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CassetDlg dialog


CassetDlg::CassetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CassetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CassetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ComputerAsset);
	DDX_Text(pDX, IDC_EDIT2, MonitorAsset);
	DDX_Text(pDX, IDC_EDIT3, MonitorSerialNumber);
	DDX_Text(pDX, IDC_COMBO1, Location);
	DDX_Text(pDX, IDC_EDIT5, Office);
}

BEGIN_MESSAGE_MAP(CassetDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CassetDlg message handlers

BOOL CassetDlg::OnInitDialog()
{
	HKEY hKey;
	DWORD length = 255;
	FILE *stream;

	*filename = 0;
	//_wcsset_s(filename, 255, 0);
	_wsetlocale( LC_ALL, L"Russian" );
	if( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        //TEXT("SOFTWARE\\Microsoft\\SMS\\Client\\Configuration\\Client Properties"),
		    TEXT("SOFTWARE\\Microsoft\\SMS"),
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS)
	{
		if ( RegQueryValueEx(hKey,
			TEXT("NOIDMIF Directory"),
			NULL,
			NULL,
			(LPBYTE) filename,
			&length) == ERROR_SUCCESS)
		{
			wcscat_s(filename, 255, L"\\sample.mif");
			if (!_wfopen_s(&stream, filename, L"r"))
			{
				ComputerAsset = get_value(stream, CString("Computer Asset Number"));
				MonitorAsset = get_value(stream, CString("Monitor Asset Number"));
				MonitorSerialNumber = get_value(stream, CString("Monitor Serial Number"));
				Location = get_value(stream, CString("Location"));
				Office = get_value(stream, CString("Office"));
				fclose(stream);
			};

		};
		RegCloseKey(hKey);
	};
	if (!filename[0]) {
		MessageBox((LPCTSTR) L"Возможно Microsoft SMS агент еще не установлен на этом компьютере", (LPCTSTR) L"Ошибка", MB_ICONSTOP);
		exit(1);
	};

	CComboBox *pList = (CComboBox*) GetDlgItem(IDC_COMBO1);
	for (int i = 0; i < LOC_COUNT; i++) {
		pList->AddString(LPCTSTR(Locations[i])); };

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CassetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CassetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CassetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
