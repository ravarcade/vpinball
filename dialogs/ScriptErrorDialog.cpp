#include "ScriptErrorDialog.h"
#include "stdafx.h"

ScriptErrorDialog::ScriptErrorDialog(const std::wstring &message) :
	CDialog(IDD_SCRIPT_ERROR),
	initMessage(message)
{}

BOOL ScriptErrorDialog::OnInitDialog()
{
	HWND textBoxHwnd = ::GetDlgItem(GetHwnd(), IDC_ERROR_EDIT);

	::SendMessage(textBoxHwnd, WM_SETFONT, (size_t)GetStockObject(ANSI_FIXED_FONT), 0);
	::SetWindowTextW(textBoxHwnd, initMessage.c_str());

	return TRUE;
}

BOOL ScriptErrorDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (LOWORD(wParam))
	{
		case IDC_SCRIPT_CONTINUE:
		{
			shouldSuppressErrors = ::IsDlgButtonChecked(GetHwnd(), IDC_SUPPRESS_ERRORS_CHECK) == BST_CHECKED;
			Close();
			return TRUE;
		}
		case IDC_SCRIPT_STOP:
		{
			shouldSuppressErrors = true;
			g_pvp->QuitPlayer(0);
			Close();
			return TRUE;
		}
	}

	return FALSE;
}
