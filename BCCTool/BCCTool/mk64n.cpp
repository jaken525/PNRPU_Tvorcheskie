#include "mk64n.h"
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

namespace fs = std::filesystem;

std::string inf2obj::openfilename()
{
	std::string filename(MAX_PATH, '\0');
	OPENFILENAME ofn = { };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "INF Files (*.inf)\0*.inf\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = &filename[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	if (!GetOpenFileName(&ofn))
		return "";
	return filename;
}

std::string inf2obj::getFilenamePath(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");
	if (found != std::string::npos)
	{
		strt = str.substr(0, found);
		return (strt + "\\");
	}
	else return "";
}

std::string inf2obj::getFilenameFile(const std::string str)
{
	size_t found;
	std::string strt;
	found = str.find_last_of("/\\");
	if (found < str.size())
	{
		strt = str.substr(found + 1, -1);
		found = strt.find(".");
		if (found < strt.size())
			strt = strt.substr(0, found);
	}
	else strt = str;
	size_t lastdot = strt.find_last_of(".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
}

unsigned long inf2obj::readlong(char*& f, size_t& pos)
{
	unsigned long result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
		(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
		(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
	};
	pos += 4;
	return result;
}

int inf2obj::Convert()
{
	block = true;

	std::string file = "";
	file = openfilename();

	if (!fs::exists(*path + "\\Converted"))
		fs::create_directory(*path + "\\Converted");

	if (file != "")
	{
		char* f = NULL;
		size_t fsize = 0;
		if (openFile(f, fsize, file))
		{
			fmtINF inf;
			fmtTRI tri;
			size_t ptr = 0;
			std::string fpath = getFilenamePath(file);
			std::string fname = getFilenameFile(file);

			inf.num_vertices = readlong(f, ptr);
			inf.num_triangles = readlong(f, ptr);
			tri.num_triangles = inf.num_triangles;

			inf.readVer(fpath, fname);
			tri.readTri(fpath, fname);

			inf.ver_triangles = tri.ver_triangles;
			inf.nor_triangles = tri.nor_triangles;
			inf.tex_triangles = tri.tex_triangles;

			verTri = tri.ver_triangles;
			num_triangles = tri.num_triangles;
			vertices = inf.vertices;
			num_vertices = inf.num_vertices;

			inf.write_obj(*path + "\\Converted\\" + fname + ".obj");
		}
		if (f != NULL)
			delete[] f;
	}

	block = false;

	return 0;
}

unsigned short fmtINF::readshort(char*& f, size_t& pos)
{
	unsigned short result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100)
	};
	pos += 2;
	return result;
}

unsigned long fmtINF::readlong(char*& f, size_t& pos)
{
	unsigned long result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
		(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
		(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
	};
	pos += 4;
	return result;
}

unsigned short fmtTRI::readshort(char*& f, size_t& pos)
{
	unsigned short result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100)
	};
	pos += 2;
	return result;
}

