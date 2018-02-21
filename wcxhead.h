#pragma once

// Contents of file wcxhead.h version 2.21se (07.09.2011)
// It contains definitions of error codes, flags and callbacks

// Extended path length for Unicode functions
#define MAX_PATH_EX       1024

// Error codes returned to calling application
#define E_END_ARCHIVE       10      // No more files in archive
#define E_NO_MEMORY         11      // Not enough memory
#define E_BAD_DATA          12      // CRC error in the data of the currently unpacked file
#define E_BAD_ARCHIVE       13      // The archive as a whole is bad, e.g. damaged headers
#define E_UNKNOWN_FORMAT    14      // Archive format unknown
#define E_EOPEN             15      // Cannot open existing file
#define E_ECREATE           16      // Cannot create file
#define E_ECLOSE            17      // Error closing file
#define E_EREAD             18      // Error reading from file
#define E_EWRITE            19      // Error writing to file
#define E_SMALL_BUF         20      // Buffer too small
#define E_EABORTED          21      // Function aborted by user
#define E_NO_FILES          22      // No files found
#define E_TOO_MANY_FILES    23      // Too many files to pack
#define E_NOT_SUPPORTED     24      // Function not supported

// Flags for unpacking
#define PK_OM_LIST           0
#define PK_OM_EXTRACT        1

// Flags for ProcessFile
#define PK_SKIP              0      // Skip this file
#define PK_TEST              1      // Test file integrity
#define PK_EXTRACT           2      // Extract to disk

// Flags passed through ChangeVolProc
#define PK_VOL_ASK           0      // Ask user for location of next volume
#define PK_VOL_NOTIFY        1      // Notify app that next volume will be unpacked

// Flags for packing

// For PackFiles
#define PK_PACK_MOVE_FILES   1      // Delete original after packing
#define PK_PACK_SAVE_PATHS   2      // Save path names of files
#define PK_PACK_ENCRYPT      4      // Ask user for password, then encrypt

// Returned by GetPackCaps
#define PK_CAPS_NEW          1      // Can create new archives
#define PK_CAPS_MODIFY       2      // Can modify exisiting archives
#define PK_CAPS_MULTIPLE     4      // Archive can contain multiple files
#define PK_CAPS_DELETE       8      // Can delete files
#define PK_CAPS_OPTIONS     16      // Has options dialog
#define PK_CAPS_MEMPACK     32      // Supports packing in memory
#define PK_CAPS_BY_CONTENT  64      // Detect archive type by content
#define PK_CAPS_SEARCHTEXT 128      // Allow searching for text in archives
                                    // created with this plugin}
#define PK_CAPS_HIDE       256      // Show as normal files (hide packer
                                    // icon), open with Ctrl+PgDn, not Enter
#define PK_CAPS_ENCRYPT    512      // Plugin supports PK_PACK_ENCRYPT option

#define BACKGROUND_UNPACK    1      // Which operations are thread-safe?
#define BACKGROUND_PACK      2
#define BACKGROUND_MEMPACK   4

// Flags for packing in memory
#define MEM_OPTIONS_WANTHEADERS 1   // Return archive headers with packed data

// Errors returned by PackToMem
#define MEMPACK_OK           0      // Function call finished OK, but there is more data
#define MEMPACK_DONE         1      // Function call finished OK, there is no more data

#define PK_CRYPT_SAVE_PASSWORD       1
#define PK_CRYPT_LOAD_PASSWORD       2
#define PK_CRYPT_LOAD_PASSWORD_NO_UI 3  // Load password only if master password has already been entered!
#define PK_CRYPT_COPY_PASSWORD       4  // Copy encrypted password to new archive name
#define PK_CRYPT_MOVE_PASSWORD       5  // Move password when renaming an archive
#define PK_CRYPT_DELETE_PASSWORD     6  // Delete password

#define PK_CRYPTOPT_MASTERPASS_SET   1  // The user already has a master password defined

typedef struct {
	char ArcName[MAX_PATH];
	char FileName[MAX_PATH];
	int Flags;
	int PackSize;
	int UnpSize;
	int HostOS;
	int FileCRC;
	int FileTime;
	int UnpVer;
	int Method;
	int FileAttr;
	char* CmtBuf;
	int CmtBufSize;
	int CmtSize;
	int CmtState;
} tHeaderData;

typedef struct {
	char ArcName[MAX_PATH_EX];
	char FileName[MAX_PATH_EX];
	int Flags;
	unsigned int PackSize;
	unsigned int PackSizeHigh;
	unsigned int UnpSize;
	unsigned int UnpSizeHigh;
	int HostOS;
	int FileCRC;
	int FileTime;
	int UnpVer;
	int Method;
	int FileAttr;
	char* CmtBuf;
	int CmtBufSize;
	int CmtSize;
	int CmtState;
	char Reserved[1024];
} tHeaderDataEx;

