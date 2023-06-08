#include "Graph.h"

using namespace std;

int WinW = 960;
int WinH = 720;
int R;
int ver = 0;

bool ButtonSalesmanSecond = false;
bool* vertmouse = new bool[maxSize];
bool standView = false;
bool vertmove = false;
bool commiglut = false;
bool prohod = false;

int ButtonCheck;
int Moving_Vertex;
int x_coord_mouse;
int y_coord_mouse;

VertexCoordinates vertcrd[maxSize + 2];

Graph graph;

vector<pair<int, int>> Way;
vector<int> New_Way;

Graph::Graph()
{
	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++)
			adjMatrix[i][j] = 0;

		vertmouse[i] = false;
	}
}

int Graph::GetVerticesPos(const int& vertex)
{
	for (size_t i = 0; i < vertList.size(); i++)
		if (vertList[i] == vertex)
			return i;

	return -1;
}

int Graph::GetAmountEdges()
{
	int numb = 0;
	for (int i = 0; i < vertList.size(); i++)
		for (int j = 0; j < vertList.size(); j++)
			if (adjMatrix[i][j] > 0)
				numb++;

	return numb;
}

void Graph::InsertVertex(const int& vertex)
{ 
	if (!IsFull())
		vertList.push_back(vertex);
	else
	{
		cout << "Граф уже заполнен. Невозможно добавить новую вершину" << endl;
		return;
	}
}

