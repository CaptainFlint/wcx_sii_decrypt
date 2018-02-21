#pragma once

// Structure to store the current archive data
struct ArchiveHandleW
{
	WCHAR ArcName[MAX_PATH_EX];             // Full path to the archive
	int OpenMode;                           // Open mode (if archive is opened for listing or unpacking)
	tProcessDataProcW pProcessDataProcW;    // Callback function for progress bar updating
	HANDLE hFile;                           // Handle to the archive being processed
	size_t ContentsPos;                     // Index of the currently requested file in the archive (only 1 file, so can be only 0)
};
