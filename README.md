# wcx_sii_decrypt
This is a Total Commander plugin for unpacking SII files: save data from SCS games.

Currently tested on Euro Truck Simulator 2 and American Truck Simulator. Supported types:
* encrypted text format;
* encrypted binary format;
* plain binary format.

The SII file is opened as an archive containing a single TXT file representing the plain text contents you can view or extract.

**Note:**

The TXT file size is displayed as 0 because it is impossible to know the size of the decrypted data without actual decrypting, and this can be quite long. I didn't want to make opening the archive too slow.

## Requirements and Dependencies
The project is based on the [SII_Decrypt](https://github.com/ncs-sniper/SII_Decrypt) project by František Milt. The DLLs from it are packaged along with the plugin and are used for the actual decrypting and decoding.

The `SII_Decrypt` DLLs can be updated independently as long as the binary interface remains compatible.

#### Minimal requirements for the 32-bit version:
* Windows XP SP2
* Total Commander 7.50 32-bit

#### Minimal requirements for the 64-bit version:
* Processor with 64-bit instruction set (Intel Pentium 4, AMD Athlon 64 and higher)
* Windows XP x64
* Total Commander 8.0 64-bit

## Build from Sources
To build the project you need Microsoft Visual Studio 2015 Community Edition. Other versions, like 2013 or 2017, will probably work too but were not tested. Just open the project and build the Release version for Win32 and x64 architectures.

When the `SII_Decrypt` project updates without breaking compatibility it is enough to just replace the DLL files in the respective subdirectory and the plugin installation package. If API changes were introduced you'll need to perform the following steps:
1. Update the DLL files in the `SII_Decrypt` subdirectory (Lazarus-built versions are preferred, because they are both 32- and 64-bit).
2. Edit the files `SII_Decrypt.h`, `SII_Decrypt.cpp`, `SII_Decrypt.def` to reflect the changes:
   * The header file contains function definitions ported from the original Pascal header file ([Headers\SII_Decrypt_Header.pas](https://github.com/ncs-sniper/SII_Decrypt/blob/master/Headers/SII_Decrypt_Header.pas)).
   * The DEF file lists the exported functions, so you only need to edit it if a function was added or deleted.
   * The CPP file contains fake implementations of the exported functions declared in the H file (needed for generating the correct LIB for the 32-bit version).
3. Update the LIB files by running `genlib.cmd` (don't forget to fix the path to `vcvarsall.bat` if you are using a different version of MSVC).
4. Build the main project.

## Version history
### 1.4.0.0, 25.08.2018
* Updated to SII_Decrypt 1.4.2.

### 1.0.0.0, 23.02.2018
* First public version.
