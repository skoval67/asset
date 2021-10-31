// stdafx.cpp : source file that includes just the standard includes
// asset.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

wchar_t* trimchars = L"\n \"";

void split(parameter* p, const wchar_t* delimeter, CString str)
{
	int curPos = 0;
	CString resToken = str.Tokenize(delimeter, curPos);
	wcscpy_s(p->name, resToken.GetLength() + 1, resToken.Trim(trimchars));
	if (curPos != -1) {
		resToken = str.Tokenize(delimeter, curPos).Trim(trimchars);
		wcscpy_s(p->value, resToken.GetLength() + 1, resToken.Trim(trimchars));
	} else
		p->value = L"";
}

CString get_value(FILE *s, CString param)
{
	wchar_t line[128];
	wchar_t name[80];
	wchar_t value[80];
	parameter par;
	par.name = name;
	par.value = value;
	fseek(s, 0, SEEK_SET);
	while (fgetws(line, sizeof line, s)) {
		split(&par, L"=", CString(line));
		if (CString(par.name).MakeUpper() == "NAME" && CString(par.value).MakeUpper() == param.MakeUpper()) {
			while (fgetws(line, sizeof line, s)) {
				split(&par, L"=", CString(line));
				if (CString(par.name).MakeUpper() == "VALUE") return CString(par.value);
			};
		};
	};
	return (CString) "";
}

void WriteAttribute(FILE *s, const wchar_t *AttrName, short id, const wchar_t *AttrType, CString value)
{
	wchar_t buff[128];
	wchar_t wcstr[128];
	swprintf(buff, sizeof buff, L"Start Attribute\nName = %s\n", AttrName);
	fputws(buff, s);
	swprintf(buff, sizeof buff, L"ID = %u\n", id);
	fputws(buff, s);
	swprintf(buff, sizeof buff, L"Type = %s\n", AttrType);
	fputws(buff, s);
    mbstowcs_s(NULL, wcstr, value.GetLength() + 1, (CStringA) value, _TRUNCATE);
	swprintf(buff, sizeof buff, L"Value = \"%s\"\nEnd Attribute\n\n", wcstr);
	fputws(buff, s);
}

void SaveAssets(const wchar_t* fname, CString comp_num, CString monitor_num, CString monitor_serial, CString location, CString office)
{
	short i = 0;
	errno_t err;
	FILE *stream;
	if (err = _wfopen_s(&stream, fname, L"w")) {
		char message[80];
		sprintf_s(message, sizeof message, "System error: %u", err);
		MessageBox(NULL, LPCWSTR(message), (LPCWSTR) "Ошибка", MB_ICONSTOP);
	} else {
		fputws(L"Start Component\nName = \"System Information\"\n\n", stream);
		fputws(L"Start Group\nName = \"PC Info\"\n", stream);
		fputws(L"ID = 1\nClass = \"AssetNumbers\"\n\n", stream);
		
		WriteAttribute(stream, L"\"Computer Asset Number\"", ++i, L"String(16)", comp_num.Trim());
		WriteAttribute(stream, L"\"Monitor Asset Number\"", ++i, L"String(25)", monitor_num.Trim());
		WriteAttribute(stream, L"\"Monitor Serial Number\"", ++i, L"String(30)", monitor_serial.Trim().MakeUpper());
		WriteAttribute(stream, L"\"Location\"", ++i, L"String(30)", location.Trim());
		WriteAttribute(stream, L"\"Office\"", ++i, L"String(15)", office.Trim());

		fputws(L"End Group\n", stream);
		fputws(L"End Component", stream);

		fclose(stream);
	};
}