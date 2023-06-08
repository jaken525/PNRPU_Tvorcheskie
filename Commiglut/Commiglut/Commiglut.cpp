#include <iostream>
#include <GL/freeglut.h>
#include "Graph.h"

using namespace std;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	glutInit(&argc, argv);

	MakeGraph();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WinW, WinH);

	glutCreateWindow("Graph");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}