void Graph::InsertEdge(const int& vertex1, const int& vertex2, int weight)
{

	if (GetVerticesPos(vertex1) != (-1) && GetVerticesPos(vertex2) != (-1))
	{
		int vertPos1 = GetVerticesPos(vertex1);
		int vertPos2 = GetVerticesPos(vertex2);
		if (adjMatrix[vertPos1][vertPos2] != 0 || adjMatrix[vertPos2][vertPos1] != 0)
		{
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else
			adjMatrix[vertPos1][vertPos2] = weight;
	}
	else
	{
		if (weight < 1) 
			cout << "\nДанная величина веса некорректна\n";
		else
			cout << "Обеих вершин (или одной из них) нет в графе" << endl; cout << "Исходная вершина: ";

		int sourceVertex, targetVertex, edgeWeight;
		cin >> sourceVertex;

		cout << "Конечная вершина: ";
		cin >> targetVertex;
		cout << "Вес ребра: ";
		cin >> edgeWeight;

		graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
	}
}

void Graph::PrintGraph()
{
	if (!IsEmpty())
	{
		cout << "Матрица смежности графа: " << endl;

		for (int i = 0; i < vertList.size(); i++)
		{
			cout << vertList[i] << " ";

			for (int j = 0; j < vertList.size(); j++)
				cout << setw(4) << adjMatrix[i][j];

			cout << endl;
		}
	}
	else
		cout << "\nГраф пуст\n" << endl;
}

void Graph::EraseLastVertex()
{
	if (IsEmpty())
	{
		cout << "\nГраф пуст\n";
		return;
	}

	int n = vertList.size();

	for (int j = 0; j < n; j++)
	{
		adjMatrix[n - 1][j] = 0;
		adjMatrix[j][n - 1] = 0;
	}

	vertList.pop_back();
}

void Graph::EraseEdge(const int& vertex1, const int& vertex2)
{
	if (GetVerticesPos(vertex1) != (-1) && GetVerticesPos(vertex2) != (-1))
	{
		int vertPos1 = GetVerticesPos(vertex1);
		int vertPos2 = GetVerticesPos(vertex2);

		if (adjMatrix[vertPos1][vertPos2] != 0 || adjMatrix[vertPos2][vertPos1] != 0)
		{
			adjMatrix[vertPos1][vertPos2] = 0;
			adjMatrix[vertPos2][vertPos1] = 0;
		}
		else
		{
			cout << "Ребра между данными вершинами нет\n" << endl;
			return;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе" << endl;
		return;
	}
}

void Graph::DrawGraph()
{
	int n = graph.GetAmountVertices();
	for (int i = 0; i < n; i++)
		if (!standView)
			SetCoordinats(i, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int a = adjMatrix[i][j];

			if (a != 0)
				drawLine(a, vertcrd[i].x, vertcrd[i].y, vertcrd[j].x, vertcrd[j].y, false);

			if (a == adjMatrix[j][i] && a != 0)
				drawLine(a, vertcrd[j].x, vertcrd[j].y, vertcrd[i].x, vertcrd[i].y, false);
		}

	drawVertex(n, prohod);

	glutPostRedisplay();
}

int ClickOnCircle(int x, int y)
{
	for (int i = 0; i < graph.GetAmountVertices(); i++)
		if (pow(x - vertcrd[i].x, 2) + pow(y - vertcrd[i].y, 2) <= pow(R, 2))
			return i;

	return -1;
}

void ButtonMouseOn(int x, int y)
{
	if (x > 10 && x < WinW / 7 && y > WinH - WinH / 10 && y < WinH - 20)
	{
		ButtonCheck = 1;
	}
	else
	{
		if (x > 10 && x < WinW / 7 && y > WinH - 2 * (WinH / 10) && y < WinH - (WinH / 10) - 20)
		{
			ButtonCheck = 2;
		}
		else
		{
			if (x > 10 && x < WinW / 7 && y > WinH - 3 * (WinH / 10) && y < WinH - 2 * (WinH / 10) - 20)
			{
				ButtonCheck = 3;
			}
			else
			{
				if (x > 10 && x < WinW / 7 && y > WinH - 4 * (WinH / 10) && y < WinH - 3 * (WinH / 10) - 20)
				{
					ButtonCheck = 4;
				}
				else
				{
					if (x > 10 && x < WinW / 7 && y > WinH - 5 * (WinH / 10) && y < WinH - 4 * (WinH / 10) - 20)
					{
						ButtonCheck = 5;
					}
					else
					{
						if (x > 10 && x < WinW / 7 && y > WinH - 6 * (WinH / 10) && y < WinH - 5 * (WinH / 10) - 20)
						{
							ButtonCheck = 6;
						}
						else
						{
							ButtonCheck = 0;

						}
					}
				}
			}
		}
	}
}

void mouseMove(int x, int y)
{
	y = WinH - y;
	x_coord_mouse = x;
	y_coord_mouse = y;

	int i = ClickOnCircle(x, y);

	if (i != -1)
		vertmouse[i] = true;
	else
		for (int j = 0; j < graph.GetAmountVertices(); j++)
			vertmouse[j] = false;

	if (vertmove)
	{
		vertcrd[Moving_Vertex].x = x_coord_mouse;
		vertcrd[Moving_Vertex].y = y_coord_mouse;
	}

	ButtonMouseOn(x, y);
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	int j = ClickOnCircle(x, WinH - y);

	if (vertmove)
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			vertmove = false;
			return;
		}

	if (j != -1)
	{
		standView = true;

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			vertmove = true;
			Moving_Vertex = j;
			return;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > 20) && (y < WinH / 10))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			New_Way.clear();
			Way.clear();

			cout << "\nЗадача Коммивояжера:\n";

			int** matrix = ChangeMatrix();
			bool checker = IsSalesmanPossible(matrix);

			if (!checker)
			{
				cout << "\nДля данного графа нельзя выполнить задачу коммивояжера\n";
				return;
			}

			int n = graph.GetAmountVertices();

			while (Way.size() < n)
				matrix = HighZero(matrix);

			cout << endl;

			ButtonSalesmanSecond = true;
			PrintResult();

			if (prohod)
				prohod = false;
			else
				prohod = true;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > (WinH / 10) + 20) && (y < 2 * (WinH / 10)))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			ButtonSalesmanSecond = false;
			prohod = false;

			New_Way.clear();
			Way.clear();

			Graph New;
			graph = New;

			MakeGraph();
			return;
		}

		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			standView = false;
			return;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > 2 * (WinH / 10) + 20) && (y < 3 * (WinH / 10)))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			ButtonSalesmanSecond = false;
			prohod = false;
			int cur = graph.GetAmountVertices();
			graph.InsertVertex(cur + 1);

			vertcrd[cur].x = WinW / 2;
			vertcrd[cur].y = WinH / 2;
			return;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > 3 * (WinH / 10) + 20) && (y < 4 * (WinH / 10)))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			ButtonSalesmanSecond = false;
			prohod = false;
			graph.EraseLastVertex();

			int cur = graph.GetAmountVertices();

			return;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > 4 * (WinH / 10) + 20) && (y < 5 * (WinH / 10)))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			ButtonSalesmanSecond = false;
			prohod = false;
			int sourceVertex, targetVertex, edgeWeight;

			cout << "Исходная вершина: ";
			cin >> sourceVertex;
			cout << "Конечная вершина: ";
			cin >> targetVertex;
			cout << "Вес ребра: ";
			cin >> edgeWeight;

			graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
			return;
		}
	}

	if ((x > 10) && (x < WinW / 7) && (y > 5 * (WinH / 10) + 20) && (y < 6 * (WinH / 10)))
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			ButtonSalesmanSecond = false;
			prohod = false;
			int sourceVertex, targetVertex;

			cout << "Исходная вершина: ";
			cin >> sourceVertex;
			cout << "Конечная вершина: ";
			cin >> targetVertex;

			graph.EraseEdge(sourceVertex, targetVertex);
			return;
		}
	}
}

