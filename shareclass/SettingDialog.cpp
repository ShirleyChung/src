#include "stdafx.h"
#include "SettingDialog.h"

size_t _StringToUNICODE(const CString& str, BYTE* buffer)
{
	size_t nChars = str.GetLength() + 1, nActualChars;
	WCHAR* pchCaption = new WCHAR[nChars];
	nActualChars = MultiByteToWideChar(CP_ACP, 0, str, -1, pchCaption, nChars);
	memcpy( buffer, pchCaption, nActualChars * sizeof(WCHAR) );
	delete[] pchCaption;
	return nActualChars;
}

BYTE* CDlgItem::WriteToBuffer(BYTE* pBuffer)
{
	/*  DLGITEMTEMPLATE */
	memcpy(pBuffer, &m_dlgItem, sizeof(DLGITEMTEMPLATE));
	pBuffer += sizeof(DLGITEMTEMPLATE);
	/*  indicating atom value */
	*(WORD*)pBuffer = 0xFFFF;
	pBuffer += sizeof(WORD);
	/* control type */
	*(WORD*)pBuffer = m_controlType;
	pBuffer += sizeof(WORD);
	/* ���D/title */
	pBuffer += _StringToUNICODE(m_strCaption, pBuffer) * sizeof(WCHAR);
	/* bytes in data for control */
	*(WORD*)pBuffer = 0;
	pBuffer += sizeof(WORD);

	return pBuffer;
}


CSettingDialog::CSettingDialog()
{
}


CSettingDialog::~CSettingDialog()
{
}

BEGIN_MESSAGE_MAP(CSettingDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CSettingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CSettingDialog::AddCheckBox(WORD id, CString caption, CRect rt)
{
	AddControl(id, CDlgItem::BUTTON, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 0, caption, rt);
}

void CSettingDialog::AddButton(WORD id, CString caption, CRect rt)
{
	AddControl(id, CDlgItem::BUTTON, WS_CHILD | WS_VISIBLE , 0, caption, rt);
}


void CSettingDialog::AddControl(WORD id, CDlgItem::controltype type, DWORD wndStyle, DWORD exStyle, CString caption, short x, short y, short cx, short cy)
{
	CDlgItem dlgitem;
	dlgitem.m_dlgItem.x = x;
	dlgitem.m_dlgItem.y = y;
	dlgitem.m_dlgItem.cx = cx;
	dlgitem.m_dlgItem.cy = cy;
	dlgitem.m_dlgItem.id = id;
	dlgitem.m_dlgItem.style = wndStyle;
	dlgitem.m_dlgItem.dwExtendedStyle = exStyle;
	dlgitem.m_strCaption = caption;
	dlgitem.m_controlType = type;
	m_dlgItemList.AddTail(dlgitem);
}

void CSettingDialog::AddControl(WORD id, CDlgItem::controltype type, DWORD wndStyle, DWORD exStyle, CString caption, CRect rt)
{
	AddControl(id, type, wndStyle, exStyle, caption, (short)rt.left, (short)rt.top, (short)rt.Width(), (short)rt.Height());
}

void CSettingDialog::DoModalDialog(CRect rt, const CString& caption, CWnd* parent, const CString& fontname, short fontsize, DWORD style, DWORD exStyle)
{
	size_t allocSize = sizeof(DLGTEMPLATE) + 3 * sizeof(WORD) + (caption.GetLength() + fontname.GetLength() + 2) * sizeof(WCHAR);
	allocSize = (allocSize + 3) & ~3; //first control has to be DWORD aligned.

	POSITION pos = NULL;
	for(pos = m_dlgItemList.GetHeadPosition(); pos;)
		allocSize +=m_dlgItemList.GetNext(pos).GetSize();

	BYTE* pBuffer = new BYTE[allocSize];
	BYTE* pDest = pBuffer;
	memset(pDest, 0, allocSize);

	pDest = _InitDlgTemplate(pDest, rt, caption, fontname, fontsize, style, exStyle);

	for(pos = m_dlgItemList.GetHeadPosition(); pos;)
		pDest = m_dlgItemList.GetNext(pos).WriteToBuffer(  (BYTE*)(((DWORD_PTR)pDest + 3) & ~3)  );

	if (! InitModalIndirect((DLGTEMPLATE*)pBuffer, parent) )
		MessageBox("InitModalIndirect failed!");
	else
		DoModal();

	delete[] pBuffer;
}

BYTE* CSettingDialog::_InitDlgTemplate(BYTE* pBuffer, CRect& rt, const CString& strCaption, const CString& fontname, short fontsize, DWORD style, DWORD exStyle)
{
	/* DLGTEMPLATE */
	LPDLGTEMPLATE pDlgTemp = (LPDLGTEMPLATE)pBuffer;
	pDlgTemp->x = (short)rt.left;
	pDlgTemp->y = (short)rt.top;
	pDlgTemp->cx = (short)rt.Width();
	pDlgTemp->cy = (short)rt.Height();
	pDlgTemp->style = style;
	pDlgTemp->dwExtendedStyle = exStyle;
#if _MSC_VER >= 1310
	pDlgTemp->cdit = (WORD)m_dlgItemList.GetSize();
#else
	pDlgTemp->cdit = (WORD)m_dlgItemList.GetCount();
#endif
	pBuffer += sizeof(DLGTEMPLATE);
	/* menu */
	*(WORD*)pBuffer = 0;
	pBuffer += sizeof(WORD);
	/* windows class */
	*(WORD*)pBuffer = 0;
	pBuffer += sizeof(WORD);
	/* ���D  */
	pBuffer += _StringToUNICODE(strCaption, pBuffer) * sizeof(WCHAR);
	/* font-size */
	*(WORD*)pBuffer = fontsize;
	pBuffer += sizeof(WORD);
	/* font-name */
	pBuffer += _StringToUNICODE(fontname, pBuffer) * sizeof(WCHAR);

	return pBuffer;
}
