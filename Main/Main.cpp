#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <winuser.h>
#include <handleapi.h>
#include "GenericTreeNode.h"
#include "GenericTree.h"
using namespace std;

template<class T>
class GenericTreeNode;

template<class T>
class GenericTree;

bool ListDirectoryContents(const wchar_t *sDir, FILE * outFile);

int main()
{
	FILE * outFile;
	outFile = fopen("mydirectory.txt", "w");
	ListDirectoryContents(L"F:\\", outFile);
	fclose(outFile);
	
	system("pause");
	return 0;
}

bool ListDirectoryContents(const wchar_t *sDir, FILE *outFile)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	wchar_t sPath[2048];

	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
		fwprintf(outFile,L"Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				wprintf(L"Directory: %s\n", sPath);
				fwprintf(outFile,L"Directory: %s\n", sPath);
				ListDirectoryContents(sPath, outFile);
			}
			else {
				wprintf(L"File: %s\n", sPath);
				fwprintf(outFile,L"File: %s\n", sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);
	
	return true;
}