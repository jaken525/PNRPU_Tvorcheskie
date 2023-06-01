#include "Undat.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <shlwapi.h>
#include <vector>
#include <filesystem>
#include "Screen.h"

namespace fs = std::filesystem;

int _progress = 0;
int endPoint = 0;

bool Unpacker::OpenFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;

	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == false || dwBytesRead != fsize)
	{
		fsize = 0;
		delete[] f;
		f = NULL;
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);

	return true;
}

bool DAT::OpenFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;

	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == false || dwBytesRead != fsize)
	{
		fsize = 0;
		delete[] f;
		f = NULL;
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);

	return true;
}

	std::string DAT::ReadStringWithout(char*& f, size_t& pos, int size)
	{
		std::string result = "";
		bool isWriting = true;

		for (int i = 0; i < size; i++)
		{
			if (f[pos] != 0 && isWriting)
				result += f[pos];
			else
				isWriting = false;
			pos += 1;
		}

		return result;
	}

	std::string DAT::ReadString(char*& f, size_t& pos, int size)
	{
		std::string result = "";

		for (int i = 0; i < size; i++)
		{
			result += f[pos];
			pos += 1;
		}

		return result;
	}

	std::string DAT::WriteString(int size, std::string str)
	{
		size -= str.length();

		std::string endLine = "";
		endLine += str;

		for (int i = 0; i < size; i++)
			endLine += char(uint8_t(0));

		return endLine;
	}

	std::string DAT::WriteLong(int num)
	{
		std::string Hex = "";
		std::stringstream s;
		s << std::hex << num;

		int zeroes = 8 - size(s.str());
		for (int i = 0; i < zeroes; i++)
			Hex += "0";
		Hex += s.str();

		int arr[] = { 0, 0, 0, 0 };
		int c = 3;
		for (int i = 0; i < Hex.length() - 1; i += 2)
		{
			std::stringstream h;
			h << Hex[i] << Hex[i + 1];
			h >> std::hex >> arr[c];
			c--;
		}

		Hex = "";
		for (int i = 0; i < 4; i++)
			Hex += char(uint8_t(arr[i]));

		return Hex;
	}

	unsigned long DAT::readlong(char*& f, size_t& pos)
	{
		unsigned long result =
		{
			(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
			(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
			(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
			(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
		};
		pos += 4;
		return result;
	}

	bool DAT::ReadAndWriteFolders(char*& f, size_t& pos, size_t& fsize, std::string n)
	{
		if (!fs::exists((*currentPath) + "\\" + n))
			fs::create_directory((*currentPath) + "\\" + n);

		bool sucess = false;

		num_folders = readlong(f, pos);
		endPoint = int(fsize);
		num_files = readlong(f, pos);

		folderID = new uint32_t[num_folders];
		folderName = new std::string[num_folders];

		fileName = new std::string[num_files];
		fileOffset = new size_t[num_files];
		fileSize = new uint32_t[num_files];
		fileTSTAMPfst = new uint32_t[num_files];
		fileTSTAMPsnd = new uint32_t[num_files];
		fileFolderID = new uint32_t[num_files];
		fileFolderIDTemp = new uint32_t[num_files];

		// folders
		for (int i = 0; i < num_folders; i++)
		{
			folderID[i] = readlong(f, pos);
			folderName[i] = ReadStringWithout(f, pos, 128);
		}

		_progress = pos;

		// files
		for (int i = 0; i < num_files; i++)
		{
			fileFolderID[i] = readlong(f, pos);
			fileFolderIDTemp[i] = fileFolderID[i];
			fileName[i] = ReadStringWithout(f, pos, 128);
			fileOffset[i] = readlong(f, pos);
			fileSize[i] = readlong(f, pos);

			pos += 4; // skip zeroes

			fileTSTAMPfst[i] = readlong(f, pos);
			fileTSTAMPsnd[i] = readlong(f, pos);

			_progress = pos;

			std::vector<std::string> folders;
			while (fileFolderID[i] != 0)
			{
				fileFolderID[i] -= 1;

				folders.push_back(folderName[fileFolderID[i]]);
				fileFolderID[i] = folderID[fileFolderID[i]];
			}

			std::string path = (*currentPath) + "\\" + n + "\\";
			for (int j = folders.size() - 1; j >= 0; j--)
			{
				path += folders[j] + "\\";

				if (!fs::exists(path))
					fs::create_directory(path);
			}

			filesPath.push_back(path);
		}

//		_progress = 0;
		return sucess;
	}

	void DAT::WriteFiles(char*& f, size_t& pos, size_t& fsize)
	{
		for (int i = 0; i < num_files; i++)
		{
			std::string filepath = filesPath[i] + fileName[i];

			std::ofstream file(filepath, std::ios_base::binary);
			file << ReadString(f, fileOffset[i], fileSize[i]);
			file.close();
		}
	}

	void DAT::CreateArchive(std::string n, bool cBackup, bool cStartScreen)
	{
		std::ofstream tempWrite((*currentPath) + "\\" + n + ".temp", std::ios::binary);
		size_t archiveIntro = (num_folders * 4 + num_folders * 128) + (num_files * 16 + num_files * 128 + num_files * 8) + 8;
		size_t temp = 0;

		for (int i = 0; i < num_files; i++)
		{
			if (fs::exists(filesPath[i] + fileName[i]))
			{
				char* f = NULL;
				size_t fsize = 0;
				size_t ptr = 0;

				if (OpenFile(f, fsize, filesPath[i] + fileName[i]))
				{
					fileOffset[i] = archiveIntro + temp;

					if (fileName[i] == "CARGANDO.BMP" && cStartScreen)
					{
						fileSize[i] = std::size(tex::startScreen);
						temp += std::size(tex::startScreen) + 4;

						for (int j = 0; j < std::size(tex::startScreen); j++)
							tempWrite << char(tex::startScreen[j]);

						tempWrite << WriteLong(0);
					}
					else
					{
						fileSize[i] = fsize;

						temp += fsize + 4;

						tempWrite << ReadString(f, ptr, fsize) << WriteLong(0);
					}
				}

				if (f != NULL)
				{
					delete[] f;
					f = NULL;
				}
			}
			else
			{
				tempWrite.close();
				fs::remove((*currentPath) + "\\" + n + ".temp");

				return;
			}
		}

		tempWrite.close();

		if (cBackup)
			fs::rename((*currentPath) + "\\" + n + ".dat", (*currentPath) + "\\" + n + "old.dat");
		else
			fs::remove((*currentPath) + "\\" + n + ".dat");

		std::ofstream archive((*currentPath) + "\\" + n + ".dat", std::ios::binary);

		archive << WriteLong(num_folders) << WriteLong(num_files);
		for (int i = 0; i < num_folders; i++)
			archive << WriteLong(folderID[i]) << WriteString(128, folderName[i]);

		for (int i = 0; i < num_files; i++)
			archive << WriteLong(fileFolderIDTemp[i])
			<< WriteString(128, fileName[i])
			<< WriteLong(fileOffset[i])
			<< WriteLong(fileSize[i])
			<< WriteLong(0)
			<< WriteLong(fileTSTAMPfst[i])
			<< WriteLong(fileTSTAMPsnd[i]);

		if (fs::exists((*currentPath) + "\\" + n + ".temp"))
		{
			char* f = NULL;
			size_t fsize = 0;
			size_t ptr = 0;

			if (OpenFile(f, fsize, (*currentPath) + "\\" + n + ".temp"))
			{
				std::string strTemp = ReadString(f, ptr, fsize);
				archive << strTemp;
			}

			if (f != NULL)
			{
				delete[] f;
				f = NULL;
			}
		}
		else
		{
			archive.close();
			return;
		}

		archive.close();
		fs::remove((*currentPath) + "\\" + n + ".temp");
	}

void Unpacker::SetPath(std::string path)
{
	_currentPath = new std::string{ path };
}

void Unpacker::Extract(std::string name)
{
	char* f = NULL;
	size_t fsize = 0;

	if (OpenFile(f, fsize, (*_currentPath) + "\\" + name + ".dat"))
	{
		DAT dat((*_currentPath));
		size_t ptr = 0;

		dat.ReadAndWriteFolders(f, ptr, fsize, name);

		dat.WriteFiles(f, ptr, fsize);
	}

	if (f != NULL)
	{
		delete[] f;
		f = NULL;
	}
}

void Unpacker::PackBack(std::string name)
{
	if (fs::exists((*_currentPath) + "\\" + name))
	{
		char* f = NULL;
		size_t fsize = 0;

		if (OpenFile(f, fsize, (*_currentPath) + "\\" + name + ".dat"))
		{
			DAT dat((*_currentPath));
			size_t ptr = 0;

			dat.ReadAndWriteFolders(f, ptr, fsize, name);

			dat.CreateArchive(name, createBackup, changeStartScreen);
		}

		if (f != NULL)
		{
			delete[] f;
			f = NULL;
		}
	}
}