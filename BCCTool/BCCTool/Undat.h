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

extern int _progress;
extern int endPoint;

public ref class Unpacker
{
public:
	bool createBackup;
	bool changeStartScreen;

	std::string* _currentPath;

	Unpacker()
	{
		_progress = 0;
		endPoint = 0;

		createBackup = true;
		changeStartScreen = true;
	}

	~Unpacker()
	{
		delete _currentPath;
	}

public:
	bool OpenFile(char*& f, size_t& fsize, std::string filename);

	void SetPath(std::string path);
	void Extract(std::string name);
	void PackBack(std::string name);
};

struct DAT
{
public:
	uint32_t num_folders = 0;
	uint32_t num_files = 0;

	uint32_t* folderID;
	uint32_t* fileFolderID;
	uint32_t* fileFolderIDTemp;
	size_t* fileOffset;
	uint32_t* fileSize;
	uint32_t* fileTSTAMPfst;
	uint32_t* fileTSTAMPsnd;

	std::string* folderName;
	std::string* fileName;
	std::string* currentPath;
	std::vector<std::string> filesPath;

	DAT(std::string path)
	{
		currentPath = new std::string{ path };
		folderID = NULL;
		folderName = NULL;
		fileName = NULL;
		fileOffset = NULL;
		fileSize = NULL;
		fileTSTAMPfst = NULL;
		fileTSTAMPsnd = NULL;
		fileFolderID = NULL;
		fileFolderIDTemp = NULL;
	}
	~DAT()
	{
		if (folderID = NULL) delete[] folderID;
		if (folderName = NULL) delete[] folderName;
		if (fileName = NULL) delete[] fileName;
		if (fileOffset = NULL) delete[] fileOffset;
		if (fileSize = NULL) delete[] fileSize;
		if (fileTSTAMPfst = NULL) delete[] fileTSTAMPfst;
		if (fileTSTAMPsnd = NULL) delete[] fileTSTAMPsnd;
		if (fileFolderID = NULL) delete[] fileFolderID;
		if (fileFolderIDTemp = NULL) delete[] fileFolderIDTemp;
	}

	std::string ReadStringWithout(char*& f, size_t& pos, int size);
	std::string ReadString(char*& f, size_t& pos, int size);
	std::string WriteString(int size, std::string str);
	std::string WriteLong(int num);

	unsigned long readlong(char*& f, size_t& pos);

	bool OpenFile(char*& f, size_t& fsize, std::string filename);
	bool ReadAndWriteFolders(char*& f, size_t& pos, size_t& fsize, std::string n);

	void WriteFiles(char*& f, size_t& pos, size_t& fsize);
	void CreateArchive(std::string n, bool cBackup, bool cStartScreen);
};