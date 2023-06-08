#pragma once
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int maxSize = 20;
extern int WinW;
extern int WinH;

struct VertexCoordinates
{
	int x, y;
};

class Graph 
{
private:
	vector<int> vertList;

public:
	int adjMatrix[maxSize][maxSize];

	Graph();
	~Graph() {}

	bool IsEmpty()
	{
		if (vertList.size() != 0)
			return false;
		else
			return true;
	}
	bool IsFull() { return (vertList.size() == maxSize); }

	int GetVerticesPos(const int& vertex);
	int GetVerticesText(int i) { return vertList[i]; }

	vector<int> GetVerticesList() { return  vertList; }

	int GetAdjMatrixElement(int i, int j) { return adjMatrix[i][j]; }
	int GetAmountVertices() { return vertList.size(); }
	int GetAmountEdges();

	void SetEdgeZero(int i, int j) { adjMatrix[i][j] = 0; adjMatrix[j][i] = 0; }
	void InsertVertex(const int& vertex);
	void InsertEdge(const int& vertex1, const int& vertex2, int weigth);
	void EraseLastVertex();
	void EraseEdge(const int& vertex1, const int& vertex2);

	void PrintGraph();
	void DrawGraph();
};

extern Graph graph;

void MakeGraph();
void Reshape(int w, int h);
void Display();

void drawButtonSalesman();
void drawButtonNewGraph();
void drawButtonAddVertex();
void drawButtonDelVertex();
void drawButtonAddEdge();
void drawButtonDelEdge();

int** ChangeMatrix();
int* SearchMinElement(int* line, int n);

void PrintMatrix(int** matrix);

int** ReductMatrix(int** oldmatrix);
int** HighZero(int** oldmatrix);

void PrintResult();
void SetCoordinats(int i, int n);

bool IsSalesmanPossible(int** matrix);

void ButtonMouseOn(int x, int y);
void mouseMove(int x, int y);
void mouseClick(int button, int state, int x, int y);

void drawCircle(int x, int y, int R, bool r);
void drawText(int nom, int x1, int y1, bool red);
void drawLine(int text, int x0, int y0, int x1, int y1, bool b);
void drawVertex(int n, bool r);