void drawButtonSalesman()
{
	if (ButtonCheck == 1)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);
	glVertex2i(10, WinH - 20);
	glVertex2i(10, WinH - WinH / 10);
	glVertex2i(WinW / 7, WinH - WinH / 10);
	glVertex2i(WinW / 7, WinH - 20);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2i(10, WinH - 20);
	glVertex2i(10, WinH - WinH / 10);
	glVertex2i(WinW / 7, WinH - WinH / 10);
	glVertex2i(WinW / 7, WinH - 20);

	glEnd();

	string name = "Salesman";

	glRasterPos2i(WinW / 34, 0.93 * WinH);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
}

void drawButtonNewGraph()
{
	if (ButtonCheck == 2)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);
	glVertex2i(10, WinH - (WinH / 10) - 20);
	glVertex2i(10, WinH - 2 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - (WinH / 10) - 20);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2i(10, WinH - (WinH / 10) - 20);
	glVertex2i(10, WinH - 2 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - WinH / 10 - 20);

	glEnd();

	string name = "Create new";
	string name1 = "Graph";

	glRasterPos2i(WinW / 34, (0.83 * WinH) + 5);

	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);

	glRasterPos2i(WinW / 34, (0.83 * WinH) - 13);

	for (int i = 0; i < name1.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name1[i]);
}

void drawButtonAddVertex()
{
	if (ButtonCheck == 3)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);

	glVertex2i(10, WinH - 2 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 3 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 10) - 20);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(10, WinH - 2 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 3 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 2 * (WinH / 10) - 20);

	glEnd();

	string name = "Add Vertex";

	glRasterPos2i(WinW / 34, 0.73 * WinH);

	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);

}

void drawButtonDelVertex()
{
	if (ButtonCheck == 4)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);

	glVertex2i(10, WinH - 3 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 4 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 10) - 20);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(10, WinH - 3 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 4 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 3 * (WinH / 10) - 20);

	glEnd();

	string name = "Delete last ";
	string name1 = "Vertex";

	glRasterPos2i(WinW / 34, (0.63 * WinH) + 5);

	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);

	glRasterPos2i(WinW / 34, (0.63 * WinH) - 13);
	for (int i = 0; i < name1.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name1[i]);
}

void drawButtonAddEdge()
{
	if (ButtonCheck == 5)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);
	glVertex2i(10, WinH - 4 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 5 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 10) - 20);

	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(10, WinH - 4 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 5 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 4 * (WinH / 10) - 20);

	glEnd();
	string name = "Add Edge";

	glRasterPos2i(WinW / 34, 0.53 * WinH);

	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
}

