/*
Made by mariokart64n (coreynguyen) from XeNTaX
https://forum.xentax.com/memberlist.php?mode=viewprofile&u=531
https://github.com/coreynguyen/beetle_crazy_cup
*/
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

public ref class inf2obj
{
public:
	bool block = false;
	float* vertices = NULL;
	int num_triangles = 0;
	int num_vertices = 0;
	int* verTri = NULL;

	std::string* path;

	inf2obj()
	{
		num_triangles = 0;
		num_vertices = 0;
		vertices = NULL;
		verTri = NULL;
	}
	~inf2obj()
	{
		delete[] vertices;
		delete[] verTri;
	}

	void Reset()
	{
		num_triangles = 0;
		num_vertices = 0;

		vertices = NULL;
		verTri = NULL;
	}

	std::string openfilename();
	bool openFile(char*& f, size_t& fsize, std::string filename);
	unsigned long readlong(char*& f, size_t& pos);
	std::string getFilenamePath(const std::string str);
	std::string getFilenameFile(const std::string str);
	int Convert();
};

struct fmtINF
{
public:
	uint32_t num_vertices = 0;
	uint32_t num_triangles = 0;
	float* vertices;
	float* tvertices;
	float* normals;
	uint16_t* nor_triangles;
	int* ver_triangles;
	uint32_t* tex_triangles;

	fmtINF()
	{
		vertices = NULL;
		tvertices = NULL;
		normals = NULL;
		nor_triangles = NULL;
		ver_triangles = NULL;
		tex_triangles = NULL;
	}
	~fmtINF()
	{
		if (vertices = NULL) delete[] vertices;
		if (tvertices = NULL) delete[] tvertices;
		if (normals = NULL) delete[] normals;
		if (nor_triangles = NULL) delete[] nor_triangles;
		if (ver_triangles = NULL) delete[] ver_triangles;
		if (tex_triangles = NULL) delete[] tex_triangles;
	}

	unsigned short readshort(char*& f, size_t& pos);
	unsigned long readlong(char*& f, size_t& pos);
	float readfloat(char*& f, size_t& pos);
	bool openFile(char*& f, size_t& fsize, std::string filename);
	bool readVer(std::string fpath, std::string fname);
	void write_obj(std::string file);
	int* GetVerteciesTriangles();
};

struct fmtTRI
{
public:
	uint32_t num_triangles = 0;
	uint16_t* nor_triangles;
	int* ver_triangles;
	uint32_t* tex_triangles;

	fmtTRI()
	{
		nor_triangles = NULL;
		ver_triangles = NULL;
		tex_triangles = NULL;
	}
	~fmtTRI()
	{
		if (nor_triangles = NULL) delete[] nor_triangles;
		if (ver_triangles = NULL) delete[] ver_triangles;
		if (tex_triangles = NULL) delete[] tex_triangles;
	}

	unsigned short readshort(char*& f, size_t& pos);
	unsigned long readlong(char*& f, size_t& pos);
	bool openFile(char*& f, size_t& fsize, std::string filename);
	bool readTri(std::string fpath, std::string fname);
};