#include "stdafx.h"
#include "wcx_sii_decrypt.h"
#include "SII_Decrypt.h"

// Fake functions to make TC load the plugin
HANDLE __stdcall OpenArchive(tOpenArchiveData* ArchiveData)
{
	UNREFERENCED_PARAMETER(ArchiveData);
	ArchiveData->OpenResult = E_NOT_SUPPORTED;
	return NULL;
}
int __stdcall ReadHeader(HANDLE hArcData, tHeaderData* HeaderData)
{
	UNREFERENCED_PARAMETER(hArcData);
	UNREFERENCED_PARAMETER(HeaderData);
	return E_NOT_SUPPORTED;
}
int __stdcall ProcessFile(HANDLE hArcData, int Operation, char* DestPath, char* DestName)
{
	UNREFERENCED_PARAMETER(hArcData);
	UNREFERENCED_PARAMETER(Operation);
	UNREFERENCED_PARAMETER(DestPath);
	UNREFERENCED_PARAMETER(DestName);
	return E_NOT_SUPPORTED;
}
void __stdcall SetChangeVolProc(HANDLE hArcData, tChangeVolProc pChangeVolProc1)
{
	UNREFERENCED_PARAMETER(hArcData);
	UNREFERENCED_PARAMETER(pChangeVolProc1);
}
void __stdcall SetProcessDataProc(HANDLE hArcData, tProcessDataProc pProcessDataProc)
{
	UNREFERENCED_PARAMETER(hArcData);
	UNREFERENCED_PARAMETER(pProcessDataProc);
}

// Wrapper class for converting UTF-16LE string into UTF-8 with automatic
// cleanup when the data are no longer needed.
class Utf8String
{
public:
	Utf8String(const wchar_t* str)
	{
		int data_sz = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
		m_data = new char[data_sz];
		WideCharToMultiByte(CP_UTF8, 0, str, -1, m_data, data_sz, NULL, NULL);
	}

	~Utf8String()
	{
		if (m_data != NULL)
			delete[] m_data;
	}

	operator char*() const { return m_data; }

private:
	char* m_data;
};