void drawButtonDelEdge()
{
	if (ButtonCheck == 6)
		glColor3f(0.9, 0.9, 0.9);
	else
		glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_QUADS);
	glVertex2i(10, WinH - 5 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 6 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 10) - 20);

	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(10, WinH - 5 * (WinH / 10) - 20);
	glVertex2i(10, WinH - 6 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 6 * (WinH / 10));
	glVertex2i(WinW / 7, WinH - 5 * (WinH / 10) - 20);
	glEnd();

	string name = "Delete Edge";

	glRasterPos2i(WinW / 34, 0.43 * WinH);

	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
}

void MakeGraph()
{
	standView = false;
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight;

	cout << "Введите количество вершин в графе: ";
	cin >> amountVerts;
	cout << "Введите количество ребер в графе: ";
	cin >> amountEdges;

	for (int i = 1; i <= amountVerts; i++)
		graph.InsertVertex(i);

	for (int i = 0; i < amountEdges; i++)
	{
		cout << "Исходная вершина: ";
		cin >> sourceVertex;
		cout << "Конечная вершина: ";
		cin >> targetVertex;
		cout << "Вес ребра: ";
		cin >> edgeWeight;

		graph.InsertEdge(sourceVertex, targetVertex, edgeWeight);
	}

	cout << endl;
	graph.PrintGraph();
}

void Reshape(int w, int h)
{
	WinW = w;
	WinH = h;

	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void Display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawButtonNewGraph();
	drawButtonSalesman();

	drawButtonAddVertex();
	drawButtonDelVertex();

	drawButtonAddEdge();
	drawButtonDelEdge();

	graph.DrawGraph();

	if (prohod) 
	{
		for (int i = 0; i < New_Way.size() - 1; i++)
		{
			int vertPos1 = graph.GetVerticesPos(New_Way[i]);
			int vertPos2 = graph.GetVerticesPos(New_Way[i + 1]);

			drawLine(i + 1, vertcrd[vertPos2].x, vertcrd[vertPos2].y, vertcrd[vertPos1].x, vertcrd[vertPos1].y, true);
		}

		for (int i = 0; i < graph.GetAmountVertices(); i++)
		{
			for (int j = 0; j < New_Way.size(); j++)
			{
				if (i == New_Way[j])
					drawCircle(vertcrd[i].x, vertcrd[i].y, R / 2, true);

				if (i == 0)
					drawCircle(vertcrd[i].x, vertcrd[i].y, R / 2, true);
			}
		
			drawText(i + 1, vertcrd[i].x, vertcrd[i].y, false);
		}
	}

	glutSwapBuffers();
}

int** ChangeMatrix()
{
	int n = graph.GetAmountVertices();
	int** matrix = new int* [n];

	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int elem = graph.GetAdjMatrixElement(i, j);

			if (elem == 0 or i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}

	if (ButtonSalesmanSecond == true)
		cout << "Начальная матрица: \n";
		PrintMatrix(matrix);

	return matrix;
}

int* SearchMinElement(int* line, int n)
{
	int min = 1000000;

	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];

	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;

	return line;
}

void PrintMatrix(int** matrix)
{
	int n = graph.GetAmountVertices();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << matrix[i][j];

		cout << endl;
	}
}

int** ReductMatrix(int** oldmatrix)
{
	int** matrix = oldmatrix;
	int n = graph.GetAmountVertices();

	for (int i = 0; i < n; i++)
		matrix[i] = SearchMinElement(matrix[i], n);

	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];

		for (int j = 0; j < n; j++)
			if (matrix[j][i] >= 0) 
				matrix[j][i] -= min;

	}
	if (ButtonSalesmanSecond == true) 
	{
		cout << "\nРедуцированная матрица: \n";
		PrintMatrix(matrix);
	}

	return matrix;
}

int** HighZero(int** oldmatrix)
{
	int n = graph.GetAmountVertices();
	int** matrix = ReductMatrix(oldmatrix);
	int max = -1;
	int line = 0, column = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];

				for (int k = 0; k < n; k++)
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];

				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}

	pair<int, int> p;

	p.first = line + 1;
	p.second = column + 1;

	Way.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}

	if (ButtonSalesmanSecond == true) 
	{
		cout << endl;
		cout << "Матрица после удаления 0 с наибольшей оценкой: \n";
		PrintMatrix(matrix);
		cout << "\nПромежуточные отрезки путей: ";

		for (int i = 0; i < Way.size(); i++)
			cout << Way[i].first << " -> " << Way[i].second;

		cout << endl;
	}

	return matrix;
}

