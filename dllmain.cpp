// dllmain.cpp : Defines the entry point for the DLL application.

#include "stdafx.h"
#include "wcx_sii_decrypt.h"

HMODULE hSiiModule = NULL;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			WCHAR path[MAX_PATH];
			GetModuleFileName(hModule, path, MAX_PATH);
			WCHAR* pos = wcsrchr(path, L'\\');
			if (pos != NULL)
				*pos = L'\0';
#if defined _M_X64
			wcscat_s(path, L"\\SII_Decrypt_64.dll");
#else
			wcscat_s(path, L"\\SII_Decrypt_32.dll");
#endif
			hSiiModule = LoadLibrary(path);
			break;
		}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		{
			if (hSiiModule != NULL)
				FreeLibrary(hSiiModule);
			break;
		}
	}
	return TRUE;
}