typedef struct {
	WCHAR ArcName[MAX_PATH_EX];
	WCHAR FileName[MAX_PATH_EX];
	int Flags;
	unsigned int PackSize;
	unsigned int PackSizeHigh;
	unsigned int UnpSize;
	unsigned int UnpSizeHigh;
	int HostOS;
	int FileCRC;
	int FileTime;
	int UnpVer;
	int Method;
	int FileAttr;
	char* CmtBuf;
	int CmtBufSize;
	int CmtSize;
	int CmtState;
	char Reserved[1024];
} tHeaderDataExW;

typedef struct {
	char* ArcName;
	int OpenMode;
	int OpenResult;
	char* CmtBuf;
	int CmtBufSize;
	int CmtSize;
	int CmtState;
} tOpenArchiveData;

typedef struct {
	WCHAR* ArcName;
	int OpenMode;
	int OpenResult;
	WCHAR* CmtBuf;
	int CmtBufSize;
	int CmtSize;
	int CmtState;
} tOpenArchiveDataW;

typedef struct {
	int size;
	DWORD PluginInterfaceVersionLow;
	DWORD PluginInterfaceVersionHi;
	char DefaultIniName[MAX_PATH];
} PackDefaultParamStruct;

// Definition of callback functions called by the DLL
// Ask to swap disk for multi-volume archive
typedef int (__stdcall *tChangeVolProc)(char* ArcName, int Mode);
typedef int (__stdcall *tChangeVolProcW)(WCHAR* ArcName, int Mode);
// Notify that data is processed - used for progress dialog
typedef int (__stdcall *tProcessDataProc)(char* FileName, int Size);
typedef int (__stdcall *tProcessDataProcW)(WCHAR* FileName, int Size);
typedef int (__stdcall *tPkCryptProc)(int CryptoNr, int Mode, char* ArchiveName, char* Password, int maxlen);
typedef int (__stdcall *tPkCryptProcW)(int CryptoNr, int Mode, WCHAR* ArchiveName, WCHAR* Password, int maxlen);

// Definition of exported functions
HANDLE __stdcall OpenArchive(tOpenArchiveData* ArchiveData);
HANDLE __stdcall OpenArchiveW(tOpenArchiveDataW* ArchiveDataW);
int __stdcall ReadHeader(HANDLE hArcData, tHeaderData* HeaderData);
int __stdcall ProcessFile(HANDLE hArcData, int Operation, char* DestPath, char* DestName);
int __stdcall ProcessFileW(HANDLE hArcData, int Operation, WCHAR* DestPathW, WCHAR* DestNameW);
void __stdcall SetChangeVolProc(HANDLE hArcData, tChangeVolProc pChangeVolProc1);
void __stdcall SetChangeVolProcW(HANDLE hArcData, tChangeVolProcW pChangeVolProc1W);
void __stdcall SetProcessDataProc(HANDLE hArcData, tProcessDataProc pProcessDataProc);
void __stdcall SetProcessDataProcW(HANDLE hArcData, tProcessDataProcW pProcessDataProcW);
int __stdcall CloseArchive(HANDLE hArcData);

int __stdcall PackFiles(char* PackedFile, char* SubPath, char* SrcPath, char* AddList, int Flags);
int __stdcall PackFilesW(WCHAR* PackedFile, WCHAR* SubPath, WCHAR* SrcPath, WCHAR* AddList, int Flags);
int __stdcall DeleteFiles(char* PackedFile, char* DeleteList);
int __stdcall DeleteFilesW(WCHAR* PackedFile, WCHAR* DeleteList);
int __stdcall GetPackerCaps();
void __stdcall ConfigurePacker(HWND Parent, HINSTANCE DllInstance);
int __stdcall StartMemPack(int Options, char* FileName);
int __stdcall StartMemPackW(int Options, WCHAR* FileName);
int __stdcall PackToMem(int hMemPack, char* BufIn, int InLen, int* Taken, char* BufOut, int OutLen, int* Written, int SeekBy);
int __stdcall DoneMemPack(int hMemPack);
BOOL __stdcall CanYouHandleThisFile(char* FileName);
BOOL __stdcall CanYouHandleThisFileW(WCHAR* FileName);
void __stdcall PackSetDefaultParams(PackDefaultParamStruct* dps);
void __stdcall PkSetCryptCallback(tPkCryptProc pPkCryptProc, int CryptoNr, int Flags);
int __stdcall ReadHeaderEx(HANDLE hArcData, tHeaderDataEx* HeaderDataEx);
int __stdcall ReadHeaderExW(HANDLE hArcData, tHeaderDataExW* HeaderDataExW);
int __stdcall GetBackgroundFlags();