void PrintResult()
{
	int second = Way[0].second;
	int i = 2;

	New_Way.push_back(Way[0].first);
	New_Way.push_back(Way[0].second);

	while (i != graph.GetAmountVertices() + 1)
		for (int j = 1; j < graph.GetAmountVertices(); j++)
			if (Way[j].first == second)
			{
				second = Way[j].second;
				New_Way.push_back(second);
				i++;
			}

	cout << "Кротчайший путь :  ";

	for (int i = 0; i < New_Way.size(); i++)
	{
		cout << New_Way[i];

		if (i != New_Way.size() - 1)
			cout << " -> ";
	}

	cout << endl;

	int sum = 0;

	for (int i = 0; i < Way.size(); i++)
	{
		int line = Way[i].first - 1;
		int column = Way[i].second - 1;

		sum += graph.GetAdjMatrixElement(line, column);
	}

	cout << "\nДлина пути : " << sum << endl;

}

void SetCoordinats(int i, int n)
{
	int rad;
	int x0 = WinW / 2;
	int y0 = WinH / 2;

	if (WinW > WinH)
	{
		R = 5 * (WinH / 26) / n;
		rad = WinH / 2 - R - 10;
	}
	else
	{
		R = 5 * (WinW / 26) / n;
		rad = WinW / 2 - R - 10;
	}

	float theta = 2.0f * 3.1415926f * i / n;
	int y1 = rad * cos(theta) + y0;
	int x1 = rad * sin(theta) + x0;

	vertcrd[i].x = x1;
	vertcrd[i].y = y1;
}

bool IsSalesmanPossible(int** matrix)
{
	if (graph.IsEmpty())
		return false;

	for (int i = 0; i < graph.GetAmountVertices(); i++)
	{
		int cnt = 0;

		for (int j = 0; j < graph.GetAmountVertices(); j++)
			if (matrix[i][j] > 0)
				cnt++;

		if (cnt < 1)
			return false;
	}

	return true;
}

void drawCircle(int x, int y, int R, bool r)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	float x1, y1;
	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;

		glVertex2f(x1, y1);
	}

	glEnd();

	if (r)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);

	float x2, y2;
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void drawCircleMouseOn(int x, int y, int R)
{
	glColor3f(0.9, 0.9, 0.9);
	float x1, y1;
	glBegin(GL_POLYGON);

	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;
		glVertex2f(x1, y1);
	}

	glEnd();
	glColor3f(0.0, 0.392, 0.0);
	float x2, y2;
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int text, int x1, int y1, bool red)
{
	if (red)
		glColor3f(1.0, 0.0, 0.0);
	else
		glColor3f(0.0, 0.0, 0.0);

	GLvoid* font = GLUT_BITMAP_TIMES_ROMAN_24;
	string s = to_string(text);

	glRasterPos2i(x1 - 5, y1 - 5);

	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawLine(int text, int x0, int y0, int x1, int y1, bool b)
{
	if (b)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();

	if (b)
		drawText(text, (x0 + x1) / 2 - 15, (y0 + y1) / 2 - 15, b);
	else 
		drawText(text, (x0 + x1) / 2 + 15, (y0 + y1) / 2 + 15, b);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);

	vx *= s;
	vy *= s;

	x1 = x1 + R * vx;
	y1 = y1 + R * vy;

	if (b)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
		glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	}
	glEnd();
}

void drawVertex(int n, bool r)
{
	for (int i = 0; i < n; i++)
	{
		if (vertmouse[i])
			drawCircleMouseOn(vertcrd[i].x, vertcrd[i].y, R);
		else
			drawCircle(vertcrd[i].x, vertcrd[i].y, R, false);

		drawText(i + 1, vertcrd[i].x, vertcrd[i].y, false);
	}
}