unsigned long fmtTRI::readlong(char*& f, size_t& pos)
{
	unsigned long result = {
		(unsigned int)((uint8_t)f[pos] * 0x00000001) + \
		(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
		(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
		(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
	};
	pos += 4;
	return result;
}

float fmtINF::readfloat(char*& f, size_t& pos)
{
	float result = 0.0;
	unsigned long b = readlong(f, pos);
	memcpy(&result, &b, 4);
	return result;
}

bool fmtINF::openFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << " Failed to Open File\n";
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		std::cout << " Failed to read file. File is Empty?\n";
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;
	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize)
	{
		std::cout << " Failed to copy file into memory\n";
		fsize = 0;
		delete[] f;
		f = NULL;
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

bool fmtTRI::openFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << " Failed to Open File\n";
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		std::cout << " Failed to read file. File is Empty?\n";
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;
	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize)
	{
		std::cout << " Failed to copy file into memory\n";
		fsize = 0;
		delete[] f;
		f = NULL;
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);

	return true;
}

bool inf2obj::openFile(char*& f, size_t& fsize, std::string filename)
{
	HANDLE hFile = CreateFile(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << " Failed to Open File\n";
		return false;
	}

	fsize = GetFileSize(hFile, NULL);
	if (fsize == 0)
	{
		std::cout << " Failed to read file. File is Empty?\n";
		return false;
	}

	f = new char[fsize];
	unsigned long dwBytesRead = 0;
	if (ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize)
	{
		std::cout << " Failed to copy file into memory\n";
		fsize = 0;
		delete[] f;
		f = NULL;
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);

	return true;
}

bool fmtINF::readVer(std::string fpath, std::string fname)
{
	bool sucess = false;
	std::string verFile = fpath + fname + ".ver";

	if (num_vertices > 0)
	{
		char* f1 = NULL;
		size_t fsize1 = 0;
		size_t pos1 = 0;

		if (openFile(f1, fsize1, verFile))
		{
			vertices = new float[num_vertices * 3];
			tvertices = new float[num_vertices * 2];
			for (int i = 0; i < num_vertices; i++)
			{
				vertices[i * 3] = readfloat(f1, pos1);
				vertices[(i * 3) + 1] = readfloat(f1, pos1);
				vertices[(i * 3) + 2] = readfloat(f1, pos1);
				tvertices[i * 2] = readfloat(f1, pos1);
				tvertices[(i * 2) + 1] = readfloat(f1, pos1);
			}
		}
		if (f1 != NULL)
			delete[] f1;

	}
	return sucess;
}

bool fmtTRI::readTri(std::string fpath, std::string fname)
{
	bool sucess = false;
	std::string triFile = fpath + fname + ".tri";

	if (num_triangles > 0)
	{
		char* f = NULL;
		size_t fsize = 0;
		size_t pos = 0;

		if (openFile(f, fsize, triFile))
		{
			nor_triangles = new uint16_t[num_triangles * 3];
			ver_triangles = new int[num_triangles * 3];
			tex_triangles = new uint32_t[num_triangles];

			for (int i = 0; i < num_triangles; i++)
			{
				ver_triangles[i * 3] = readshort(f, pos);
				nor_triangles[i * 3] = readshort(f, pos);
				ver_triangles[(i * 3) + 1] = readshort(f, pos);
				nor_triangles[(i * 3) + 1] = readshort(f, pos);
				ver_triangles[(i * 3) + 2] = readshort(f, pos);
				nor_triangles[(i * 3) + 2] = readshort(f, pos);
				tex_triangles[i] = readshort(f, pos);

				readshort(f, pos);
			}
		}
		if (f != NULL)
			delete[] f;

		sucess = (num_triangles > 0) || sucess;
	}
	return sucess;
}

void fmtINF::write_obj(std::string file)
{
	std::string line;
	std::ofstream obj(file.c_str());
	int fp = 6;
	if (obj.is_open())
	{
		obj << "Beetle Crazy Cup/Beetle Buggin'/Kafer" << std::endl;
		obj << "https://forum.xentax.com/viewtopic.php?p=179690#p179690" << std::endl;
		obj << std::endl << "# Num Vertices " << num_vertices << std::endl;
		for (int i = 0; i < num_vertices; i++)
		{
			obj << "v " << std::fixed << std::setprecision(fp);
			obj << vertices[(i * 3)] << " ";
			obj << vertices[(i * 3) + 1] << " ";
			obj << vertices[(i * 3) + 2] << std::endl;
		}

		obj << std::endl << "# Num Texture Vertices " << num_vertices << std::endl;
		for (int i = 0; i < num_vertices; i++)
		{
			obj << "vt " << std::fixed << std::setprecision(fp);
			obj << tvertices[(i * 2)] << " ";
			obj << tvertices[(i * 2) + 1] << std::endl;
		}

		obj << std::endl << "# Num Faces " << num_triangles << std::endl;
		for (int i = 0; i < num_triangles; i++)
		{
			obj << "usemtl " << tex_triangles[i] << std::endl;
			obj << "f " << ver_triangles[(i * 3)] + 1 << "/";
			obj << nor_triangles[(i * 3)] + 1 << "/";
			obj << nor_triangles[(i * 3)] + 1 << " ";
			obj << ver_triangles[(i * 3) + 2] + 1 << "/";
			obj << nor_triangles[(i * 3) + 2] + 1 << "/";
			obj << nor_triangles[(i * 3) + 2] + 1 << " ";
			obj << ver_triangles[(i * 3) + 1] + 1 << "/";
			obj << nor_triangles[(i * 3) + 1] + 1 << "/";
			obj << nor_triangles[(i * 3) + 1] + 1 << std::endl;
		}
		obj.close();
	}
}

int* fmtINF::GetVerteciesTriangles()
{
	int* newArr = new int[num_triangles * 3];

	for (int i = 0; i < num_triangles * 3; i++)
		newArr[i] = ver_triangles[i];

	return newArr;
}