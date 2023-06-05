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

struct VertexCoord
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
	~Graph();

	bool IsEmpty();
	bool IsFull();

	int GetVertPos(const int& vertex);
	int GetVertText(int i);

	vector<int> GetVertList();

	int GetAdjMatrixElem(int i, int j);
	int GetAmountVerts();
	int GetAmountEdges();

	void SetEdgeZero(int i, int j);
	void InsertVertex(const int& vertex);
	void InsertEdge(const int& vertex1, const int& vertex2, int weigth);
	void Print();
	void EraseLastVert();
	void EraseEdge(const int& vertex1, const int& vertex2);
	void DrawGraph();
};

extern Graph graph;

void mouseMove(int x, int y);

void makeGraph();
void reshape(int w, int h);
void display();

int** Change_Matrix();
int* Search_MinElem(int* line, int n);

void Print_Matrix(int** matrix);

int** Reduct_Matrix(int** oldmatrix);
int** High_Zero(int** oldmatrix);

void Print_Result();
void setCoords(int i, int n);

bool SalesmanPossible(int** matrix);

void ButtonMouseOn(int x, int y);
void mouseMove(int x, int y);
void mouseClick(int button, int state, int x, int y);

void drawBtnSalesman();
void drawBtnNewGraph();
void drawBtnAddVertex();
void drawBtnDelVertex();
void drawBtnAddEdge();
void drawBtnDelEdge();

void drawCircle(int x, int y, int R, bool r);
void drawText(int nom, int x1, int y1, bool red);
void drawLine(int text, int x0, int y0, int x1, int y1, bool b);
void drawVertex(int n, bool r);