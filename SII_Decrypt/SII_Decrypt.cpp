/*===============================================================================
  This file has been converted from Headers\SII_Decrypt_Header.pas
===============================================================================*/

/*===============================================================================

  Current SII Decrypt version:  1.4.2
  Current library API version:  1.0

  Note:

    Change in major version of library API marks compatibility change, minor
    version marks only changes that do not break backward compatibility.
    For example, if you implement your application for API of version 1.1, it
    will be still compatible with version 1.95, but not with version 2.0.

  Changelog:

    1.4.2 - no change in the library API
    1.4.1 - no change in the library API
    1.4.0 - started documenting changes
          - return values completely changed
          - added function APIVersion
          - added functions Is3nKEncodedMemory, Is3nKEncodedFile
          - added functions DecryptFileInMemory, DecodeFileInMemory and
            DecryptAndDecodeFileInMemory

===============================================================================*/

#pragma once

#include <stdint.h>
#include <Windows.h>

extern "C"
{

	/*
	  Types used in this unit (in case anyone will be translating this unit to other
	  languages):

	    Pointer   - general, untyped pointer
	    PPointer  - pointer to untyped pointer
	    TMemSize  - unsigned integer the size of pointer (8 bytes on 64bit system,
	                4 bytes on 32bit system)
	    PMemSize  - pointer to an unsigned pointer-sized integer
	    Int32     - signed 32bit integer
	    UInt32    - unsigned 32bit integer
	    PUTF8Char - pointer to the first character of UTF8-encoded, null-terminated
	                string
	    LongBool  = 32bit wide boolean value (0 = False; any other value = True)

	*/

	/*
	  Following are all possible values any library function can return.
	  For meaning of individual values, refer to description of functions that
	  returns them - only values the function can normally return are documented,
	  if it returns value that is not documented for that particular fucntion,
	  treat it as SIIDEC_RESULT_GENERIC_ERROR.
	  If any function returns value that is not listed here, you should process it
	  as if it returned SIIDEC_RESULT_GENERIC_ERROR.
	*/
	#define SIIDEC_RESULT_GENERIC_ERROR    -1
	#define SIIDEC_RESULT_SUCCESS           0
	#define SIIDEC_RESULT_FORMAT_PLAINTEXT  1
	#define SIIDEC_RESULT_FORMAT_ENCRYPTED  2
	#define SIIDEC_RESULT_FORMAT_BINARY     3
	#define SIIDEC_RESULT_FORMAT_3NK        4
	#define SIIDEC_RESULT_FORMAT_UNKNOWN    10
	#define SIIDEC_RESULT_TOO_FEW_DATA      11
	#define SIIDEC_RESULT_BUFFER_TOO_SMALL  12

	//==============================================================================

	/*-------------------------------------------------------------------------------

	  APIVersion

	  Returns version of API the library is providing. Lower 16 bits or returned
	  value contains minor version, higher 16 bits contains major version.

	  Returns:

	    Version of provided API.
	*/
	  uint32_t __stdcall APIVersion() { return 0; }

	/*-------------------------------------------------------------------------------

	  GetMemoryFormat

	  Returns format of the passed memory buffer.
	  The format is discerned acording to first four bytes (signature) and the size
	  is then checked againts that format (must be high enough to contain valid
	  data for the given format).

	  Parameters:

	    Mem  - Pointer to a memory block that should be scanned (must not be nil)
	    Size - Size of the memory block in bytes

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - memory contains plain-text SII file
	    SIIDEC_RESULT_FORMAT_ENCRYPTED - memory contains encrypted SII file
	    SIIDEC_RESULT_FORMAT_BINARY    - memory contains binary form of SII file
	    SIIDEC_RESULT_FORMAT_3NK       - memory contains 3nK-encoded SII file
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - memory contains unknown data format
	    SIIDEC_RESULT_TOO_FEW_DATA     - memory buffer is too small to contain valid
	                                     data for its format

	*/
	  int32_t __stdcall GetMemoryFormat(void* Mem, size_t Size) { return 0; }

	/*-------------------------------------------------------------------------------

	  GetFileFormat

	  Returns format of file given by its name (path).
	  It is recommended to pass full file path, but relative path is acceptable.
	  If the file does not exists, a generic error code is returned.
	  The format is discerned acording to first four bytes (signature) and the size
	  is then checked againts that format (must be high enough to contain valid
	  data for the given format).

	  Parameters:

	    FileName - path to the file that should be scanned

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - plain-text SII file
	    SIIDEC_RESULT_FORMAT_ENCRYPTED - encrypted SII file
	    SIIDEC_RESULT_FORMAT_BINARY    - binary form of SII file
	    SIIDEC_RESULT_FORMAT_3NK       - file is an 3nK-encoded SII file
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - file of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - file is too small to contain valid data for
	                                     its format

	*/
	  int32_t __stdcall GetFileFormat(char* FileName) { return 0; }

	/*-------------------------------------------------------------------------------

	  IsEncryptedMemory

	  Checks whether the passed memory buffer contains an encrypted SII file.

	  Parameters:

	    Mem  - Pointer to a memory block that should be checked (must not be nil)
	    Size - Size of the memory block in bytes

	  Returns:

	    Zero (false) when the buffer DOES NOT contain an encrypted SII file. When it
	    DOES contain an encrypted SII file, it returns non-zero value (true).
	*/
	  BOOL __stdcall IsEncryptedMemory(void* Mem, size_t Size) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  IsEncryptedFile

	  Checks whether the given file contains an encrypted SII file.
	  It is recommended to pass full file path, but relative path is acceptable.
	  If the file does not exists, zero (false) is returned.

	  Parameters:

	    FileName - path to the file that should be checked

	  Returns:

	    Zero (false) when the file is NOT an encrypted SII file. When it IS an
	    encrypted SII file, it returns non-zero value (true).
	*/
	  BOOL __stdcall IsEncryptedFile(char* FileName) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  IsEncodedMemory

	  Checks whether the passed memory buffer contains a binary SII file.

	  Parameters:

	    Mem  - Pointer to a memory block that should be checked (must not be nil)
	    Size - Size of the memory block in bytes

	  Returns:

	    Zero (false) when the buffer DOES NOT contain a binary SII file. When it
	    DOES contain a binary SII file, it returns non-zero value (true).
	*/
	  BOOL __stdcall IsEncodedMemory(void* Mem, size_t Size) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  IsEncodedFile

	  Checks whether the given file contains a binary SII file.
	  It is recommended to pass full file path, but relative path is acceptable.
	  If the file does not exists, zero (false) is returned.

	  Parameters:

	    FileName - path to the file that should be checked

	  Returns:

	    Zero (false) when the file is NOT a binary SII file. When it IS a binary SII
	    file, it returns non-zero value (true).
	*/
	  BOOL __stdcall IsEncodedFile(char* FileName) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  Is3nKEncodedMemory

	  Checks whether the passed memory buffer contains an 3nK-encoded SII file.

	  Parameters:

	    Mem  - Pointer to a memory block that should be checked (must not be nil)
	    Size - Size of the memory block in bytes

	  Returns:

	    Zero (false) when the buffer DOES NOT contain an 3nK-encoded SII file. When
	    it DOES contain an 3nK-encoded SII file, it returns non-zero value (true).
	*/
	  BOOL __stdcall Is3nKEncodedMemory(void* Mem, size_t Size) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  Is3nKEncodedFile

	  Checks whether the given file contains an 3nK-encoded SII file.
	  It is recommended to pass full file path, but relative path is acceptable.
	  If the file does not exists, zero (false) is returned.

	  Parameters:

	    FileName - path to the file that should be checked

	  Returns:

	    Zero (false) when the file is NOT an 3nK-encoded SII file. When it IS an
	    3nK-encoded SII file, it returns non-zero value (true).
	*/
	  BOOL __stdcall Is3nKEncodedFile(char* FileName) { return FALSE; }

	/*-------------------------------------------------------------------------------

	  DecryptMemory

	  Decrypts memory block given by the Input parameter and stores decrypted data
	  to a memory given by Output parameter.
	  To properly use this function, you have to call it twice. Do following:

	    - call this function with parameter Output set to nil (null/0), variable
	      pointed to by OutSize pointer can contain any value
	    - if the function returns SIIDEC_RESULT_SUCCESS, then minimal size of output
	      buffer is stored in a variable pointed to by parameter OutSize, otherwise
	      stop here and do not continue with next step
	    - use returned min. size of output buffer to allocate buffer for the next
	      step
	    - call this function again, this time with Output set to a buffer allocated
	      in previous step and value of variable pointed to by OutSize set to a size
	      of the allocated output buffer
	    - if the function returns SIIDEC_RESULT_SUCCESS, then true size of decrypted
	      data will be stored to a variable pointed to by parameter OutSize and
	      decrypted data will be stored to buffer passed in Output parameter,
	      otherwise nothing is stored in any output

	  Parameters:

	    Input   - pointer to a memory block containing input data (encrypted SII
	              file) (must not be nil)
	    InSize  - size of the input data in bytes
	    Output  - pointer to a buffer that will receive decrypted data
	    OutSize - pointer to a variable holding size of the output buffer, on return
	              receives true size of the decryted data (in bytes)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input data were successfully decrypted and
	                                     result stored in the output buffer
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input data contains plain-text SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_BINARY    - input data contains binary form of SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_3NK       - input data contains 3nK-encoded SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input data are of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input buffer is too small to contain
	                                     complete encrypted SII file header
	    SIIDEC_RESULT_BUFFER_TOO_SMALL - size of the output buffer given in OutSize
	                                     is too small to store all decrypted data

	*/
	  int32_t __stdcall DecryptMemory(void* Input, size_t InSize, void* Output, size_t* OutSize) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptFile

	  Decrypts file given by a path in InputFile parameter and stores decrypted
	  result in a file given by a path in OutputFile parameter.
	  It is recommended to pass full file paths, but relative paths are acceptable.
	  Folder, where the destination file will be stored, must exists prior of
	  calling this function, otherwise it fails with SIIDEC_RESULT_GENERIC_ERROR.
	  It is allowed to pass the same file as input and output.

	  Parameters:

	    InputFile   - path to the source file (encrypted SII file)
	    OutputFile  - path to the destination file (where decrypted result will be
	                  stored)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input file were successfully decrypted and
	                                     result stored in the output file
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input file contains plain-text SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_BINARY    - input file contains binary form of SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_3NK       - input file contains 3nK-encoded SII file
	                                     (does not need decryption)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input file is of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input file is too small to contain complete
	                                     encrypted SII file header

	*/
	#undef DecryptFile
	  int32_t __stdcall DecryptFile(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptFileInMemory

	  Works exactly the same as function DecryptFile (refer there for details), but
	  is implemented slightly differently. It reduces IO operations in exchange for
	  larger memory use.
	*/
	  int32_t __stdcall DecryptFileInMemory(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecodeMemoryHelper

	  Decodes (converts binary data to their textual form) memory block given by the
	  Input parameter and stores decoded data to a memory given by Output parameter.
	  Use of this function is somewhat complex, but it can be split into two, let's
	  say, paths - one where you use the provided Helper parameter, and one where
	  you don't.

	  When you will use the helper, do following:

	    - call this function with parameter Output set to nil (null/0), variable
	      pointed to by OutSize pointer can contain any value, Helper must contain
	      a valid pointer to pointer
	    - if the function returns SIIDEC_RESULT_SUCCESS, then minimal size of output
	      buffer is stored in a variable pointed to by parameter OutSize and
	      variable pointed to by Helper parameter receives helper object, otherwise
	      stop here and do not continue with next step
	    - use returned min. size of output buffer to allocate buffer for the next
	      step
	    - call this function again, this time with Output set to a buffer allocated
	      in previous step, value of variable pointed to by OutSize set to a size
	      of the allocated output buffer and Helper pointing to the same variable as
	      in first call
	    - if the function returns SIIDEC_RESULT_SUCCESS, then true size of decoded
	      data will be stored to a variable pointed to by parameter OutSize,
	      decoded data will be stored to buffer passed in Output parameter and
	      helper object will be consumed and freed, otherwise nothing is stored in
	      any output and you have to free the helper object using function
	      FreeHelper

	  If you won't use the helper, set the parameter Helper to nil. The procedure is
	  then the same as with the function DecryptMemory, so refer there.

	  This function cannot determine the size of result before actual decoding is
	  complete. So when you ask it for size of output buffer, it will do complete
	  decoding, which may be quite a long process (several seconds).
	  Helper is there to speed things up - when you use it (pass valid pointer), the
	  function stores helper object (DO NOT assume anything about it, consider it
	  being completely opaque) to a variable pointed to by Helper parameter. When
	  you allocate output buffer and call the function again, pass this returned
	  helper and the function will, instead of decoding the data again, only copy
	  data from decoding done in the first iteration.
	  WARNING - if you don't call the function second time or if the function fails
	  in the second call, you have to manually free the helper using function
	  FreeHelper, otherwise it will result in serious memory leak (tens of MiB).
	  Given mentioned facts, it is strongly recommended to use the helper whenever
	  possible, but with caution.

	  Parameters:

	    Input   - pointer to a memory block containing input data (binary SII
	              file) (must not be nil)
	    InSize  - size of the input data in bytes
	    Output  - pointer to a buffer that will receive decoded data
	    OutSize - pointer to a variable holding size of the output buffer, on return
	              receives true size of the decoded data (in bytes)
	    Helper  - pointer to a variable that will receive or contains helper

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input data were successfully decoded and
	                                     result stored in the output buffer
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input data contains plain-text SII file
	                                     (does not need decoding)
	    SIIDEC_RESULT_FORMAT_ENCRYPTED - input data contains encrypted SII file
	                                     (needs decrypting before decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input data are of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input buffer is too small to contain valid
	                                     binary or 3nK-encoded SII file
	    SIIDEC_RESULT_BUFFER_TOO_SMALL - size of the output buffer given in OutSize
	                                     is too small to store all decoded data

	*/
	  int32_t __stdcall DecodeMemoryHelper(void* Input, size_t InSize, void* Output, size_t* OutSize, void** Helper) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecodeMemory

	  Decodes (converts binary data to their textual form) memory block given by the
	  Input parameter and stores decoded data to a memory given by Output parameter.
	  Use of this function is exactly the same as for DecodeMemoryHelper when you do
	  not use helper, so refer there for details.

	  Parameters:

	    Input   - pointer to a memory block containing input data (binary SII
	              file) (must not be nil)
	    InSize  - size of the input data in bytes
	    Output  - pointer to a buffer that will receive decoded data
	    OutSize - pointer to a variable holding size of the output buffer, on return
	              receives true size of the decoded data (in bytes)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input data were successfully decoded and
	                                     result stored in the output buffer
	    SIIDEC_RESULT_FORMAT_PLAINTEXT  - input data contains plain-text SII file
	                                     (does not need decoding)
	    SIIDEC_RESULT_FORMAT_ENCRYPTED - input data contains encrypted SII file
	                                     (needs decrypting before decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input data are of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input buffer is too small to contain valid
	                                     binary or 3nK-encoded SII file
	    SIIDEC_RESULT_BUFFER_TOO_SMALL - size of the output buffer given in OutSize
	                                     is too small to store all decoded data

	*/
	  int32_t __stdcall DecodeMemory(void* Input, size_t InSize, void* Output, size_t* OutSize) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecodeFile

	  Decodes file given by a path in InputFile parameter and stores decoded result
	  in a file given by a path in OutputFile parameter.
	  It is recommended to pass full file paths, but relative paths are acceptable.
	  Folder, where the destination file will be stored, must exists prior of
	  calling this function, otherwise it fails with SIIDEC_RESULT_GENERIC_ERROR.
	  It is allowed to pass the same file as input and output.

	  Parameters:

	    InputFile   - path to the source file (binary SII file)
	    OutputFile  - path to the destination file (where decoded result will be
	                  stored)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input file was successfully decoded and
	                                     result stored in the output file
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input file contains plain-text SII file
	                                     (does not need decoding)
	    SIIDEC_RESULT_FORMAT_ENCRYPTED - input file contains encrypted SII file
	                                     (needs decrypting before decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input file is of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input file is too small to contain a valid
	                                     binary or 3nK-encoded SII file

	*/
	  int32_t __stdcall DecodeFile(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecodeFileInMemory

	  Works exactly the same as function DecodeFile (refer there for details), but
	  is implemented slightly differently. It reduces IO operations in exchange for
	  larger memory use.
	*/
	  int32_t __stdcall DecodeFileInMemory(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptAndDecodeMemoryHelper

	  Decrypts and, if needed, decodes memory block given by the Input parameter and
	  stores decoded data to a memory given by Output parameter.
	  Use is exactly the same as in function DecodeMemoryHelper, refer there for
	  details about how to properly use this function

	  Parameters:

	    Input   - pointer to a memory block containing input data (encrypted or
	              binary SII file) (must not be nil)
	    InSize  - size of the input data in bytes
	    Output  - pointer to a buffer that will receive decrypted and decoded data
	    OutSize - pointer to a variable holding size of the output buffer, on return
	              receives true size of the decrypted and decoded data (in bytes)
	    Helper  - pointer to a variable that will receive or contains helper

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input data were successfully decrypted
	                                     and/or decoded and result stored in the
	                                     output buffer
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input data contains plain-text SII file
	                                     (does not need decryption or decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input data are of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input buffer is too small to contain valid
	                                     encrypted or encoded SII file
	    SIIDEC_RESULT_BUFFER_TOO_SMALL - size of the output buffer given in OutSize
	                                     is too small to store all decrypted and
	                                     decoded data

	*/
	  int32_t __stdcall DecryptAndDecodeMemoryHelper(void* Input, size_t InSize, void* Output, size_t* OutSize, void** Helper) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptAndDecodeMemory

	  Decrypts and, if needed, decodes memory block given by the Input parameter and
	  stores decoded data to a memory given by Output parameter.
	  Use is exactly the same as in function DecodeMemory, refer there for details
	  about how to properly use this function

	  Parameters:

	    Input   - pointer to a memory block containing input data (encrypted or
	              binary SII file) (must not be nil)
	    InSize  - size of the input data in bytes
	    Output  - pointer to a buffer that will receive decrypted and decoded data
	    OutSize - pointer to a variable holding size of the output buffer, on return
	              receives true size of the decrypted and decoded data (in bytes)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input data were successfully decrypted
	                                     and/or decoded and result stored in the
	                                     output buffer
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input data contains plain-text SII file
	                                     (does not need decryption or decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input data are of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input buffer is too small to contain valid
	                                     encrypted or encoded SII file
	    SIIDEC_RESULT_BUFFER_TOO_SMALL - size of the output buffer given in OutSize
	                                     is too small to store all decrypted and
	                                     decoded data

	*/
	  int32_t __stdcall DecryptAndDecodeMemory(void* Input, size_t InSize, void* Output, size_t* OutSize) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptAndDecodeFile

	  Decrypts and, if needed, decodes file given by a path in InputFile parameter
	  and stores the result in a file given by a path in OutputFile parameter.
	  It is recommended to pass full file paths, but relative paths are acceptable.
	  Folder, where the destination file will be stored, must exists prior of
	  calling this function, otherwise it fails with SIIDEC_RESULT_GENERIC_ERROR.
	  It is allowed to pass the same file as input and output.

	  Parameters:

	    InputFile   - path to the source file (ecrypted or binary SII file)
	    OutputFile  - path to the destination file (where decrypted and decoded
	                  result will be stored)

	  Returns:

	    SIIDEC_RESULT_GENERIC_ERROR    - an unhandled exception have occured
	    SIIDEC_RESULT_SUCCESS          - input file was successfully decrypted
	                                     and/or decoded and result stored in the
	                                     output file
	    SIIDEC_RESULT_FORMAT_PLAINTEXT - input file contains plain-text SII file
	                                     (does not need decryption or decoding)
	    SIIDEC_RESULT_FORMAT_UNKNOWN   - input file is of an uknown format
	    SIIDEC_RESULT_TOO_FEW_DATA     - input file is too small to contain a valid
	                                     encrypted or encoded SII file

	*/
	  int32_t __stdcall DecryptAndDecodeFile(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  DecryptAndDecodeFileInMemory

	  Works exactly the same as function DecryptAndDecodeFile (refer there for
	  details), but is implemented slightly differently. It reduces IO operations
	  in exchange for larger memory use.
	*/
	  int32_t __stdcall DecryptAndDecodeFileInMemory(char* InputFile, char* OutputFile) { return 0; }

	/*-------------------------------------------------------------------------------

	  FreeHelper

	  Frees resources taken by a helper object allocated by DecodeMemoryHelper or
	  DecryptAndDecodeMemoryHelper function. Refer to those functions documentation
	  for details about when you have to call this function and when you don't.
	  Passing in an already freed object is allowed, the function just returns
	  immediately.

	  Parameters:

	    Helper - Pointer to a variable containing helper object to be freed

	  Returns:

	    This routine does not have a return value.
	*/
	void __stdcall FreeHelper(void** Helper) {}

	//==============================================================================
}
