#include <iostream>
#include <GL/freeglut.h>
#include "Graph.h"

using namespace std;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	glutInit(&argc, argv);

	makeGraph();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WinW, WinH);

	glutCreateWindow("Graph");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();
}