// Open archive
HANDLE __stdcall OpenArchiveW(tOpenArchiveDataW* ArchiveDataW)
{
	ArchiveHandleW* arch_data = NULL;

	// Create the new archive handle object and initialize it
	try
	{
		arch_data = new ArchiveHandleW;
	}
	catch (...) 
	{
		ArchiveDataW->OpenResult = E_NO_MEMORY;
		return NULL;
	}
	arch_data->hFile = CreateFile(ArchiveDataW->ArcName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (arch_data->hFile == INVALID_HANDLE_VALUE)
	{
		delete arch_data;
		ArchiveDataW->OpenResult = E_EOPEN;
		return NULL;
	}
	// Check the file signature
	BYTE signature[4];
	DWORD dr;
	if (!ReadFile(arch_data->hFile, signature, 4, &dr, NULL) ||
		(dr != 4) ||
		((memcmp(signature, "BSII", 4) != 0) &&
		 (memcmp(signature, "ScsC", 4) != 0)))
	{
		delete arch_data;
		ArchiveDataW->OpenResult = E_UNKNOWN_FORMAT;
		return NULL;
	}
	int32_t fmt = GetFileFormat(Utf8String(ArchiveDataW->ArcName));
	if ((fmt != SIIDEC_RESULT_SUCCESS) && (fmt != SIIDEC_RESULT_BINARY_FORMAT))
	{
		delete arch_data;
		ArchiveDataW->OpenResult = E_UNKNOWN_FORMAT;
		return NULL;
	}
	// File looks OK, return the valid handle
	wcscpy_s(arch_data->ArcName, ArchiveDataW->ArcName);
	arch_data->OpenMode = ArchiveDataW->OpenMode;
	arch_data->pProcessDataProcW = NULL;
	arch_data->ContentsPos = 0;

	return (HANDLE)arch_data;
}

// Get the callback function for change volume requests (not used here)
void __stdcall SetChangeVolProcW(HANDLE hArcData, tChangeVolProcW pChangeVolProc1W)
{
	UNREFERENCED_PARAMETER(hArcData);
	UNREFERENCED_PARAMETER(pChangeVolProc1W);
}

// Get the callback function for progress bar updating
void __stdcall SetProcessDataProcW(HANDLE hArcData, tProcessDataProcW pProcessDataProcW)
{
	ArchiveHandleW* arch_data = (ArchiveHandleW*)hArcData;
	arch_data->pProcessDataProcW = pProcessDataProcW;
}

// Return information about the next packed file
int __stdcall ReadHeaderExW(HANDLE hArcData, tHeaderDataExW* HeaderDataExW)
{
	ArchiveHandleW* arch_data = (ArchiveHandleW*)hArcData;
	int ret_value = 0;
	if (arch_data->ContentsPos > 0)
		ret_value = E_END_ARCHIVE;
	else
	{
		arch_data->ContentsPos = 1;
		memset(HeaderDataExW, 0, sizeof(tHeaderDataExW));
		wchar_t* FileName = wcsrchr(arch_data->ArcName, L'\\');
		if (FileName == NULL)
			wcscpy_s(HeaderDataExW->FileName, L"decrypted.txt");
		else
		{
			wcscpy_s(HeaderDataExW->FileName, FileName + 1);
			wcscat_s(HeaderDataExW->FileName, L".txt");
		}
		FILETIME tm, ltm;
		if (GetFileTime(arch_data->hFile, NULL, NULL, &tm) && FileTimeToLocalFileTime(&tm, &ltm))
			FileTimeToDosDateTime(&ltm, ((WORD*)(&HeaderDataExW->FileTime)) + 1, (WORD*)(&HeaderDataExW->FileTime));
//		HeaderDataExW->PackSize = HeaderDataExW->UnpSize = elem->Length & 0xffffffff;
//#ifdef _WIN64
//		HeaderDataExW->PackSizeHigh = HeaderDataExW->UnpSizeHigh = elem->Length >> 32;
//#else
//		HeaderDataExW->PackSizeHigh = HeaderDataExW->UnpSizeHigh = 0;
//#endif
		HeaderDataExW->FileAttr = 0x20;
	}
	return ret_value;
}

// Unpack the next packed file
int __stdcall ProcessFileW(HANDLE hArcData, int Operation, WCHAR* DestPathW, WCHAR* DestNameW)
{
	switch (Operation)
	{
	case PK_SKIP:
	case PK_TEST:
		return 0;
	case PK_EXTRACT:
		return E_NOT_SUPPORTED;
	default:
		return E_NOT_SUPPORTED;
	}
//	ArchiveHandleW* arch_data = (ArchiveHandleW*)hArcData;
//	WCHAR DestFullName[MAX_PATH_EX];
//	DestFullName[0] = L'\0';
//	int ret_value = 0;
//	MemFile* elem = arch_data->hd.file_list.GetCurrentElement();
//	if (elem == NULL)
//		return E_END_ARCHIVE;
//	arch_data->hd.file_list.MoveToNextElement();
//
//	HANDLE f;
//	const BYTE* data = elem->Data;
//	size_t data_len = elem->Length;
//	DWORD w;
//	switch (Operation)
//	{
//	case PK_SKIP:
//	case PK_TEST:
//		break;
//	case PK_EXTRACT:
//		if (DestPathW != NULL)
//			wcscpy_s(DestFullName, MAX_PATH_EX, DestPathW);
//		wcscat_s(DestFullName, MAX_PATH_EX, DestNameW);
//		f = CreateFile(DestFullName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//		if (f == INVALID_HANDLE_VALUE)
//		{
//			ret_value = E_ECREATE;
//			break;
//		}
//		if ((data != NULL) && (!WriteFile(f, data, data_len, &w, NULL) || (w != data_len)))
//			ret_value = E_EWRITE;
//		CloseHandle(f);
//		break;
//	default:
//		ret_value = E_NOT_SUPPORTED;
//	}
//	return ret_value;
}

// Close the archive
int __stdcall CloseArchive(HANDLE hArcData)
{
	ArchiveHandleW* arch_data = (ArchiveHandleW*)hArcData;
	CloseHandle(arch_data->hFile);
	delete arch_data;
	return 0;
}

// Return the plugin's capabilities
int __stdcall GetPackerCaps(void)
{
	return PK_CAPS_BY_CONTENT | PK_CAPS_SEARCHTEXT | PK_CAPS_HIDE;
}

// Return the plugin's background operations support information
int __stdcall GetBackgroundFlags(void)
{
	return BACKGROUND_UNPACK;
}
