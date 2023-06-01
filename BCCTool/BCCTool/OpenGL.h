#pragma once

#include <cmath>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

using namespace System::Windows::Forms;

GLfloat rotateX = 0;
GLfloat rotateY = 0;
GLfloat zoom = 1;

namespace OpenGLForm
{
	public ref class COpenGL : public System::Windows::Forms::NativeWindow
	{
	public:
		float* vertices;
		int* faces;

		int facesNum = 0;
		int verNum = 0;

		COpenGL(System::Windows::Forms::Form^ parentForm, GLsizei iWidth, GLsizei iHeight)
		{
			vertices = NULL;
			faces = NULL;

			CreateParams^ cp = gcnew CreateParams;

			cp->X = 12;
			cp->Y = 114;
			cp->Height = iHeight;
			cp->Width = iWidth;

			cp->Parent = parentForm->Handle;

			cp->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			this->CreateHandle(cp);

			m_hDC = GetDC((HWND)this->Handle.ToPointer());

			if (m_hDC)
			{
				MySetPixelFormat(m_hDC);
				ReSizeGLScene(iWidth, iHeight);
				InitGL();
			}
		}

		void Reset()
		{
			facesNum = 0;
			verNum = 0;
			vertices = NULL;
			faces = NULL;
		}

		int GetZeroesOfMaxOfArray(float* arr, int size)
		{
			float max = arr[0];

			for (int i = 1; i < size; i++)
				if (arr[i] > max)
					max = arr[i];

			int number_of_digits = 0;
			int intMax = max;

			do 
			{
				++number_of_digits;
				intMax /= 10;
			} while (intMax);

			return number_of_digits;
		}

		System::Void Render(System::Void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			if (rotateX >= 360)
				rotateX -= 360;
			else if (rotateX <= -360)
				rotateX += 360;

			if (rotateY >= 360)
				rotateY -= 360;
			else if (rotateY <= -360)
				rotateY += 360;

			glScalef(zoom, zoom, zoom);
			glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
			glRotatef(rotateX, 0.0f, 1.0f, 0.0f);

			if (vertices != NULL) 
			{
				int n = GetZeroesOfMaxOfArray(vertices, verNum);

				glBegin(GL_TRIANGLES);
				glColor3f(0.0f, 1.0f, 0.0f);

				for (int i = 0; i < facesNum; i++)
				{
					glNormal3f(vertices[faces[i * 3] * 3] / pow(10, n), vertices[faces[i * 3] * 3 + 1] / pow(10, n), vertices[faces[i * 3] * 3 + 2] / pow(10, n));
					glNormal3f(vertices[faces[i * 3 + 1] * 3] / pow(10, n), vertices[faces[i * 3 + 1] * 3 + 1] / pow(10, n), vertices[faces[i * 3 + 1] * 3 + 2] / pow(10, n));
					glNormal3f(vertices[faces[i * 3 + 2] * 3] / pow(10, n), vertices[faces[i * 3 + 2] * 3 + 1] / pow(10, n), vertices[faces[i * 3 + 2] * 3 + 2] / pow(10, n));

					glVertex3f(vertices[faces[i * 3] * 3] / pow(10, n), vertices[faces[i * 3] * 3 + 1] / pow(10, n), vertices[faces[i * 3] * 3 + 2] / pow(10, n));
					glVertex3f(vertices[faces[i * 3 + 1] * 3] / pow(10, n), vertices[faces[i * 3 + 1] * 3 + 1] / pow(10, n), vertices[faces[i * 3 + 1] * 3 + 2] / pow(10, n));
					glVertex3f(vertices[faces[i * 3 + 2] * 3] / pow(10, n), vertices[faces[i * 3 + 2] * 3 + 1] / pow(10, n), vertices[faces[i * 3 + 2] * 3 + 2] / pow(10, n));
				}
				glEnd();											// Done drawing the pyramid
			}
		}

		System::Void SwapOpenGLBuffers(System::Void)
		{
			SwapBuffers(m_hDC);
		}

	private:
		HDC m_hDC;
		HGLRC m_hglrc;

	protected:
		~COpenGL(System::Void)
		{
			this->DestroyHandle();

			delete[] vertices;
			delete[] faces;
			facesNum = 0;
		}

		GLint MySetPixelFormat(HDC hdc)
		{
			static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
			{
				sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
				1,											// Version Number
				PFD_DRAW_TO_WINDOW |						// Format Must Support Window
				PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
				PFD_DOUBLEBUFFER,							// Must Support Double Buffering
				PFD_TYPE_RGBA,								// Request An RGBA Format
				16,										// Select Our Color Depth
				0, 0, 0, 0, 0, 0,							// Color Bits Ignored
				0,											// No Alpha Buffer
				0,											// Shift Bit Ignored
				0,											// No Accumulation Buffer
				0, 0, 0, 0,									// Accumulation Bits Ignored
				16,											// 16Bit Z-Buffer (Depth Buffer)  
				0,											// No Stencil Buffer
				0,											// No Auxiliary Buffer
				PFD_MAIN_PLANE,								// Main Drawing Layer
				0,											// Reserved
				0, 0, 0										// Layer Masks Ignored
			};

			GLint  iPixelFormat;

			// get the device context's best, available pixel format match 
			if ((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
			{
				MessageBox::Show("ChoosePixelFormat Failed");
				return 0;
			}

			// make that match the device context's current pixel format 
			if (SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
			{
				MessageBox::Show("SetPixelFormat Failed");
				return 0;
			}

			if ((m_hglrc = wglCreateContext(m_hDC)) == NULL)
			{
				MessageBox::Show("wglCreateContext Failed");
				return 0;
			}

			if ((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				MessageBox::Show("wglMakeCurrent Failed");
				return 0;
			}


			return 1;
		}

		bool InitGL(GLvoid)										// All setup for opengl goes here
		{
			glShadeModel(GL_SMOOTH);							// Enable smooth shading
			glClearColor(0.8f, 0.8f, 0.8f, 5.0f);				// Black background
			glClearDepth(1.0f);									// Depth buffer setup
			glEnable(GL_DEPTH_TEST);							// Enables depth testing
			glEnable(GL_LIGHTING);
			glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
			glEnable(GL_NORMALIZE);

			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);

			float light0_diffuse[] = { 0.7, 0.7, 0.7 };
			float light0_direction[] = { 0.0, 0.0, 1.0, 0.0 };
			float light1_direction[] = { 0.0, 0.0, -1.0, 0.0 };
			float light2_diffuse[] = { 0.5, 0.5, 0.5 };
			float light2_direction[] = { 0.0, 1.0, 0.0, 0.0 };
			float light3_direction[] = { 0.0, -1.0, 0.0, 0.0 };
			float light4_direction[] = { 1.0, 0.0, 0.0, 0.0 };
			float light5_direction[] = { -1.0, 0.0, 0.0, 0.0 };

			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); 
			glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse);
			glLightfv(GL_LIGHT1, GL_POSITION, light1_direction);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
			glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, light2_diffuse);
			glLightfv(GL_LIGHT3, GL_POSITION, light3_direction);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, light2_diffuse);
			glLightfv(GL_LIGHT4, GL_POSITION, light4_direction);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, light2_diffuse);
			glLightfv(GL_LIGHT5, GL_POSITION, light5_direction);

			glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calculations
			return TRUE;										// Initialisation went ok
		}

		GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialise the gl window
		{
			if (height == 0)										// Prevent A Divide By Zero By
				height = 1;										// Making Height Equal One

			glViewport(0, 0, width, height);						// Reset The Current Viewport

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix

			gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
			gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.2f, -1.0f, 0.0f, 1.0f, 0.0f);
		}
	};
}